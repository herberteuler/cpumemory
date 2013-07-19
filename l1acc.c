#include <stdio.h>
#include <string.h>
#include "rdtsc.h"

#define N (CLS / sizeof (int))

static inline void
f (int v[N])
{
  int j, k = 4, m = N / k;

  for (j = 0; j < m; j++)
    {
      v[j] + 0;
      v[j+1] + 0;
      v[j+2] + 0;
      v[j+3] + 0;
    }
}

static inline void
g (int v[N])
{
  int j, k = 4, m = N / k;

  for (j = 0; j < m; j++)
    {
      v[j] = 0;
      v[j+1] = 0;
      v[j+2] = 0;
      v[j+3] = 0;
    }
}

int
main (int argc, char *argv[])
{
  int v[N];
  long i, iteration = 100000000;
  long before, after, diff;

  memset(v, 0, sizeof v);

  before = rdtsc ();
  for (i = 0; i < iteration; i++)
    f (v);
  after = rdtsc ();
  diff = after - before;
  printf ("read: %ld\n%ld\n", diff, diff / N / iteration);

  before = rdtsc ();
  for (i = 0; i < iteration; i++)
    g (v);
  after = rdtsc ();
  diff = after - before;
  printf ("write: %ld\n%ld\n", diff, diff / N / iteration);

  return 0;
}
