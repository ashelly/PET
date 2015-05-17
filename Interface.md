# PET Interface

The testbed has the following interface: 
(Replace XXX with the 3-letter abbreviation for an evaluator)

## Concepts:

### Rank:  
  A numeric representation of the following hand ranks:   
    Straight Flush, Four of a Kind, Full House,
  Flush, Straight, Three of a Kind, Two Pair,
  Pair, High Card.  
  

   Enumerated in `pet_utils.h` as `pet_rank`.   An evaluator can use a different representation, as long as it can convert to this enumeration on demand.

### FaceValue:
  2 through 10, Jack, Queen, King, Ace.
### Suit:
  Clubs, Diamonds, Hearts, Spades.  
  


  Each card has a Suit and FaceValue,  enumerated in `pet_utils.h` as `pet_card`;  An evaluator should be able to convert to and from this enumeration.



### Equivalence Class:
  Although there are 2,598,960 possible 5-card hands, there are only 7,462 possible results when determining a winning hand. For example, there are 6 possible ways to have a pair of aces with any given kicker *[AcAd AcAh AcAs AdAh AdAs AhAs]*, but they all count the same when finding the winner. All four ways to get a royal flush are equivalent, and have the same equivalency class, as do all 4080 ways of getting the lowest possible hand *(7-5-4-3-2)*.  You can list these classes in order: Royal Flush, King High Straight Flush,...Full House Queens over 2s, Full House Jacks over Aces, ... Pair Tens with a K 9 8, ... down to 7 Card High, and assign them each a value in descending order.  Then finding winning hands becomes as simple as comparing equivalency values.


## Requirements:

### `typedef`s:
 - `Card`  :  A single card representation. Whatever is most effiicent for the evaluator.
 -  `EquivClass` : Holds the equivalence class of a hand. An evaluator can use any scheme it wishes, as long as a) there are only 7462 possible values, and b) larger values beat smaller ones.

### `#define`:
  - `XXXHAND` : An integer. The `addcard` and `evaluate` will operate on a "Hand" of size `Card[XXXHAND]`. (This size may be more or less than 7 Cards, it should be the most efficient representation for the evaluator).

###  Methods (functions or macros)

 - `int XXXX_init(void);`  //Any one-time setup, return 0 on success
 - `Card XXX_makecard(pet_card c);` //turns an enumeration from 0..51 into internal card representation.
 - `void XXX_addcard(Card*, Card);` //Adds a card to a Hand. Called 7 times.
 - `EquivClass XXX_evaluate(Card*);` //Evaluates hand, returns a Equivalence Class. 
 - `int XXX_rank(EquivClass);`       //returns the hand rank. An internal representation of Rank, must be between 0 and 9 inclusive.
 - `pet_rank XXX_ranktran(int rank);`       //converts internal rank to pet_rank (see pet_utils.h)
 - `pet_rank XXX_decode(Hand, EquivClass, int* out);` //Fills `out` with the 5 winning cards from the hand, returns the rank.
 - `void XXX_cleanup();`     //frees any resurces from init.

