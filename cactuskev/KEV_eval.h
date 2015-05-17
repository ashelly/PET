// PET adaptor for CactusKev's evaluator
// http://www.suffecool.net/poker/evaluator.html
//
// (c) 2015 Adam Shelly (github.com/ashelly)

#include <stdint.h>
#include "../pet_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

#define Card uint32_t
#define EquivClass uint16_t

#define KEVHAND 8

#define KEV_init() (0)
#define KEV_addcard(hand,card) ((hand)[(hand)[7]++]=(card))
#define KEV_evaluate(hand)  eval_7hand(hand)
#define KEV_rank(v) hand_rank(v)
#define KEV_ranktran(r) ((10-(r))%10)

#define KEV_decode(h,v,out)  KEV_ranktran(KEV_rank(v))
#define KEV_DECODES_CARDS 0   //True if decode fills `out` with cards

extern int primes[];
static inline Card KEV_makecard(pet_card c){
  int rank=c%13, suit = 0x8000>>(c/13);
  return primes[rank] | (rank << 8) | suit | (1 << (16+rank));
}



#ifdef __cplusplus
}
#endif

