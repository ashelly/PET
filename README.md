Poker Evaluator Testbed 
==================

##PET: A Roundup and Speed Comparison of Seven Card Poker Hand Evaluators

---------------------------------------------

##What's This?
A open test framework and speed comparison of seven card poker hand evaluators in C and C++.  Measuring the state-of-the art in open-source hand evaluators.  Inspired by James Devlin's [apparently defunct](http://www.codingthewheel.com/archives/poker-hand-evaluator-roundup)
 five card roundup at [CodingTheWheel](https://web.archive.org/web/20140717015339/http://codingthewheel.com/archives/poker-hand-evaluator-roundup/). 


##What do I do with it?

1. [View existing results](wiki/results)

      ![Sample Results](https://cloud.githubusercontent.com/assets/3831873/7672694/25aff802-fcca-11e4-8fb9-9cfe26a323ea.png "Example")

2. [Contribute test results from your machine](howtoruntests.md)

3. [Add more evaluators](howtoaddevaluators.md)

4. Create more test scenarios. 


##How does it work?

The framework provides a C adaptor for each evaluator to give it a uniform interface.  Each Evaluator Under Test (EUT) is assigned a unique 3 letter abbreviation,  and implements the api defined in `PET_evaluator.h`. A set of macros in that header translates the API names to the evaluator's names so that we can use the same test harness for all of them.  See Interface.md for more details


It runs each evaluator through two tests, and times the performance for:

- Enumerating every possible 7 card hand.
 - This test includes the cost of adding cards to the hand.
- Enumerating lots (50,000,000 by default) of random hands.
 - This one creates the hands and calls `addcard` outside the timing loop.

There is a script to collect and plot the results. `python plot.py trials`


## Evaluators Tested:

- [CactusKev](cactuskev/README.md)
- [TwoPlusTwo](twoplustwo/README.md)
- [Paul Senzee's 7-Card](senzee/README.md)
- [Steve Brecher's Holdem Showdown](showdown/README.md)
- [PokerSource](pokersource/README.md)
- [Ace Eval](ace_eval/README.md)
- [Moritz Hammer](hammer/README.md)
- [PerfectHash for CactusKev](perfecthash/README.md)

## Coming In The Future
- [SpecialK](specialk/README.md)
- [PokerStove](pokerstove/README.md)


### Licence
The PET code is open source, available under the terms of the MIT License (see LICENSE).  Individual evaluators are licenced under their original terms, see README files in each subidrectory.

