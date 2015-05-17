// PET adaptor for Moritz Hammer's evaluator
// http://www.pst.ifi.lmu.de/~hammer/poker/handeval.html
//
// adaptor (c) 2015 Adam Shelly (github.com/ashelly)

#include <stdint.h>
#include "../pet_utils.h"
#include "source/handeval/handevaluator.h"

typedef unsigned char Card; 
typedef handeval_eq_class* EquivClass; 
typedef Card* Hand;


#define HAMHAND 8
static int HAM_init() { 
  //todo: add local version of these loaders with error checking and combined file
  load_equivalenceclasses("./ham_table1.dat"); 
  load_dag("./ham_table2.dat");
  return 0;
}
static inline Card HAM_makecard(int i){return (((i%13)<<2)|(i/13));}
static inline void HAM_addcard(Hand h, Card c){ h[h[7]++]=c;}
#define HAM_evaluate(h)   calculate_equivalence_class((h))
#define HAM_rank(v)       ((v)->type)
#define HAM_ranktran(r)   ((r)+1)


static inline pet_card ham2pet(char c) {
  return (c>>2)+(13*(c&3));
}

const char* ham_valstr="23456789TJQKA";
static inline pet_card pull_card_from_hand(char cardstr, Hand hand) 
{
  short i,cardval;
  for (cardval=0;ham_valstr[cardval]!=cardstr;cardval++) {
    if (cardval>12) { return (pet_card)-1; } //error
  }
  for (i=0;i<hand[7];i++) {
    if ( (hand[i]>>2)==cardval){
      pet_card retval = ham2pet(hand[i]);
      hand[i]=hand[--(hand[7])];
      return retval;
    }
  }
  return (pet_card)-1;
} 

static inline pet_rank HAM_decode(Card* hand,EquivClass v, pet_card* out)
{
  int i;
  pet_rank rank=HAM_ranktran(HAM_rank(v));
  if (out){
    Card h[HAMHAND];
    memcpy(h,hand,sizeof(h));
    for (i=0;i<5;i++){
      unsigned char cardstr = v->cards[i];
      out[i]=pull_card_from_hand(cardstr,h);
    }
  }
  return rank;
}
#define HAM_DECODES_CARDS 1   //True if decode fills `out` with cards
