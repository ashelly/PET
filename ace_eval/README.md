# AShelly's Card Evaluator
## ACE

Source: https://github.com/ashelly/ACE_eval.git


- Card Representation: 32 bit: `0a0k0q0j0t09080706050403020..SHDC`  
  one bit for face value, one bit for suit


- Hand Representation: 5 Card reps.  
   One for each suit, plus  one with all card OR'd together.


- Equivalence Class: `RRRR..AKQJT98765432akqjt98765432`.  
 4 bit rank, one bit for each value card, one bit for each kicker.

  Ranks:    
    - 0:"High Card"
    - 1:"One Pair
    - 2""Two Pair",
    - 3:"Three of a Kind",
    - 4:"Straight",
    - 5:"Flush",
    - 6:"Full House",
    - 7:"Four of a Kind",
    - 8:"unused",
    - 9:"Straight Flush" 


A tiny table-less evaluator that uses "sideways addition" to generate counts of each face value in parallel. This allows fast detection of everything but straights and flushes. Flushes are found by inspecting the count of each suit. Straights are found by shifting and AND'ing the value bits 4 times, which clears them unless there are 5 in a row.  As part of detecting the hand rank, the evaluator extracts the bits which determine the value. From there, it is easy to find the remaining kicker cards, and so it is possible to find the hand description (i.e. "Aces over Tens with a King kicker") directly from the returned Equivalence class.  See the README.md for more info.
