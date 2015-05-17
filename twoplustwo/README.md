
# TwoPlusTwo: 
## TPT

Source:  http://archives1.twoplustwo.com/showflat.php?Cat=0&Number=8513906&amp;amp;amp;page=2&fpart=1&vc=1
Author:  various, see source.

- Card Representation: 16 bits : 0=2C,1=2D,..4=3C,...51=AS
- Hand Representation: 7 Cards + a card count  *(see Note)
- Hand Value: 16 bits: RRRRvvvvvvvvvvvv  R=HandRank,v=Value

  This evaluator, developed in an epic discussion on the two-plus-two poker forum, starts with the same basic idea as [cactusKev](../cactuskev/README.md): Let's take a set of unsorted cards, and turn them directly into the equivalency class.  But it does it in a ingenious, yet fairly straightforward way: Assign each card in the deck a value between 1 and 51.  Lookup that card in an 52 entry table. The result is the address of another table. Use the next card as an index, and get yet another table address, and so on, until you get to the 7th card and the 7th table.  The result of the last lookup is the hand value. The tables are actually all concatenated together so the 'address' is really just an offset further into the array.   This is probably the bare minumum of operations you can do.  The only drawback: 129MB of tables.  The amount of memory swapping can cause a speed penalty for some use cases.


* Note: The Hand Representation could theoretically be implemented as a single table pointer that gets updated each time AddCard is called.  I haven't tried this yet.