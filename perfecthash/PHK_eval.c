// PET adaptor for Paul Senzee's Perfect Hash optimization of CactusKev's evaluator
// http://www.suffecool.net/poker/evaluator.html
// http://www.paulsenzee.com/2006/06/some-perfect-hash.html
//
// adaptor (c) 2015 Adam Shelly (github.com/ashelly)

#include "PHK_eval.h"

#ifdef __cplusplus
extern "C" {
#endif


extern int perm7[21][5];
extern int eval_5hand_fast(int c1, int c2, int c3, int c4, int c5);

// This is a non-optimized method of determining the
// best five-card hand possible out of seven cards.
//
short
eval_7hand_fast( int *hand )
{
    int i, j, q, best = 9999, subhand[5];

	for ( i = 0; i < 21; i++ )
	{
		q = eval_5hand_fast( hand[perm7[i][0]],
                         hand[perm7[i][1]],
                         hand[perm7[i][2]],
                         hand[perm7[i][3]],
                         hand[perm7[i][4]]);
		if ( q < best )
			best = q;
	}
	return( best );
}

