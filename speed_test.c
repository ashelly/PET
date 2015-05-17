#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "pet_utils.h"

// Poker Evaluator Testbed
//
//: Based on code collected in the XPokerEval library by James Devlin at:
//    http://www.codingthewheel.com/archives/poker-hand-evaluator-roundup
//: original code from Ray Wouten, Steve Brecher, Kevin Suffecool 
//:  and others on twoplustwo.com.  
//: See READMEs in individual directories for full credits
//:  
// This implementation
// (c) 2015 Adam Shelly (github.com/ashelly)

#define NCARDS 7        //hand size

#include "PET_evaluator.h"


/* ****************************************
//Poker Evaluators under Test must provide:
typedef Card;   // The card representation

int PET_init( );
//  Does any setup needed for the evaluator.
//  File reading, table creation, etc.
//  Return 0 on success.

Card PET_makecard(pet_card i); 
//  Take a number from 0..51, return the appropriate Card representation.
//  See enum card_t in 'pet_utils.h" for the order.  

#define PETHAND N
// where N is the number of Card items needed to represent a hand.
// Each 'player' gets a hand represented by `Card h[PETHAND]`
//TODO: maybe replace this with a required Hand_t?  Most don't seem to need it.

void PET_addcard(Card* hand,Card card);
// Adds card to hand.  Will be called NCARDS times.

typedef EquivClass;  //The 'equivalence' class of the hand.
//The expectation is that the largest value wins.

EquivClass PET_evaluate(Card* hand);  // *timed
//  Evaluate the hand, return the equivalence class

int PET_rank(EquivClass v);        //* timed
//  Given an equivalence class, return a integer representing the rank.
// this can be in the internal format, as long as it is between 0 and 9.

pet_rank PET_ranktran(int rank); //translate internal rank to pet_rank.

pet_rank PET_decode(Card* hand,EquivClass v, pet_card* cards_out);
//   Given the hand and the result, show the rank.
//   If cards_out is not null, treat as array, fill with 5 winning cards.

Note that `makecard`, `ranktran` and `decode` are adapters specifically for the purpose
of converting between the representation used by this testharness and 
the implementation's internal representation.
They will not be timed and may take a different form in real-world usage.

*/

#define LOTS   50000000L //how many random hands to time

//Expected frequency for 7 card hands
static int expected_freq_7[] = {
  0,
  23294460,
  58627800,
  31433400,
  6461620,
  6180020,
  4047644,
  3473184,
  224848,
  41584
};


//"Knuth Shuffle"  or "Fisher-Yates"
void Shuffle(Card* Deck)
{
  int r,i;
  Card temp;
  for(i=51;i>0;i--)  {
    r=(int)(((float)rand())/RAND_MAX*i); //TODO: better rand
    temp = Deck[i];
    Deck[i]=Deck[r];
    Deck[r]=temp;
  }
}

//Adapters 
//   This routine initializes the deck.  A deck of cards is
//   simply an array of Cards of length 52 (no jokers).  This
//   routine should populate the array. 
void pet_init_deck(Card* deck) {
  int i;
  for (i=0;i<52;i++) 
    deck[i]=PET_makecard(i);
}

//Given `hand` of `n` cards, return eqivalence class
EquivClass pet_eval_hand(Card* hand,int n) {
  int i;
  Card h[PETHAND]={0};
  for (i=0;i<n;i++) PET_addcard(h,hand[i]);
  return PET_evaluate(h);
}

int valuecomp(const void* a,const void*b){ return petcard_value(*(int*)a)-petcard_value(*(int*)b);}

//Given 7 cards, verify that evaluator produces expected result.
//`winners` should be NULL, or an array of 5 pet_card, which will be filled with
// the best 5 out of 7
void verify(pet_card a,pet_card b, pet_card c, pet_card d, pet_card e, pet_card f, pet_card g, 
            pet_rank expected, pet_card* winners)
{
  EquivClass v;
  pet_rank actual;
  Card card,h[PETHAND]={0};
  pet_card hits[5];

  PET_addcard(h,PET_makecard(a));
  PET_addcard(h,PET_makecard(b));
  PET_addcard(h,PET_makecard(c));
  PET_addcard(h,PET_makecard(d));
  PET_addcard(h,PET_makecard(e));
  PET_addcard(h,PET_makecard(f));
  PET_addcard(h,PET_makecard(g));
  v  = PET_evaluate(h);
  actual = PET_decode(h,v,winners?hits:NULL);
  if (winners && PET_DECODES_CARDS) {
    int i;
    qsort(winners,5,sizeof(pet_card),valuecomp);
    qsort(hits,5,sizeof(pet_card),valuecomp);
    for (i=0; i<5 && (actual!=rInvalid); i++) {
      if (petcard_value(winners[i]) != petcard_value(hits[i])){
        printf("Error: card rank %d != %d\n",hits[i],winners[i]);
        actual = rInvalid; //force fail
      }
      if (actual == rFlush || actual == rStraightFlush){
        if (petcard_suit(winners[i]) != petcard_suit(hits[i])){
          printf("Error: card suit %d != %d\n",hits[i],winners[i]);
          actual = rInvalid; //force fail
        }
      }
    }
  }
  if (actual == expected) { printf ("ok.."); } 
  else printf("Error: rank %x != %x\n",actual,expected);
}


