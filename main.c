/*
Timing code for optimized implementation of Haraka.
*/

#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "haraka.h"
#include "timing.h"

typedef void (*hash_function)(unsigned char *out, unsigned long long outlen, const unsigned char *in, unsigned long long inlen);

// Measures how many cycles func requires to process a random input.
double timeit(hash_function func, int inlen, int outlen)
{
  unsigned char *in, *out;
  unsigned long long timer = 0;
  double timings[NUM_TIMINGS];

  int i, j;

  srand(0);
  in = malloc(inlen);
  out = malloc(outlen);

  load_constants();

  for (i = -100; i < NUM_TIMINGS; i++)
  {
    //Get random input
    for (j = 0; j < inlen; j++)
    {
      in[j] = rand() & 0xff;
    }

    timer = startTimer();
    for (j = 0; j < ITERATIONS; j++)
    {
      func(out, outlen, in, inlen);
    }
    timer = endTimer() - timer;

    if (i >= 0 && i < NUM_TIMINGS)
    {
      timings[i] = ((double)timer) / ITERATIONS;
    }
  }

  //Get Median
  qsort(timings, NUM_TIMINGS, sizeof(double), compareDouble);

  free(out);
  free(in);
  return timings[NUM_TIMINGS / 2];
}

int main()
{

  
  // simple constructions
  printf("Haraka-512/NI   64 -> 32    %f cycles \n", timeit(haraka512, 64, 32));
  printf("Haraka-768/NI   96 -> 32    %f cycles \n", timeit(haraka768, 96, 32));
  printf("Haraka-1024/NI 128 -> 32    %f cycles \n", timeit(haraka1024, 128, 32));

  // only the permutation part
  printf("haraka512_perm_NI           %f cycles \n", timeit(haraka512_perm_NI, 64, 64));
  printf("haraka1024_perm_NI          %f cycles \n", timeit(haraka1024_perm_NI, 128, 128));

  // sponge constructions
  printf("Haraka-512_S/NI  128 -> 32  %f cycles \n", timeit(haraka_S_NI, 128, 32));
  printf("Haraka-1024_S/NI 128 -> 32  %f cycles \n", timeit(haraka_1024S, 128, 32));
  printf("Haraka-512_S/NI   96 -> 32  %f cycles \n", timeit(haraka_S_NI, 96, 32));
  printf("Haraka-1024_S/NI  96 -> 32  %f cycles \n", timeit(haraka_1024S, 96, 32));
}
