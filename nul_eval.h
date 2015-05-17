//null evaluator for PET
// non-functional
// used to determine minimum size of evaluation code
//
// (c) 2015 Adam Shelly (github.com/ashelly)

#include "pet_utils.h"

#define Card int
#define EquivClass int


#define NULHAND 1
#define NUL_init() (0)
#define NUL_makecard(i) (i)

#define NUL_addcard(h,c)  ((h)[0]+=(c))
#define NUL_evaluate(h)   (h[0])
#define NUL_rank(v)       ((v)>>24)
#define NUL_ranktran(r)   (((r)<9)?(r):9)
#define NUL_DECODES_CARDS 0

static inline int NUL_decode(Card* h, EquivClass v, pet_card* out)
{
  int rank=NUL_ranktran(NUL_rank(v));
  return rank;
}
