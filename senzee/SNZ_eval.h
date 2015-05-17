// PET adaptor for the Paul Senzee's 7 hand evaluator
// http://www.paulsenzee.com/2006/06/some-perfect-hash.html
// 
// adaptor (c) 2015 Adam Shelly (github.com/ashelly)

#include <stdint.h>
#include "../pet_utils.h"

#ifndef SNZ_NOTABLES
#include "source/index52c7.h"
#endif

#define Card uint64_t
typedef uint16_t EquivClass;


extern EquivClass* snzTable;
EquivClass* load_table(const char*);

#define SNZHAND 1
static inline int SNZ_init(){
  snzTable=load_table("snz_tables.dat");
  return (snzTable==NULL?-1:0);
}

#define SNZ_makecard(i) (1LL<<(i))

#define SNZ_addcard(h,c)  (*(h)|=(c))
#define SNZ_evaluate(h)   snzTable[index52c7(*(h))]

static inline pet_rank SNZ_rank(EquivClass v){
  if (v > 6185) return(rHighCard);        // 1277 high card
  if (v > 3325) return(rPair);         // 2860 one pair
  if (v > 2467) return(rTwoPair);         //  858 two pair
  if (v > 1609) return(rThreeOfaKind);  //  858 three-kind
  if (v > 1599) return(rStraight);         //   10 straights
  if (v > 322)  return(rFlush);            // 1277 flushes
  if (v > 166)  return(rFullHouse);       //  156 full house
  if (v > 10)   return(rFourOfaKind);   //  156 four-kind
  return(rStraightFlush);                   //   10 straight-flushes
}

#define SNZ_ranktran(r)   (r)

static inline int SNZ_decode(Card* h,EquivClass v, pet_card* out)
{
  int rank=SNZ_ranktran(SNZ_rank(v));
  return rank;
}
#define SNZ_DECODES_CARDS 0   //True if decode fills `out` with cards
