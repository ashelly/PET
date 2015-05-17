# Paul Senzee's 7 card evaluator:  
## SNZ

Source: http://www.paulsenzee.com/2007/01/7.html

- Card Representation: 52 bits : `AKQJT98765432` repeated 4 times, once per suit.
- Hand Representation: 52 bits : 7 cards OR'd together.
- Hand Value: ---same as [CactusKev](..\cactuskev\README.md)

This is another evaluator that tries to do a direct loopup into a big table.  It represents the hand as a 52 bit number with exactly 7 bits set.  It provides a hash function `index52c7` which turns that into a unique value between 1 and ~133 million.  The hash function is hard to reverse-engineer: It splits the input into 16 bit words, then does a series of table lookups, additions and multiplications to get the result.  The tables used include a 2^16 entry `_bitcount`, a 2^16 entry partial result, and a set of smaller offset and multiplier tables. 

The final result is now used as an index into a 133 million (265GB) table which contains the Cactus Kev equivalency class. This is actually faster than the two-plus-two evaluator, (likely because it only does 1 lookup in the giant table instead of 7), but it is still slower than most of the less massive evaluators.

*TODO: figure out why 133 million and not 183 million.
