# How to add evaluators.

1. Fork this repository.

2. Pick a 3 letter abbreviation for your evaluator. Use that abbreviation everywhere you see 'xxx' below.

3. Make a subdirectory for your evaluator. (Use a long name, not the 3 letter name). Change to it.
4. Create a `get.sh`. Make it executable.       
   It must contain commands to fetch the evaluator from the web, and place it in a subdirectory named `source`. (Use git clone, wget,...) See existing directories for examples. Test it.  Add `get.sh` to a commit.

5. Create a `XXX_eval.h` This file will map the specifics of your evaluator's implementation to the generic test interface.
  - The file should `#include "..\pet_utils.h`
  - The file must define the following 2 types:
  Card, EquivClass
 - It must #define XXXHAND which contains the count of Card sized objects needed to represent a Hand
 - It must contain these 6 functions/macros. 
    - int XXX_init()
    - Card XXX_makecard(in)
    - void XXX_addcard(Hand,Card)
    - EquivClass XXX_evaluate(Hand)
    - int XXX_rank(EquivClass)
    - pet_rank XXX_ranktran(int)  
See [the Interface document](Interface.md) for more details.  
  Add this file to the commit.

6.  Edit `PET_evaluator.h` to add your code.  This is the file that redirects calls to PET_* to your evaluator.  Just copy and paste the 3 lines starting with `elif TESTXXX`, replacing XXX with your abbreviation.  
Add this file to the commit.

7. Edit the `Makefile`.   Copy an existing entry as an example.  It is important to change "-DTESTXXX=1" and "-oxxx" for your evaluator.  Also add your abbreviation to the "all" line.    
 Run `make all` and ensure your code builds cleanly.  Run ./xxx to ensure it runs without errors.
 Add the makefile to the commit.

8. If there is a data file, Also add a Makefile line to create the file if needed, and to copy it to the root with name xxx_tables.dat.   Make sure the `XXX_init()` function uses this file.

9. See [How To Run Tests](howtoruntests.md) to compare your evaluator to the rest.



