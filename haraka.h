/*
Optimized Implementations for Haraka256 and Haraka512
*/
#ifndef HARAKA_H_
#define HARAKA_H_

#include "immintrin.h"

#define NUMROUNDS 5

#define u64 unsigned long
#define u128 __m128i

u128 rc[40];

#define LOAD(src) _mm_load_si128((u128 *)(src))
#define STORE(dest,src) _mm_storeu_si128((u128 *)(dest),src)

#define AES2(s0, s1, rci) \
  s0 = _mm_aesenc_si128(s0, rc[rci]); \
  s1 = _mm_aesenc_si128(s1, rc[rci + 1]); \
  s0 = _mm_aesenc_si128(s0, rc[rci + 2]); \
  s1 = _mm_aesenc_si128(s1, rc[rci + 3]);

#define AES2_4x(s0, s1, s2, s3, rci) \
  AES2(s0[0], s0[1], rci); \
  AES2(s1[0], s1[1], rci); \
  AES2(s2[0], s2[1], rci); \
  AES2(s3[0], s3[1], rci);

#define AES2_8x(s0, s1, s2, s3, s4, s5, s6, s7, rci) \
  AES2_4x(s0, s1, s2, s3, rci); \
  AES2_4x(s4, s5, s6, s7, rci);

#define AES4(s0, s1, s2, s3, rci) \
  s0 = _mm_aesenc_si128(s0, rc[rci]); \
  s1 = _mm_aesenc_si128(s1, rc[rci + 1]); \
  s2 = _mm_aesenc_si128(s2, rc[rci + 2]); \
  s3 = _mm_aesenc_si128(s3, rc[rci + 3]); \
  s0 = _mm_aesenc_si128(s0, rc[rci + 4]); \
  s1 = _mm_aesenc_si128(s1, rc[rci + 5]); \
  s2 = _mm_aesenc_si128(s2, rc[rci + 6]); \
  s3 = _mm_aesenc_si128(s3, rc[rci + 7]);

#define AES8(s0, s1, s2, s3, s4, s5, s6, s7, rci) \
  s0 = _mm_aesenc_si128(s0, rc[rci]); \
  s1 = _mm_aesenc_si128(s1, rc[rci + 1]); \
  s2 = _mm_aesenc_si128(s2, rc[rci + 2]); \
  s3 = _mm_aesenc_si128(s3, rc[rci + 3]); \
  s4 = _mm_aesenc_si128(s4, rc[rci + 4]); \
  s5 = _mm_aesenc_si128(s5, rc[rci + 5]); \
  s6 = _mm_aesenc_si128(s6, rc[rci + 6]); \
  s7 = _mm_aesenc_si128(s7, rc[rci + 7]); \
  s0 = _mm_aesenc_si128(s0, rc[rci + 8]); \
  s1 = _mm_aesenc_si128(s1, rc[rci + 9]); \
  s2 = _mm_aesenc_si128(s2, rc[rci + 10]); \
  s3 = _mm_aesenc_si128(s3, rc[rci + 11]); \
  s4 = _mm_aesenc_si128(s0, rc[rci + 12]); \
  s5 = _mm_aesenc_si128(s1, rc[rci + 13]); \
  s6 = _mm_aesenc_si128(s2, rc[rci + 14]); \
  s7 = _mm_aesenc_si128(s3, rc[rci + 15]);


#define AES4_4x(s0, s1, s2, s3, rci) \
  AES4(s0[0], s0[1], s0[2], s0[3], rci); \
  AES4(s1[0], s1[1], s1[2], s1[3], rci); \
  AES4(s2[0], s2[1], s2[2], s2[3], rci); \
  AES4(s3[0], s3[1], s3[2], s3[3], rci);

#define AES4_8x(s0, s1, s2, s3, s4, s5, s6, s7, rci) \
  AES4_4x(s0, s1, s2, s3, rci); \
  AES4_4x(s4, s5, s6, s7, rci);

#define MIX2(s0, s1) \
  tmp = _mm_unpacklo_epi32(s0, s1); \
  s1 = _mm_unpackhi_epi32(s0, s1); \
  s0 = tmp;

