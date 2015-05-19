// PET adaptor for SpecialK's Poker Evaluator
// https://github.com/kennethshackleton/SpecialKEval.git source
//
// adaptor (c) 2015 Adam Shelly (github.com/ashelly)
#include <stdint.h>
#include "../pet_utils.h"

typedef int Card; 
typedef unsigned short EquivClass; 


#define Card int
#define EquivClass short


#define SPKHAND 8
int SPK_init();
#define SPK_makecard(i) (((51-(i))/13)+((51-(i))%13)*4)
//TODO: speed this up by modifying SevenEval constructor to use same enumeration order as `pet_card

#define SPK_addcard(h,c)  ((h)[++((h)[0])]=(c))
//#define SK7_evaluate(h)   sk7Evaluator->getRankOfSeven(h[1],h[2],h[3],h[4],h[5],h[6])
unsigned short SPK_evaluate(Card* hand);
int SPK_rank(EquivClass v);
#define SPK_ranktran(r)   (r)

#define SPK_decode(h,v,o) (SPK_rank(v))
#define SPK_DECODES_CARDS 0
