// PET adaptor for the TwoPlusTwo 7 card hand evaluator
// http://archives1.twoplustwo.com/showflat.php?Cat=0&Number=8513906&amp;amp;amp;page=2&fpart=1&vc=1
//
// adaptor (c) 2015 Adam Shelly (github.com/ashelly)

#include "../pet_utils.h"
#include "TPT_eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLESIZE 32487834
uint32_t HR[TABLESIZE]={0};
int TPT_init(void)
{
  printf("Loading tpt_tables.dat file...");
  FILE * fin = fopen("tpt_tables.dat", "rb");
  if (!fin)
	 return -1;
  size_t bytesread = fread(HR, sizeof(HR), 1, fin);	// get the HandRank Array
  fclose(fin);
  printf("%ld bytes loaded.\n\n",bytesread*sizeof(HR));
  return 0;
}

