# CactusKev Evaluator
## KEV

Source: http://suffecool.net/poker/evaluator.html


- Card Representation: 32 bit: `...AKQJT98765432CDHSrrrrxxpppppp`  
  r = rank[0..12],p= prime (see below).
- Hand Representation: 7 Cards
- Hand Value: 1...7462 , 1 is best.


  A five-card evaluator. Introduced the idea of equivalency classes. Kev's concept was to find a fast way to map each set of cards to the equivalent value. He does this by assigning each card rank a prime number p: '2' is 2, '3' is 3, '4' is 5, upto 'A' which is 41.   By multiplying each card's prime together you get a unique number. The largest possible product is `41*41*41*41*37 = 104,553,157`.  You could implement a 104 million entry array and store the equivalence value directly, but that doesn't do nice things to your cache. It's also fairly sparse, so a lot of the space would be wasted. Instead, he does a binary search on a table of products, and uses the index of the match to lookup the value.
This scheme can not detect flushes, so part of the card representation is a bit for the suit, and a bit for each rank. If all five cards have the same suit bit set, it's a flush, and the 13 rank bits are used as a lookup into a 'flushes' table'.  All the rest of the possible hand classes can be found by the product of primes scheme, but Kev makes it faster by using the 13 rank bits as a lookup into a 'unique5' table which returns the hand class if all five cards are different.  
Unfortunately, this evaluator does not scale well to a 7 card hand (the largest product becomes 143,133,271,933 and you can now have a flush with more than 1 suit in your hand).  So it evaluates 7 card hands by running the 5 card evaluator on the 21 possible permutations of 5 cards.  This drops it to near the bottom of the speed test.
