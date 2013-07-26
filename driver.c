#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

extern void *prepare (int, char *[]);
extern int run (int, char *[], void *);
extern int postrun (int, char *[], void *);

int
main (int argc, char *argv[])
{
  int opt;
  size_t i, repeats = 0u;
  void *context;

  while ((opt = getopt (argc, argv, "r:")) != -1)
    switch (opt)
      {
      case 'r':
        repeats = (size_t) atoi (optarg);
        break;
      default:
        fprintf (stderr, "Usage: %s [-r repeats]\n", argv[0]);
        exit (-1);
      }

  argv += optind;
  argc -= optind;

  context = prepare (argc, argv);
  for (i = 0; i < repeats; i++)
    {
      int r;

      r = run (argc, argv, context);
      if (r != 0)
        exit (r);
    }
  return postrun (argc, argv, context);
}
