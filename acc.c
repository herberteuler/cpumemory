/* Structure definition and basic idea from the paper /What Every
   Programmer Should Know About Memory/ by Ulrich Drepper, section
   3.3.2.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rdtsc.h"

struct l {
  struct l *n;
  long int pad[ACC_NPAD];
};

int
main (int argc, char *argv[])
{
  int i;
  struct l *list;
  unsigned long long before, after, diff;
  struct l *p;
  int working_set_size, N;

  working_set_size = atoi (argv[1]);
  N = working_set_size / sizeof (struct l);
  list = (struct l *) calloc (N + 1, sizeof (struct l));
  for (i = 0; i < N; i++)
    list[i].n = &list[i + 1];

  p = list;
  before = rdtsc ();
  while (p->n != NULL)
    p = p->n;
  after = rdtsc ();
  diff = after - before;
  printf ("cpu cycles: %ld\t%ld\n", diff, diff / N);

  return 0;
}
