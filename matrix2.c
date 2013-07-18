/* This program is basically the one in the paper /What Every
   Programmer Should Know About Memory/ by Ulrich Drepper, section
   6.2.  See the paper for more information. */

#include <stdlib.h>
#include <stdio.h>
#include <emmintrin.h>
#include "rdtsc.h"
#include "matrix.h"

double tmp[N][N];

int
main (int argc, char *argv[])
{
  int i, j, k;
  long before, after;

#ifdef CHECK_RESULT
  init_matrix (mul1);
  init_matrix (mul2);
  reset_matrix (res);
#endif

  before = rdtsc ();

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      tmp[i][j] = mul2[j][i];

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      for (k = 0; k < N; k++)
        res[i][j] += mul1[i][k] * tmp[j][k];

  after = rdtsc ();
  printf ("cpu cycles: %ld\n", after - before);

#ifdef CHECK_RESULT
  printf ("%.0f\n", sum_matrix (res));
#endif

  return 0;
}
