# The Test Framework

## Framework Types

The framework defines two types: 

-   `pet_card`: an enum representing a card. The order is `0 = 2C, 1 = 3C, ..., 13 = 2D, ... , 51 = AS`.
-   `pet_rank`: an enum representing the hand rank: `1 = high card, 2 = pair, ..., 9 = StraightFlush`.  

## Evaluator Methods and Types

The Evaluators under test must implement the following methods, which the framework will call in the listed order.  It must also define the **`Bolded`** types.
	  
1. Do any one-time setup (loading files, creating tables, etc) with:

    void PET_init(void);  

2. Create 52 Cards to fill the deck with:

    Card PET_makecard(pet_card); 

**`Card`** is defined by the evaluator as it's most efficient card representation.

3.  Add Cards to the Hand with:

    void XXX_addcard(Hand, Card); 

**`Hand`** is defined as an array of `Card`s of size `PETHAND`. The evaluator defines PETHAND. The test harness allocates the memory. The evaluator is free to cast the pointer into a more efficient representation.

4. Run the evaluator to find the [equivalence value](equivalence.md):

    EquivClass XXX_evaluate(Hand); 

The **`EquivClass`** can use any numeric encoding scheme, as long as better hands always get higher numbers.

5. Extract the hand rank with:

    pet_rank XXX_rank(EquivClass); 


6. Or fetch the winning cards into the 5 card `out` array with:
 
    pet_rank XXX_decode(Hand,EquivClass,pet_card* out);


7. Cleanup any initialized resources with:

    void XXX_cleanup();     //frees any resurces from init.



 The framework  
 -HandRank has 10 possible values: StraightFlush through HighCard, plus "Invalid" (Evaluator can, but is not required to detect hands that are impossible with 7 cards from a 51 card deck.)



#### *A note about "equivalency classes".*

 Although there are X possible 5-card hands, there are only Y possible results when determining a winning hand. For example, there are 6 possible ways to have a pair of aces `(AcAd AcAh AcAs AdAh AdAs AhAs)`, but they all count the same when determining the winner.  All four ways to get a royal flush are count the same and have the same equivalency class, as do all N ways of getting a 7 card High.   You can list these classes in order from low to high:

    7 High, with 5,4,3,2
    7 High, with 6,4,3,2
    ...
    Pair Aces with a K Q J, 
    Two Pair 2s and 3s with a 5,
     ...
    Full House Jacks over Aces, 
    Full House Queens over 2s,
    ...
    King high Straight Flush,
    Royal Flush.

Assigning each of these a unique number in an increasing sequence gives an equivalency class for that hand.    

### Terminology and Abbreviations

- Rank (card): The number or face on the card : `2..9TJQKA` 
- Suit       : The card suit: `CDHS`
- Hand       : 7 cards
- Hand Value : A number representing the equivalency class. Can be any 1-to-1 mapping to the 6xxx classes, as long as the higher value is always a better hand.
- Hand Rank  : The 'type' of hand: One Pair, Full House, etc.


