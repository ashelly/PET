//PET adaptor for Paul Senzee's perfect hash optimization of CactusKev's Evaluator
// http://www.suffecool.net/poker/evaluator.html
// http://www.paulsenzee.com/2006/06/some-perfect-hash.html
//
// adaptor (c) 2015 Adam Shelly (github.com/ashelly)

#include <stdint.h>
#include "../pet_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

#define Card uint32_t
#define EquivClass uint16_t

#define PHKHAND 8

#define PHK_init() (0)
#define PHK_addcard(hand,card) ((hand)[(hand)[7]++]=(card))
#define PHK_evaluate(hand)  eval_7hand_fast(hand)
#define PHK_rank(v) hand_rank(v)
#define PHK_ranktran(r) ((10-(r))%10)

#define PHK_decode(h,v,out)  PHK_ranktran(PHK_rank(v))
#define PHK_DECODES_CARDS 0   //True if decode returns cards in `out`

extern int primes[];
static inline Card PHK_makecard(pet_card c){
  int rank=c%13, suit = 0x8000>>(c/13);
  return primes[rank] | (rank << 8) | suit | (1 << (16+rank));
}


#ifdef __cplusplus
}
#endif

