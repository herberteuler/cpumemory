/* This program is basically the one in the paper /What Every
   Programmer Should Know About Memory/, by Ulrich Drepper, section
   6.2.  See the paper for more information.  */

#ifndef MATRIX_H
#define MATRIX_H

/* for memset */
#include <string.h>

#define N (1000)

double res[N][N] __attribute__ ((aligned (64)));
double mul1[N][N] __attribute__ ((aligned (64)));
double mul2[N][N] __attribute__ ((aligned (64)));

#ifdef CHECK_RESULT
static void
init_matrix (double matrix[N][N])
{
  int i, j;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      matrix[i][j] = (i + 1) * (j + 1);
}

static void
reset_matrix (double matrix[N][N])
{
  memset (matrix, 0, sizeof (double) * N * N);
}

static double
sum_matrix (double matrix[N][N])
{
  int i, j;
  double sum = 0.0;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      sum += matrix[i][j];

  return sum;
}
#endif /* CHECK_RESULT */

#endif /* !MATRIX_H */
