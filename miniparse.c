//minimal evaluator for PET.
// usage:  echo "AH KH 2D 3D 4D 4C AD" | ./a.out
// returns hand rank and equivalence class
//
// (c) 2015 Adam Shelly (github.com/ashelly)

#include <string.h>
#include <stdio.h>
#include "PET_evaluator.h"
char*S="CDHS23456789TJQKA",b[32],*c;
Card hand[PETHAND]={0};
main(int C){
  PET_init();
  c=gets(&b[0]);
  while (*c){
    int rank=strchr(S,*c++)-S-4;
    int suit=strchr(S,*c++)-S;
    Card card = PET_makecard(rank+suit*13);
    c++;
    PET_addcard(hand,card);
  }
  EquivClass v =PET_evaluate(hand);
  printf("%s\n",pet_rank_str[PET_ranktran(PET_rank(v))]);
  printf("%08x \n",(unsigned)v);
}
