// PET adaptor for Steve Brecher's Holdem Showdown
// http://www.brecware.com/Software/software.html
//
// adaptor (c) 2015 Adam Shelly (github.com/ashelly)
 
#include <stdint.h>
#include "source/HandEval.h"
#include "../pet_utils.h"

#define Card Hand_T
typedef uint32_t EquivClass;

#define BHSHAND 1
#define BHS_init() (!Init_Hand_Eval())
#define BHS_makecard(i) ((Card)IndexToMask(i))

#define BHS_addcard(h,c)  ((*h).as64Bits|=(c.as64Bits))
#define BHS_evaluate(h)   Hand_7_Eval(*h)
#define BHS_rank(v)       ((v)>>24)

#define BHS_ranktran(r)   (((r)+1)%10)

static inline int BHS_decode(Card* h,EquivClass v, pet_card* out)
{
  static const uint8_t reptable[]={0,0,1,5,2,0,0,6,3,0};
  int reps,n=0,rank=BHS_ranktran(BHS_rank(v));
  int card;
  //This is do-able but I'm not going to do it tonight.
  return rank;
}
#define BHS_DECODES_CARDS 0   //True if decode fills `out` with cards
