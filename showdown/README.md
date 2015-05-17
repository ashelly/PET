
# Steve Brecher's Holdem Showdown: 
## BHS

source:  http://www.stevebrecher.com

- Card Representation: 64 bits : `...AKQJT98765432` repeated 4 times, once per suit.
- Hand Representation: 64 bits : 7 cards OR'd together.
- Hand Value: 32 bits : `0x0R0CCCCC`. R=HandRank, C=significant card(12=A,0=2) 


  This evaluator uses a different bit to represent each card, two 13-bit lookup tables, and a lot of fast bit tricks to do the evaluation. The first step is to separate the hand into suits, then OR each suit together. This will result in a word with between 2 and 7 bits set. Looking up the word in the `nbrOfRanks` table returns that bit count, representing the number of unique card ranks.  Knowing this lets you narrow the remainder of the evaluation.  For example: only 2 unique ranks means you have "quads with trips kicker". so you can AND the suits together to find which card you have 4 of.  3 unique ranks means you have either full house or quads. You can refine further XORing the four suits together, which gives you the bits that are set 1 or 3 times - triples and singletons. And so on.
Once you get over 5 unique ranks  you also need to check for straights and flushes, which is done with the 'mStraitAndOrFlush' macro. It uses the `nbrOfRanks` table again to check the number of cards in each individual suit, calling it a flush if there are 5 or more. It uses a `straightValue` table on either the flush suit or on all cards to find straights. This table returns the high card for any input with 5 bits in a row, or 0 if no straight exists. 
  
This evaluator also contains 5,6, and 8 card evaluators, as well as lowball variants like Razz.
