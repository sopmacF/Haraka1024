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

<<<<<<< HEAD
  for (i = -100; i < NUM_TIMINGS; i++) {
  //for (i = 0; i < NUM_TIMINGS; i++) {
=======
  for (i = -100; i < NUM_TIMINGS; i++)
  {
    //for (i = 0; i < NUM_TIMINGS; i++) {
>>>>>>> 873e57bb4708c4cda7813c668a4730a6a779a8be
    //Get random input
    for (j = 0; j < inlen; j++)
    {
      in[j] = rand() & 0xff;
    }

    timer = startTimer();
<<<<<<< HEAD
    for(j = 0; j < ITERATIONS; j++) {
        func(out, outlen, in, inlen);
=======
    for (j = 0; j < ITERATIONS; j++)
    {
      func(out, outlen, in, inlen);
>>>>>>> 873e57bb4708c4cda7813c668a4730a6a779a8be
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

<<<<<<< HEAD
  printf("Haraka-512/NI   64 -> 32     %f cycles \n", timeit(haraka512, 64, 32));
  printf("Haraka-768/NI   96 -> 32     %f cycles \n", timeit(haraka768, 96, 32));
  printf("Haraka-1024/NI 128 -> 32     %f cycles \n", timeit(haraka1024, 128, 32));
  //printf("Haraka-512          4x: %f cycles \n", timeit(haraka512_4x, 4*64, 4*32));
  //printf("Haraka-512          8x: %f cycles \n", timeit(haraka512_8x, 8*64, 8*32));

  printf("haraka512_perm_NI            %f cycles \n", timeit(haraka512_perm_NI, 64, 64));
  printf("haraka1024_perm_NI           %f cycles \n", timeit(haraka1024_perm_NI, 128, 128));


  //printf("Haraka-1024/AES_NI (3x 512) %f cycles \n", timeit(haraka1024_split, 128, 32));
  //printf("Haraka-1024 sponge/AES_NI   %f cycles \n", timeit(haraka_1024S_NI, 128, 32));
  printf("Haraka-512_S/NI  128 -> 32  %f cycles \n", timeit(haraka_S_NI, 128, 32));
  printf("Haraka-1024_S/NI 128 -> 32  %f cycles \n", timeit(haraka_1024S, 128, 32));
  printf("Haraka-512_S/NI   96 -> 32  %f cycles \n", timeit(haraka_S_NI, 96, 32));
  printf("Haraka-1024_S/NI  96 -> 32  %f cycles \n", timeit(haraka_1024S, 96, 32));



  
=======
  // simple constructions
  printf("Haraka-512/NI   64 -> 32    %f cycles \n", timeit(haraka512, 64, 32));
  printf("Haraka-768/NI   96 -> 32    %f cycles \n", timeit(haraka768, 96, 32));
  printf("Haraka-1024/NI 128 -> 32    %f cycles \n", timeit(haraka1024, 128, 32));

  // only the permutation part
  printf("haraka512_perm_NI           %f cycles \n", timeit(haraka512_perm_NI, 64, 64));
  printf("haraka1024_perm_NI          %f cycles \n", timeit(haraka1024_perm_NI, 128, 128));
>>>>>>> 873e57bb4708c4cda7813c668a4730a6a779a8be

  // sponge constructions
  printf("Haraka-512_S/NI  128 -> 32  %f cycles \n", timeit(haraka_S_NI, 128, 32));
  printf("Haraka-1024_S/NI 128 -> 32  %f cycles \n", timeit(haraka_1024S, 128, 32));
  printf("Haraka-512_S/NI   96 -> 32  %f cycles \n", timeit(haraka_S_NI, 96, 32));
  printf("Haraka-1024_S/NI  96 -> 32  %f cycles \n", timeit(haraka_1024S, 96, 32));
}
