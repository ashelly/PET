#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/* Table Builder for Paul Senzee's 7 card poker evaluator.

Authors:
   Paul Senzee (index52c7 function and lookup tables)
   http://www.senzee5.com/2007/01/7.html

   James Devlin (code to build 266MB lookup table from index52c7)
   http://www.codingthewheel.com/archives/poker-hand-evaluator-roundup

   Adam Shelly (minor modifications for PET framework)
   http://wwww.github.com/ashelly/PET_framework

*/

#include "source/index52c7.h"
#include "../cactuskev/KEV_eval.h"

extern short eval_7hand( int *hand );

#define LOOKUP_TABLE_SIZE 133784560

EquivClass* snzTable;


uint16_t* create_table(const char* saveAs)
{
 	printf("Allocating memory for 133,784,560 entries...\n");
	uint16_t* hand_lookup = (uint16_t*) malloc(sizeof(uint16_t)*LOOKUP_TABLE_SIZE);
	if (!hand_lookup)
		return NULL;

	printf("Creating %s...\n", saveAs);

	printf("Initializing decks...\n");
	// Initialize the Pokersource deck...
	int64_t virginDeck[52];
	int c,cactusKevDeck[52];
	for (c = 0; c < 52; c++){
	  virginDeck[c] = (0x1LL << c);
	  cactusKevDeck[c] = KEV_makecard((int)c);
	}	 

	int c0, c1, c2, c3, c4, c5, c6;
	int64_t h0, h1, h2, h3, h4, h5, h6;
	int cactuskev_hand[7];
	int count = 0;

	printf("Building table: enumerating 7-card hands...\n");
	for (c0 = 0; c0 < 46; c0++) {
	  h0 = virginDeck[c0]; // first card
	  cactuskev_hand[0] = cactusKevDeck[c0];
	  for (c1 = c0+1; c1 < 47; c1++) {
		 h1 = h0 | virginDeck[c1]; // 2nd card
		 cactuskev_hand[1] = cactusKevDeck[c1];
		 for (c2 = c1+1; c2 < 48; c2++) {
			h2 = h1 | virginDeck[c2]; // 3rd card
			cactuskev_hand[2] = cactusKevDeck[c2];
			for (c3 = c2+1; c3 < 49; c3++) {
			  h3 = h2 | virginDeck[c3]; // 4th card
			  cactuskev_hand[3] = cactusKevDeck[c3];
			  for (c4 = c3+1; c4 < 50; c4++) {
				 h4 = h3 | virginDeck[c4]; // 5th card
				 cactuskev_hand[4] = cactusKevDeck[c4];
				 for (c5 = c4+1; c5 < 51; c5++) {
					h5 = h4 | virginDeck[c5]; // 6th card
					cactuskev_hand[5] = cactusKevDeck[c5];
					for (c6 = c5+1; c6 < 52; c6++) {
					  h6 = h5 | virginDeck[c6]; // 7th card
					  cactuskev_hand[6] = cactusKevDeck[c6];
					  
					  int hashedIndex = index52c7(h6);
					  hand_lookup[hashedIndex] = eval_7hand(cactuskev_hand);
					  
					  if ((count++ % 1000000) == 0)
						 printf("%d hands complete...\n", count);
					}
				 }
			  }
			}
		 }
	  }
	}

	printf("Saving the lookup table into %s...\n", saveAs);

	// output the array now that I have it!!
	FILE * fout = fopen(saveAs, "wb");
	if (fout)
	{
		fwrite(hand_lookup, 2, LOOKUP_TABLE_SIZE, fout);  // big write, but quick
		fclose(fout);
	}
	else
	{
		printf("Problem creating the Output File!\n");
	}

	printf("Press any key to continue...");
	
}


int main(int c, char* v){
  create_table("snz_tables.dat");
}