float report(const char* typestr, sysTime_t timings, sysTime_t endtimings, clock_t timer, int count)
{
  // display the clock results
  double clocksused = platformSysTimeToMs(platformTimeElapsed(endtimings,timings));
  float mhps = count/((double)clocksused/1000)/1000000.0;

  printf("\nValidation seconds = %.4lf\nTotal HighPrecision Clocks = %lf\n"
         "HighPrecision clocks per lookup = %lf\n", 
         (double)timer/CLOCKS_PER_SEC, clocksused, (double) clocksused /  count) ;

  printf("\n %lf Mhands/sec (%s)\n",mhps,typestr);
  return mhps;
}


//Eval LOTS of random hands
Card hands[LOTS][PETHAND]={0};

inline pet_card* setcards(pet_card* hand, pet_card c1, pet_card c2, pet_card c3, pet_card c4, pet_card c5){
  pet_card* hp = hand;
  *hp++=c1;  *hp++=c2;  *hp++=c3;  *hp++=c4;  *hp++=c5;
  return hand;
}

int main(int argc, char*argv[])
{
  long i;
  Card deck[52];
  Card hand[7];  //this is 7 individual cards, not a handrep
  pet_card best[5];
  int cardsLeft;
  int count = 0;
  int handTypeSum[10]={0};
  int a,b,c,d,e,f=-1,g=-1;
  EquivClass v;
  int rank;
  sysTime_t timings,endtimings;
  float speed[2];


  //TODO: MTRand
  srand(argc);

  if (PET_init()!=0) {
    printf("%s Initialization Error\n",PET_STR(EUT));
    return -1;
  }

  /* first verify some hands */
  //no hand
  verify(c2H,c3H,c4H,c5H,cTD,cJD,cKD, rHighCard, setcards(best,cKD,cJD,cTD,c5H,c4H));
  //1pr
  verify(cKH,c3H,c4H,c5H,cAD,cJD,cKD, rPair, setcards(best,cKH,cKD,cAD,cJD,c5H));
  //2pr 
  verify(cKD,c3H,c3C,c5H,cAD,cJD,cKS, rTwoPair, setcards(best,cKD,cKS,c3H,c3C,cAD));
  verify(cKD,c3H,c3C,c5H,c5S,c2D,cKS, rTwoPair, setcards(best,cKD,cKS,c5H,c5S,c3D));
  //trip
  verify(c3D,c4D,c6H,c3H,c9S,c3C,cTD, rThreeOfaKind, setcards(best,c3H,c3C,c3D,cTD,c9S));
  //straight
  verify(c3D,c4D,c9H,c5H,c2D,c3C,cAD, rStraight, setcards(best,c5H,c4D,c3D,c2D,cAD));
  verify(c3D,c4D,c6H,c5H,c2D,c3C,cAD, rStraight, setcards(best,c6H,c5H,c4D,c3D,c2D));
  verify(c3D,c4D,c6H,c5H,c2D,c7C,cAD, rStraight, setcards(best,c7C,c6H,c5H,c4D,c3D));
  verify(cTD,cJD,cKH,c5H,cQD,c3C,cAD, rStraight, setcards(best,cAD,cKH,cQD,cJD,cTD));
  //flush
  verify(c2H,c3H,c4H,c5H,cTD,cJH,cKD, rFlush, NULL);
  verify(cKH,c3H,c4H,c5H,cAH,cJD,cKD, rFlush, NULL);
  verify(cKD,c3H,c3D,c5D,cAD,cJD,cKS, rFlush, NULL);
  verify(c3D,c4D,c6D,c3H,c9D,c3C,cTD, rFlush, NULL);
  verify(c3D,c4D,c6D,c3H,c9D,c2D,cTD, rFlush, NULL);
  verify(c3D,c4D,c6D,c7D,c9D,cJD,cTD, rFlush, NULL);
  //fh
  verify(c3D,c4D,c3H,c4H,c9S,c3C,cTD, rFullHouse, NULL);
  verify(c4S,c4D,c6H,c4H,c3S,c3C,cTD, rFullHouse, NULL);
  verify(c3D,c9D,c9H,c3H,c9S,c3C,cTD, rFullHouse, NULL);
  
  //quad
  verify(c3D,c9D,c9H,c3H,c3S,c3C,cTD, rFourOfaKind, NULL);

  //straight flush low
  verify(cAH,c2H,c3H,c4H,c5H,c9D,cTD, rStraightFlush, NULL);
  verify(cAD,c2H,c3H,cJD,cKD,cQD,cTD, rStraightFlush, NULL);
  verify(c9D,c7D,c8D,cJD,cKD,cQD,cTD, rStraightFlush, NULL);
  printf("\n");

  pet_init_deck(deck);

  printf("Enumerating all possible hands\n");

  count = 0;
  clock_t timer = clock();						    // start regular clock
  platformGetTime(&timings);                   //and h-p clock

  // loop over every possible seven-card hand
  for(g=0;g<46;g++)
    {
      hand[6] = deck[g];
      for(f=g+1;f<47;f++)
        {
          hand[5] = deck[f];
          //loop over every possible 5 card hand
          for(e=f+1;e<48;e++)
            {
              hand[4] = deck[e];
              for(d=e+1;d<49;d++)
                {
                  hand[3] = deck[d];
                  for(c=d+1;c<50;c++)
                    {
                      hand[2] = deck[c];
                      for(b=c+1;b<51;b++)
                        {
                          hand[1] = deck[b];
                          for(a=b+1;a<52;a++)
                            {
                              hand[0] = deck[a];
				
                              v = pet_eval_hand( hand, NCARDS );
                              rank = PET_rank(v);
                              handTypeSum[rank]++;
                            }
                        }
                    }
                }
            }
        }
    }

  platformGetTime(&endtimings);	  // end the high precision clock
  timer = clock() - timer;				  // end the regular clock

  count = 0;
  for(i=0;i<=9;i++){
    pet_rank r = PET_ranktran(i);
    if (r>rInvalid && r<= rStraightFlush) 
      {
        printf("%15s: %8d\n", pet_rank_str[r], handTypeSum[i]);
        if (handTypeSum[i]!=expected_freq_7[r]) {
          printf("Error, should be %8d\n",expected_freq_7[r]);
        }
      }
    count+=expected_freq_7[r]; //TODO: need expected for N<7
  }

  speed[0]=report("Enumerated", timings,endtimings,timer,count);

  memset(handTypeSum,0,sizeof(handTypeSum[0])*10);


  printf("\nCreating %ld random hands...\n",LOTS);
  cardsLeft = 0;	
  for (i=0;i<LOTS;i++) {

    if (cardsLeft<7) {
      Shuffle(deck);
      cardsLeft=52;
    }
    memset(hands[i],0,sizeof(Card)*PETHAND);//empty hand
    --cardsLeft;                            //don't do inside addcard cal, b/c it may be macro
    PET_addcard(hands[i],deck[cardsLeft]);
    --cardsLeft;
    PET_addcard(hands[i],deck[cardsLeft]);
    --cardsLeft;
    PET_addcard(hands[i],deck[cardsLeft]);
    --cardsLeft;
    PET_addcard(hands[i],deck[cardsLeft]);
    --cardsLeft;
    PET_addcard(hands[i],deck[cardsLeft]);
    --cardsLeft;
    PET_addcard(hands[i],deck[cardsLeft]);
    --cardsLeft;
    PET_addcard(hands[i],deck[cardsLeft]);
  }


  //TIME LOTS of Evals
  printf("Evaluating %ld hands...\n",LOTS);
  count = 0;
  timer = clock();						    // start regular clock
  platformGetTime(&timings);                   //and h-p clock
  
  for (i=0;i<LOTS;i++)
    {
      EquivClass r = PET_evaluate( hands[i] );
      handTypeSum[PET_rank(r)]++;
      count++;
    }

  platformGetTime(&endtimings);	  // end the high precision clock
  timer = clock() - timer;				  // end the regular clock

  for (i = 0; i <= 9; i++) {
    // display results
    pet_rank r = PET_ranktran(i);
    if (r>rInvalid && r<= rStraightFlush) {
      printf("\n%16s = %d", pet_rank_str[r], handTypeSum[i]);
    }
  }

  printf("\nTotal Hands = %d\n", count);

  speed[1]=report("Random",timings,endtimings,timer,count);

  printf("%s\t%f\t%f\n",PET_STR(EUT),speed[0],speed[1]);

}


