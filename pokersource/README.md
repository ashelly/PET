# Poker Source Evaluator
## PSE

Source: http://gna.org/projects/pokersource/ 

- Card Representation: 64 bits : `...AKQJT98765432` repeated 4 times, once per suit.
- Hand Representation: 52 bits : 7 cards OR'd together.
- Hand Value: 32 bits : `0x0R0CCCCC`. R=HandRank, C=significant card(12=A,0=2) 

This is a big fast open source library.  It uses the same card and hand representation as the Senzee7 evaluator.  It starts similarly to [Brecher's Holdem Showdown](..\showdown\README.md), and uses many of the same techniques: It OR's the suits and counts the number of unique ranks (bits set) using a table lookup, and the number of duplicates (num cards - num ranks). If there are more than 5 different ranks, checks each suit in turn: are there more then 5 cards, and are those 5 a straight. (Straights are also detected with a 13 bit table lookup). As long as there are not more than 2 duplicate cards, then there is no quad or FH and the result is set.
Otherwise, it does a switch on num duplicates: 
			  0 = no pair: the top 5 cards are extracted with a 13 bit lookup.
  		     1 = 1 pair, the pair card is found by XORing the suits with the all-ranks.
			  2 = 2 pair or trips. Use the same XOR trick to find the pairs: if none it's trips, and more bitwise magic finds the right bit.
			  else: AND the suits to detect a quad; else if trips still exist it's a fullhouse. else if flush or straight were not detected above, it must be 2 pair.
For all these hands the top cards are extracted by looking up the top card(s) in a 13 bit table, then XORing with all cards to find the kickers and looking up those too. 
			 
