/* Evaluator selector for PET testbed
   Sets the "Evaluator Under Test"(EUT) and includes the adapter file

   compile with -DTESTXXX to include evaluator xxx.

   (c) 2015 Adam Shelly (github.com/ashelly)

*/


#if TESTNUL
#include "nul_eval.h"
#define EUT NUL   

#elif TESTACE
#include "ace_eval/ACE_eval.h"
#define EUT ACE   

#elif TESTTPT
#include "twoplustwo/TPT_eval.h"
#define EUT TPT

#elif TESTKEV
#include "cactuskev/KEV_eval.h"
#define EUT KEV

#elif TESTHES
#include "showdown/HES_eval.h"
#define EUT HES

#elif TESTBHS
#include "showdown/BHS_eval.h"
#define EUT BHS

#elif TESTPSE
#include "pokersource/PSE_eval.h"
#define EUT PSE

#elif TESTSNZ
#include "senzee/SNZ_eval.h"
#define EUT SNZ

#elif TESTPHK
#include "perfecthash/PHK_eval.h"
#define EUT PHK

#elif TESTHAM
#include "hammer/HAM_eval.h"
#define EUT HAM

/*Copy the following 3 lines, paste above this, and replace 'XXX' and 'newdir' */
#elif TESTXXX
#include "newdir/XXX_eval.h"
#define EUT XXX

#endif

/* These macros transform evaluator calls to PET_method
   to calls to XXX_Method, where XXX is the EvaluatorUnderTest.
*/


#define STRINGIZE(a) #a
#define PET_STR(a)  STRINGIZE(a)
#define PET_CONCAT(a,b) a ## b
#define PET_MAKENAME(a,b) PET_CONCAT(a,b)
#define EUT_NAME(b) PET_MAKENAME(EUT,b)

#define PETHAND EUT_NAME(HAND)
#define PET_init EUT_NAME(_init)
#define PET_makecard EUT_NAME(_makecard)
#define PET_addcard EUT_NAME(_addcard)
#define PET_evaluate EUT_NAME(_evaluate)
#define PET_rank EUT_NAME(_rank)
#define PET_ranktran EUT_NAME(_ranktran)
#define PET_decode EUT_NAME(_decode)
#define PET_DECODES_CARDS EUT_NAME(_DECODES_CARDS)

