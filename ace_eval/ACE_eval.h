// PET adaptor for ACE_eval
// (c) 2015 Adam Shelly (github.com/ashelly)
#include <stdint.h>
#include "../pet_utils.h"

typedef uint32_t Card; 
typedef uint32_t EquivClass; 


#define ACEHAND 5
#define ACE_init() (0)
static inline Card ACE_makecard(int i){return 1<<(2*(i%13)+6)|1<<(i/13);}
static inline void ACE_addcard(Card* h, Card c){ h[c&7]+=c;  h[3]|=c; }
#define ACE_evaluate(h)   E((h))
#define ACE_rank(v)       ((v)>>28)
#define ACE_ranktran(r)   ((r)<8?(r)+1:((r)==9?9:0))


//remove a card of `cardrank` from `hand`, return it.
static inline pet_card PullCardFromHand(int cardrank, Card* hand){
  int suit, rank_mask = ACE_makecard(cardrank)&~0x3F;  //card less suit bits
  for (suit=0;suit<4;suit++) {
    int suit_bit = (1<<suit)&7;
    if (hand[suit_bit]&rank_mask) { //cardrank is in this suit
      hand[suit_bit]&=~rank_mask;
      return cardrank + (suit)*13;
    }
  }
  return -1;
}


//given `hand` with class `v`, fill `out` with the cards that determine value
static inline pet_rank ACE_decode(Card* hand,EquivClass v, pet_card* out)
{
  //reptable is packed 2-bit counters: starting with highest card,
  //  how many more instances of that cardrank to include to represent rank
  pet_rank rank=ACE_ranktran(ACE_rank(v));
  if (out){
    static const uint8_t reptable[]={0,0,1,5,2,0,0,6,3,0};
    Card h[ACEHAND];
    memcpy(h,hand,sizeof(h));
    int bit,i=0;
    int reps = reptable[rank]; 
    for (bit=26;bit-->0 && i<5;) { //extract 5 bits downto 0
      if (v & (1<<bit)) { //card counts toward hand
        for (reps++;3&reps;reps--){
          out[i++]=PullCardFromHand(petcard_value(bit),h);
          if (rank==rStraight||rank==rStraightFlush){
            if (v&(1<<13) && i<5) { //handle low ace 
              out[i++]=PullCardFromHand(cAC,h);
            }
            else {
              v=v>>1; //straights only set the high bit, but we need 5.
            }
          }
        } 
        reps/=4; //next counter
      }
    }
  }
  return rank;
}
#define ACE_DECODES_CARDS 1   //True if decode fills `out` with cards
