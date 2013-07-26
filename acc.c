/* Structure definition and basic idea from the paper /What Every
   Programmer Should Know About Memory/ by Ulrich Drepper, section
   3.3.2.  See the paper for more information.  */

#include <stdlib.h>
#include <string.h>

struct l {
  struct l *n;
  long int pad[ACC_NPAD];
};

void *
prepare (int argc, char *argv[])
{
  size_t working_set_size, N, i;
  struct l *list;

  working_set_size = (size_t) atoi (argv[0]);
  N = working_set_size / sizeof (struct l);
  list = (struct l *) calloc (N, sizeof (struct l));
  for (i = 0; i < N; i++)
    list[i].n = &list[i + 1];

  return list;
}

int
run (int argc, char *argv, void *context)
{
  struct l *p = (struct l *) context;

  while (p->n != NULL)
    p = p->n;
  return 0;
}

int
postrun (int argc, char *argv[], void *context)
{
  return 0;
}
