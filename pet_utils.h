/* Basic types and Utilities for PET: Poker Evaluator Test

(c) 2014-2015 Adam Shelly (github.com/ashelly)

 */
#ifndef PETUTILS_H
#define PETUTILS_H
#include <stdio.h>

//card values
typedef enum card_t {
  c2C, c3C, c4C, c5C, c6C, c7C, c8C, c9C, cTC, cJC, cQC, cKC, cAC,
  c2D, c3D, c4D, c5D, c6D, c7D, c8D, c9D, cTD, cJD, cQD, cKD, cAD,
  c2H, c3H, c4H, c5H, c6H, c7H, c8H, c9H, cTH, cJH, cQH, cKH, cAH,
  c2S, c3S, c4S, c5S, c6S, c7S, c8S, c9S, cTS, cJS, cQS, cKS, cAS
} pet_card;

static const char* pet_card_str[] = {
  "Two","Three","Four",
  "Five","Six","Seven",
  "Eight","Nine","Ten",
  "Jack","Queen","King","Ace"
};
static const char* pet_suit_str[] = {
  "Clubs","Diamonds","Hearts","Spades"
};

//hand ranks
typedef enum rank_t { 
  rInvalid, 
  rHighCard, rPair, rTwoPair,
  rThreeOfaKind, rStraight, rFlush,
  rFullHouse, rFourOfaKind, rStraightFlush
} pet_rank;

static const char *pet_rank_str[] = {
  "BAD",
  "High Card",
  "One Pair",
  "Two Pair",
  "Three of a Kind",
  "Straight",
  "Flush",
  "Full House",
  "Four of a Kind",
  "Straight Flush"
};


//populates `out` with upto `n` chars describing card `c`
//ex: "Ace of Spades"
//returns !0 if n is not big enough
static inline int pet_card_longname(pet_card c, char* out, int n){
	int r = snprintf(out, n,"%s of %s",pet_card_str[c%13],pet_suit_str[c/13]);
	return  r<0||r>n;
}

//populates `out` with min(2,`n)` chars describing card `c`  
//ex: "AS"
//returns !0 if n is not big enough
static inline int pet_card_name(pet_card c, char* out, int n){
	int r = snprintf(out, n,"%c%c","23456789TJQKA"[c%13],"CDHS"[c/13]);
	return  r<0||r>n;
}

//returns card face value 0=2 .. 13=Ace
static inline short petcard_value(pet_card c) { return c%13;}
//returns card suit: 0..3 = C..S
static inline short petcard_suit(pet_card c) { return c/13;}

#endif
