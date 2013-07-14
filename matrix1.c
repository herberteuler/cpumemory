#include <stdlib.h>
#include <stdio.h>
#include <emmintrin.h>
#include "rdtsc.h"
#include "matrix.h"

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
      for (k = 0; k < N; k++)
        res[i][j] += mul1[i][k] * mul2[k][j];

  after = rdtsc ();
  printf ("cpu cycles: %ld\n", after - before);

#ifdef CHECK_RESULT
  printf ("%.0f\n", sum_matrix (res));
#endif

  return 0;
}
