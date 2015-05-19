
#include "source/SevenEval.h"

static SevenEval const* g_spk_evaluator = new SevenEval();

extern "C" {

#include "SPK_eval.h"

int SPK_init() {
  return 0;
}


unsigned short SPK_evaluate(Card* hand) {
  return g_spk_evaluator->GetRank(hand[1],hand[2],hand[3],hand[4],hand[5],hand[6],hand[7]);
}


int
SPK_rank( EquivClass val )
{
  if (val <= 1277) return(1); ///1); //HIGH_CARD);        // 1277 high card
  if (val <= 4137) return(2); //ONE_PAIR);         // 2860 one pair
  if (val <= 4995) return(3); //TWO_PAIR);         //  858 two pair
  if (val <= 5853) return(4); ///THREE_OF_A_KIND);  //  858 three-kind
  if (val <= 5863) return(5); ///STRAIGHT);         //   10 straights
  if (val <= 7140)  return(6); ///FLUSH);            // 1277 flushes
  if (val <= 7296)  return(7); ///FULL_HOUSE);       //  156 full house
  if (val <= 7452)   return(8); ///FOUR_OF_A_KIND);   //  156 four-kind
  return(9);                  //   10 straight-flushes
}



}
