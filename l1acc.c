#include <stdio.h>
#include <string.h>
#include "rdtsc.h"

#define N (CLS / sizeof (int))

int
main (int argc, char *argv[])
{
  int v[N];
  long i, j, iteration = 1000000000;
  long result = 0;
  long before, after, diff;

  memset(v, 0, sizeof v);

  before = rdtsc ();
  for (i = 0; i < iteration; i++)
    for (j = 0; j < N; j++)
      result += v[j];
  after = rdtsc ();

  diff = after - before;
  printf ("%ld\n%ld\n", diff, diff / N / iteration);

  return 0;
}
