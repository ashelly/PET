# Moritz Hammer's Hand Evaluator
## HAM

Source: http://www.pst.ifi.lmu.de/~hammer/poker/handeval.html



- Card Representation: 8 bit: `..ffffss`  
  4 bits for face value, 2 bits for suit. 2 spare
- Hand Representation: 7 Cards
- Hand Value: 1...7462 , 1 is best.



Uses a Directed Acyclic Graph (DAG) to walk through a precomputed graph of  card sets, arriving at the final hand and equivalence class.  Think of it as 7 steps of asking "if I start with this set of cards and add this new card, what set of cards do I have now?"  For example, adding a King to a pair of Jacks arrives at the same place as adding a Jack to a King,Jack.    This is essentially the same technique the TwoPlusTwo evaluator uses, but it only selects of face value, reducing the table size drastically. It uses a separate count of each suit to do flush detection.