// PET adaptor for the Pokersource poker-eval evaluator
// http://gna.org/projects/pokersource/ 
//
// adaptor (c) 2015 Adam Shelly (github.com/ashelly)

#include <stdint.h>
#include "source/include/poker_defs.h"
#include "source/include/inlines/eval.h"
#include "../pet_utils.h"

#define Card StdDeck_CardMask
typedef uint32_t EquivClass;
#define Hand Card*


#define PSEHAND 1
#define PSE_init() (0)
#define PSE_makecard(i) (StdDeck_MASK(i))

#define PSE_addcard(h,c)  StdDeck_CardMask_OR(*h,*h,c)
#define PSE_evaluate(h)   (StdDeck_StdRules_EVAL_N(*h,7))
#define PSE_rank(v)       (HandVal_HANDTYPE(v)&0xF)

#define PSE_ranktran(r)   (((r)+1)%10)


static inline pet_card pull_card_from_hand(short cardval, Hand hand) 
{
  pet_card candidate;
  int suit;
  //try all suits until we find a match
  for (suit=0;suit<4;suit++) {
    Card result;
    candidate = StdDeck_MAKE_CARD(cardval,suit);
    StdDeck_CardMask_AND(result,*hand,StdDeck_MASK(candidate));
    if (!StdDeck_CardMask_IS_EMPTY(result)){
      StdDeck_CardMask_XOR(*hand,*hand,result); //remove match
      break;
    }
  }
  return candidate;
} 


//5x3bit numbers: how many cards of each value
static const uint16_t rank_reptable[]={
  0,4681,586,82,75,4681,4681,19,12,4681};


static inline int PSE_decode(Card* hand,EquivClass v, pet_card* out)
{
  int rank=PSE_ranktran(PSE_rank(v));
  int card=0;
  if (out){
    Card h[PSEHAND];
    uint16_t reps = rank_reptable[rank];
    memcpy(h,hand,sizeof(h));
    
    if (rank==rStraight||rank==rStraightFlush){
      int val=HandVal_TOP_CARD(v);
      for (reps=5;reps-->0;){
        out[card++]=pull_card_from_hand(val,h);
        if (--val<0) val=12;
      }
      reps=0;
    }

    for(;reps&7;reps--) { 
      out[card++]=pull_card_from_hand(HandVal_TOP_CARD(v),h);
    }
    for(reps>>=3;reps&7;reps--) 
      out[card++]=pull_card_from_hand(HandVal_SECOND_CARD(v),h);
    for(reps>>=3;reps&7;reps--) 
      out[card++]=pull_card_from_hand(HandVal_THIRD_CARD(v),h);
    for(reps>>=3;reps&7;reps--) 
      out[card++]=pull_card_from_hand(HandVal_FOURTH_CARD(v),h);
    for(reps>>=3;reps&7;reps--) 
      out[card++]=pull_card_from_hand(HandVal_FIFTH_CARD(v),h);
  }
  return rank;
}
#define PSE_DECODES_CARDS 1   //True if decode fills `out` with cards
 
