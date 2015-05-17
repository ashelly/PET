# Paul Senzee's Perfect Hash Optimization of CactusKev's Evaluator
## PHK

Source : http://www.paulsenzee.com/2006/06/some-perfect-hash.html

- Card Representation: 32 bit: `...AKQJT98765432CDHSrrrrxxpppppp`  
  r = rank[0..12],p= prime (see below).
- Hand Representation: 7 Cards
- Hand Value: 1...6xxx , 1 is best.
  (Same as CactusKev).


  Paul took the CactusKev evaluator and found a way to get rid of the binary search step at the end. He takes the product of the primes, and runs it through a perfect hash, which maps each of the significant values in the 100 million value range to a unique value in a 6K range. Looking up the hashed value gives the equivalancy class directly.   He claims a 2.7x speedup over the original.  However, this still suffers from its inability to do 7 card hands directly; it also has to iterate over the 21 possible combinations of 5 cards.


