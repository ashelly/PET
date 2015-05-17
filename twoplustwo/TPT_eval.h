// PET adaptor for the TwoPlusTwo 7 card hand evaluator
// http://archives1.twoplustwo.com/showflat.php?Cat=0&Number=8513906&amp;amp;amp;page=2&fpart=1&vc=1
//
// adaptor (c) 2015 Adam Shelly (github.com/ashelly)

#include <stdint.h>

typedef uint16_t Card;
typedef uint16_t EquivClass;
typedef Card*    Hand;

#define TPTHAND 8
extern uint32_t HR[];

int TPT_init(void);
#define TPT_makecard(i) ((Card)(((i)%13)*4)+((i)/13)+1)

#define TPT_addcard(h,c) ((h)[++((h)[0])]=(c))
static inline int TPT_evaluate(Card* pCards)
{
	++pCards;
    int p = HR[53 + *pCards++];
    p = HR[p + *pCards++];
    p = HR[p + *pCards++];
    p = HR[p + *pCards++];
    p = HR[p + *pCards++];
    p = HR[p + *pCards++];
	return HR[p + *pCards++];
}

/* //maybe Hand could just be a pointer into the table. */
/* static inline void TPT_addcard(Hand h,Card c) { */
/*   if (*h==0) *h=53; */
/*   *h=HR[*h+c]; */
/* } */
/* static inline EquivClass TPT_evaluate(Hand h){ */
/*   return *h; */
/* } */


#define TPT_rank(r) ((r)>>12)
#define TPT_ranktran(r) (r)
static inline int TPT_decode(Card* h,EquivClass v, pet_card* out){
  //TODO: deal with non-NULL out
  return TPT_ranktran(TPT_rank(v));
}
#define TPT_DECODES_CARDS 0   //True if decode fills `out` with cards