#define MIX4(s0, s1, s2, s3) \
  tmp  = _mm_unpacklo_epi32(s0, s1); \
  s0 = _mm_unpackhi_epi32(s0, s1); \
  s1 = _mm_unpacklo_epi32(s2, s3); \
  s2 = _mm_unpackhi_epi32(s2, s3); \
  s3 = _mm_unpacklo_epi32(s0, s2); \
  s0 = _mm_unpackhi_epi32(s0, s2); \
  s2 = _mm_unpackhi_epi32(s1, tmp); \
  s1 = _mm_unpacklo_epi32(s1, tmp);

#define MIX8(s0, s1, s2, s3, s4, s5, s6, s7) \
  tmp0  = _mm_unpacklo_epi16(s0, s1); \
  s0 = _mm_unpackhi_epi16(s0, s1); \
  tmp1  = _mm_unpacklo_epi16(s2, s3); \
  s2  = _mm_unpackhi_epi16(s2, s3); \
  tmp2  = _mm_unpacklo_epi16(s4, s5); \
  s4 = _mm_unpackhi_epi16(s4, s5); \
  tmp3  = _mm_unpacklo_epi16(s6, s7); \
  s6  = _mm_unpackhi_epi16(s6, s7); \
  s1  = _mm_unpacklo_epi16(tmp0, tmp1); \
  tmp0 = _mm_unpackhi_epi16(tmp0, tmp1); \
  s3  = _mm_unpacklo_epi16(s0, s2); \
  tmp1  = _mm_unpackhi_epi16(s0, s2); \
  s5  = _mm_unpacklo_epi16(tmp2, tmp3); \
  tmp2 = _mm_unpackhi_epi16(tmp2, tmp3); \
  s7  = _mm_unpacklo_epi16(s4, s6); \
  tmp3  = _mm_unpackhi_epi16(s4, s6); \
  s0 = _mm_unpacklo_epi16(s1, s5); \
  s1 = _mm_unpackhi_epi16(s1, s5); \
  s4 = _mm_unpacklo_epi16(s3, s7); \
  s5 = _mm_unpackhi_epi16(s3, s7); \
  s2 = _mm_unpacklo_epi16(tmp0, tmp2); \
  s3 = _mm_unpackhi_epi16(tmp0, tmp2); \
  s6 = _mm_unpacklo_epi16(tmp1, tmp3); \
  s7 = _mm_unpackhi_epi16(tmp1, tmp3);


#define TRUNCSTORE(out, s0, s1, s2, s3) \
  *(u64*)(out) = (u64*)(s0)[1]; \
  *(u64*)(out + 8) = (u64*)(s1)[1]; \
  *(u64*)(out + 16) = (u64*)(s2)[0]; \
  *(u64*)(out + 24) = (u64*)(s3)[0];

#define TRUNCSTORE4(out, s0, s1, s2, s3, s4, s5, s6, s7) \
  *(u64*)(out) = (u64*)(s0)[1]; \
  *(u64*)(out + 4) = (u64*)(s1)[1]; \
  *(u64*)(out + 8) = (u64*)(s2)[0]; \
  *(u64*)(out + 12) = (u64*)(s3)[0]; \
  *(u64*)(out + 16) = (u64*)(s4)[1]; \
  *(u64*)(out + 20) = (u64*)(s5)[1]; \
  *(u64*)(out + 24) = (u64*)(s6)[0]; \
  *(u64*)(out + 28) = (u64*)(s7)[0]; \

void load_constants();
void test_implementations();

void haraka256(unsigned char *out, const unsigned char *in);
void haraka256_4x(unsigned char *out, const unsigned char *in);
void haraka256_8x(unsigned char *out, const unsigned char *in);

void haraka512(unsigned char *out, const unsigned char *in);
void haraka512_4x(unsigned char *out, const unsigned char *in);
void haraka512_8x(unsigned char *out, const unsigned char *in);

void haraka1024(unsigned char *out, const unsigned char *in);
void haraka1024_split(unsigned char *out, const unsigned char *in);

#endif

