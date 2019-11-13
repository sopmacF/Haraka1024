#include "haraka.h"
#include <stdio.h>

#define HARAKAS_RATE 32
#define HARAKAS_1024_RATE 96 // (1024/8) - 32 (capacity of Haraka_S)
#define SPONGE_B 128            // state size 1024 bits
#define SPONGE_CAPACITY 32      // c
#define SPONGE_RATE 96          // block size = SPONGE_B - SPONGE_CAPACITY
#define SPONGE_OUTPUT_LEN 32    // desired output lenght

static const unsigned char haraka_rc[40][16] = {
    {0x9d, 0x7b, 0x81, 0x75, 0xf0, 0xfe, 0xc5, 0xb2, 0x0a, 0xc0, 0x20, 0xe6, 0x4c, 0x70, 0x84, 0x06},
    {0x17, 0xf7, 0x08, 0x2f, 0xa4, 0x6b, 0x0f, 0x64, 0x6b, 0xa0, 0xf3, 0x88, 0xe1, 0xb4, 0x66, 0x8b},
    {0x14, 0x91, 0x02, 0x9f, 0x60, 0x9d, 0x02, 0xcf, 0x98, 0x84, 0xf2, 0x53, 0x2d, 0xde, 0x02, 0x34},
    {0x79, 0x4f, 0x5b, 0xfd, 0xaf, 0xbc, 0xf3, 0xbb, 0x08, 0x4f, 0x7b, 0x2e, 0xe6, 0xea, 0xd6, 0x0e},
    {0x44, 0x70, 0x39, 0xbe, 0x1c, 0xcd, 0xee, 0x79, 0x8b, 0x44, 0x72, 0x48, 0xcb, 0xb0, 0xcf, 0xcb},
    {0x7b, 0x05, 0x8a, 0x2b, 0xed, 0x35, 0x53, 0x8d, 0xb7, 0x32, 0x90, 0x6e, 0xee, 0xcd, 0xea, 0x7e},
    {0x1b, 0xef, 0x4f, 0xda, 0x61, 0x27, 0x41, 0xe2, 0xd0, 0x7c, 0x2e, 0x5e, 0x43, 0x8f, 0xc2, 0x67},
    {0x3b, 0x0b, 0xc7, 0x1f, 0xe2, 0xfd, 0x5f, 0x67, 0x07, 0xcc, 0xca, 0xaf, 0xb0, 0xd9, 0x24, 0x29},
    {0xee, 0x65, 0xd4, 0xb9, 0xca, 0x8f, 0xdb, 0xec, 0xe9, 0x7f, 0x86, 0xe6, 0xf1, 0x63, 0x4d, 0xab},
    {0x33, 0x7e, 0x03, 0xad, 0x4f, 0x40, 0x2a, 0x5b, 0x64, 0xcd, 0xb7, 0xd4, 0x84, 0xbf, 0x30, 0x1c},
    {0x00, 0x98, 0xf6, 0x8d, 0x2e, 0x8b, 0x02, 0x69, 0xbf, 0x23, 0x17, 0x94, 0xb9, 0x0b, 0xcc, 0xb2},
    {0x8a, 0x2d, 0x9d, 0x5c, 0xc8, 0x9e, 0xaa, 0x4a, 0x72, 0x55, 0x6f, 0xde, 0xa6, 0x78, 0x04, 0xfa},
    {0xd4, 0x9f, 0x12, 0x29, 0x2e, 0x4f, 0xfa, 0x0e, 0x12, 0x2a, 0x77, 0x6b, 0x2b, 0x9f, 0xb4, 0xdf},
    {0xee, 0x12, 0x6a, 0xbb, 0xae, 0x11, 0xd6, 0x32, 0x36, 0xa2, 0x49, 0xf4, 0x44, 0x03, 0xa1, 0x1e},
    {0xa6, 0xec, 0xa8, 0x9c, 0xc9, 0x00, 0x96, 0x5f, 0x84, 0x00, 0x05, 0x4b, 0x88, 0x49, 0x04, 0xaf},
    {0xec, 0x93, 0xe5, 0x27, 0xe3, 0xc7, 0xa2, 0x78, 0x4f, 0x9c, 0x19, 0x9d, 0xd8, 0x5e, 0x02, 0x21},
    {0x73, 0x01, 0xd4, 0x82, 0xcd, 0x2e, 0x28, 0xb9, 0xb7, 0xc9, 0x59, 0xa7, 0xf8, 0xaa, 0x3a, 0xbf},
    {0x6b, 0x7d, 0x30, 0x10, 0xd9, 0xef, 0xf2, 0x37, 0x17, 0xb0, 0x86, 0x61, 0x0d, 0x70, 0x60, 0x62},
    {0xc6, 0x9a, 0xfc, 0xf6, 0x53, 0x91, 0xc2, 0x81, 0x43, 0x04, 0x30, 0x21, 0xc2, 0x45, 0xca, 0x5a},
    {0x3a, 0x94, 0xd1, 0x36, 0xe8, 0x92, 0xaf, 0x2c, 0xbb, 0x68, 0x6b, 0x22, 0x3c, 0x97, 0x23, 0x92},
    {0xb4, 0x71, 0x10, 0xe5, 0x58, 0xb9, 0xba, 0x6c, 0xeb, 0x86, 0x58, 0x22, 0x38, 0x92, 0xbf, 0xd3},
    {0x8d, 0x12, 0xe1, 0x24, 0xdd, 0xfd, 0x3d, 0x93, 0x77, 0xc6, 0xf0, 0xae, 0xe5, 0x3c, 0x86, 0xdb},
    {0xb1, 0x12, 0x22, 0xcb, 0xe3, 0x8d, 0xe4, 0x83, 0x9c, 0xa0, 0xeb, 0xff, 0x68, 0x62, 0x60, 0xbb},
    {0x7d, 0xf7, 0x2b, 0xc7, 0x4e, 0x1a, 0xb9, 0x2d, 0x9c, 0xd1, 0xe4, 0xe2, 0xdc, 0xd3, 0x4b, 0x73},
    {0x4e, 0x92, 0xb3, 0x2c, 0xc4, 0x15, 0x14, 0x4b, 0x43, 0x1b, 0x30, 0x61, 0xc3, 0x47, 0xbb, 0x43},
    {0x99, 0x68, 0xeb, 0x16, 0xdd, 0x31, 0xb2, 0x03, 0xf6, 0xef, 0x07, 0xe7, 0xa8, 0x75, 0xa7, 0xdb},
    {0x2c, 0x47, 0xca, 0x7e, 0x02, 0x23, 0x5e, 0x8e, 0x77, 0x59, 0x75, 0x3c, 0x4b, 0x61, 0xf3, 0x6d},
    {0xf9, 0x17, 0x86, 0xb8, 0xb9, 0xe5, 0x1b, 0x6d, 0x77, 0x7d, 0xde, 0xd6, 0x17, 0x5a, 0xa7, 0xcd},
    {0x5d, 0xee, 0x46, 0xa9, 0x9d, 0x06, 0x6c, 0x9d, 0xaa, 0xe9, 0xa8, 0x6b, 0xf0, 0x43, 0x6b, 0xec},
    {0xc1, 0x27, 0xf3, 0x3b, 0x59, 0x11, 0x53, 0xa2, 0x2b, 0x33, 0x57, 0xf9, 0x50, 0x69, 0x1e, 0xcb},
    {0xd9, 0xd0, 0x0e, 0x60, 0x53, 0x03, 0xed, 0xe4, 0x9c, 0x61, 0xda, 0x00, 0x75, 0x0c, 0xee, 0x2c},
    {0x50, 0xa3, 0xa4, 0x63, 0xbc, 0xba, 0xbb, 0x80, 0xab, 0x0c, 0xe9, 0x96, 0xa1, 0xa5, 0xb1, 0xf0},
    {0x39, 0xca, 0x8d, 0x93, 0x30, 0xde, 0x0d, 0xab, 0x88, 0x29, 0x96, 0x5e, 0x02, 0xb1, 0x3d, 0xae},
    {0x42, 0xb4, 0x75, 0x2e, 0xa8, 0xf3, 0x14, 0x88, 0x0b, 0xa4, 0x54, 0xd5, 0x38, 0x8f, 0xbb, 0x17},
    {0xf6, 0x16, 0x0a, 0x36, 0x79, 0xb7, 0xb6, 0xae, 0xd7, 0x7f, 0x42, 0x5f, 0x5b, 0x8a, 0xbb, 0x34},
    {0xde, 0xaf, 0xba, 0xff, 0x18, 0x59, 0xce, 0x43, 0x38, 0x54, 0xe5, 0xcb, 0x41, 0x52, 0xf6, 0x26},
    {0x78, 0xc9, 0x9e, 0x83, 0xf7, 0x9c, 0xca, 0xa2, 0x6a, 0x02, 0xf3, 0xb9, 0x54, 0x9a, 0xe9, 0x4c},
    {0x35, 0x12, 0x90, 0x22, 0x28, 0x6e, 0xc0, 0x40, 0xbe, 0xf7, 0xdf, 0x1b, 0x1a, 0xa5, 0x51, 0xae},
    {0xcf, 0x59, 0xa6, 0x48, 0x0f, 0xbc, 0x73, 0xc1, 0x2b, 0xd2, 0x7e, 0xba, 0x3c, 0x61, 0xc1, 0xa0},
    {0xa1, 0x9d, 0xc5, 0xe9, 0xfd, 0xbd, 0xd6, 0x4a, 0x88, 0x82, 0x28, 0x02, 0x03, 0xcc, 0x6a, 0x75}
};

static unsigned char rc_[40][16];
static unsigned char rc_sseed[40][16];

static const unsigned char sbox[256] =
{ 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe,
  0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4,
  0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7,
  0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, 0x04, 0xc7, 0x23, 0xc3,
  0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, 0x09,
  0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3,
  0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe,
  0x39, 0x4a, 0x4c, 0x58, 0xcf, 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
  0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92,
  0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c,
  0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19,
  0x73, 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
  0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2,
  0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5,
  0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, 0xba, 0x78, 0x25,
  0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86,
  0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e,
  0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42,
  0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

#define XT(x) (((x) << 1) ^ ((((x) >> 7) & 1) * 0x1b))



// Simulate _mm_aesenc_si128 instructions from AESNI
void aesenc(unsigned char *s, const unsigned char *rk)
{
    unsigned char i, t, u, v[4][4];
    for (i = 0; i < 16; ++i) {
        v[((i / 4) + 4 - (i%4) ) % 4][i % 4] = sbox[s[i]];
    }
    for (i = 0; i < 4; ++i) {
        t = v[i][0];
        u = v[i][0] ^ v[i][1] ^ v[i][2] ^ v[i][3];
        v[i][0] ^= u ^ XT(v[i][0] ^ v[i][1]);
        v[i][1] ^= u ^ XT(v[i][1] ^ v[i][2]);
        v[i][2] ^= u ^ XT(v[i][2] ^ v[i][3]);
        v[i][3] ^= u ^ XT(v[i][3] ^ t);
    }
    for (i = 0; i < 16; ++i) {
        s[i] = v[i / 4][i % 4] ^ rk[i];
    }
}

// Simulate _mm_unpacklo_epi32
void unpacklo32(unsigned char *t, unsigned char *a, unsigned char *b)
{
    unsigned char tmp[16];
    memcpy(tmp, a, 4);
    memcpy(tmp + 4, b, 4);
    memcpy(tmp + 8, a + 4, 4);
    memcpy(tmp + 12, b + 4, 4);
    memcpy(t, tmp, 16);
}

// Simulate _mm_unpackhi_epi32
void unpackhi32(unsigned char *t, unsigned char *a, unsigned char *b)
{
    unsigned char tmp[16];
    memcpy(tmp, a + 8, 4);
    memcpy(tmp + 4, b + 8, 4);
    memcpy(tmp + 8, a + 12, 4);
    memcpy(tmp + 12, b + 12, 4);
    memcpy(t, tmp, 16);
}

void tweak_constants(const unsigned char *pk_seed, const unsigned char *sk_seed,
                     unsigned long long seed_length)
{
    unsigned char buf[40*16];

    /* Use the standard constants to generate tweaked ones. */
    memcpy(rc_, haraka_rc, 40*16);

    /* Constants for sk.seed */
    if (sk_seed != NULL) {
        haraka_S(buf, 40*16, sk_seed, seed_length);
        memcpy(rc_sseed, buf, 40*16);
    }

    /* Constants for pk.seed */
    haraka_S(buf, 40*16, pk_seed, seed_length);
    memcpy(rc_, buf, 40*16);
}

static void haraka_S_absorb(unsigned char *s, unsigned int r,
                            const unsigned char *m, unsigned long long mlen,
                            unsigned char p)
{
    unsigned long long i;
    unsigned char t[r];

    while (mlen >= r) {
        // XOR block to state
        for (i = 0; i < r; ++i) {
            s[i] ^= m[i];
        }
        haraka512_perm(s, s);
        mlen -= r;
        m += r;
    }

    for (i = 0; i < r; ++i) {
        t[i] = 0;
    }
    for (i = 0; i < mlen; ++i) {
        t[i] = m[i];
    }
    t[i] = p;
    t[r - 1] |= 128;
    for (i = 0; i < r; ++i) {
        s[i] ^= t[i];
    }
}

static void haraka_S_absorb_NI(unsigned char *s, unsigned int r,
                            const unsigned char *m, unsigned long long mlen,
                            unsigned char p)
{
    unsigned long long i;
    unsigned char t[r];

    while (mlen >= r) {
        // XOR block to state
        for (i = 0; i < r; ++i) {
            s[i] ^= m[i];
        }
        haraka512_perm_NI(s, HARAKAS_RATE, s, HARAKAS_RATE);
        mlen -= r;
        m += r;
    }

    memset(t, 0, r);

    memcpy(t, m, mlen);

    t[i] = p;
    t[r - 1] |= 128;
    for (i = 0; i < r; ++i) {
        s[i] ^= t[i];
    }
}


static void haraka_S_squeezeblocks(unsigned char *h, unsigned long long nblocks,
                                   unsigned char *s, unsigned int r)
{
    while (nblocks > 0) {
        haraka512_perm(s, s);
        memcpy(h, s, HARAKAS_RATE);
        h += r;
        nblocks--;
    }
}

static void haraka_S_squeezeblocks_NI(unsigned char *h, unsigned long long nblocks,
                                   unsigned char *s, unsigned int r)
{
    while (nblocks > 0) {
        haraka512_perm_NI(s, HARAKAS_RATE, s, HARAKAS_RATE);
        memcpy(h, s, HARAKAS_RATE);
        h += r;
        nblocks--;
    }
}

static void haraka_1024S_absorb_NI(unsigned char *s, unsigned int r,
                            const unsigned char *m, unsigned long long mlen,
                            unsigned char p)
{
    unsigned long long i;
    unsigned char t[r];

    while (mlen >= r) {
        // XOR block to state
        for (i = 0; i < r; ++i) {
            s[i] ^= m[i];
        }
        haraka1024_perm_NI(s, SPONGE_B, s, SPONGE_B);
        mlen -= r;
        m += r;
    }

    memset(t, 0, r);

    memcpy(t, m, mlen);

    t[i] = p;
    t[r - 1] |= 128;

    for (i = 0; i < r; ++i) {
        s[i] ^= t[i];
    }
}

static void haraka_1024S_squeezeblocks_NI(unsigned char *h, unsigned long long nblocks,
                                   unsigned char *s, unsigned int r)
{
    while (nblocks > 0) {
        haraka1024_perm_NI(s, SPONGE_B, s, SPONGE_B);
        memcpy(h, s, r);
        h += r;
        nblocks--;
    }
}

void haraka_1024S(unsigned char *out, unsigned long long outlen,
              const unsigned char *in, unsigned long long inlen)
{
    //unsigned long long i;
    unsigned char s[SPONGE_B];
    unsigned char d[SPONGE_OUTPUT_LEN];

    /*
    for (i = 0; i < SPONGE_B; i++) {
        s[i] = 0;
    }
    */
    memset(s, 0, SPONGE_B);

    haraka_1024S_absorb_NI(s, SPONGE_RATE, in, inlen, 0x1F);

    haraka_1024S_squeezeblocks_NI(out, outlen / SPONGE_RATE, s, SPONGE_RATE);
    out += (outlen / SPONGE_RATE) * SPONGE_RATE;

    if (outlen % SPONGE_RATE) {
        haraka_1024S_squeezeblocks_NI(d, 1, s, SPONGE_OUTPUT_LEN);

        memcpy(out, d, outlen % SPONGE_RATE);
        /*
        for (i = 0; i < outlen % SPONGE_RATE; i++) {
            out[i] = d[i];
        }
        */
    }
}

void haraka_S(unsigned char *out, unsigned long long outlen,
              const unsigned char *in, unsigned long long inlen)
{
    //unsigned long long i;
    unsigned char s[64];
    unsigned char d[32];

    /*
    for (i = 0; i < 64; i++) {
        s[i] = 0;
    }
    */
    memset(s, 0, 64);

    haraka_S_absorb(s, 32, in, inlen, 0x1F);

    haraka_S_squeezeblocks(out, outlen / 32, s, 32);
    out += (outlen / 32) * 32;

    if (outlen % 32) {
        haraka_S_squeezeblocks(d, 1, s, 32);

        memcpy(out, d,  outlen % 32);
        /*
        for (i = 0; i < outlen % 32; i++) {
            out[i] = d[i];
        }
        */
    }
}

void haraka_S_NI(unsigned char *out, unsigned long long outlen,
              const unsigned char *in, unsigned long long inlen)
{
    unsigned long long i;
    unsigned char s[64];
    unsigned char d[32];

    for (i = 0; i < 64; i++) {
        s[i] = 0;
    }
    haraka_S_absorb_NI(s, 32, in, inlen, 0x1F);

    haraka_S_squeezeblocks_NI(out, outlen / 32, s, 32);
    out += (outlen / 32) * 32;

    if (outlen % 32) {
        haraka_S_squeezeblocks_NI(d, 1, s, 32);
        for (i = 0; i < outlen % 32; i++) {
            out[i] = d[i];
        }
    }
}

void haraka512_perm_NI(unsigned char *out, unsigned long long outlen,
              const unsigned char *in, unsigned long long inlen)
{
	  //printf(">>haraka512_perm_NI\n");
      u128 s[4], tmp;

	  s[0] = LOAD(in);
	  s[1] = LOAD(in + 16);
	  s[2] = LOAD(in + 32);
	  s[3] = LOAD(in + 48);

	  AES4(s[0], s[1], s[2], s[3], 0);
	  MIX4(s[0], s[1], s[2], s[3]);

	  AES4(s[0], s[1], s[2], s[3], 8);
	  MIX4(s[0], s[1], s[2], s[3]);

	  AES4(s[0], s[1], s[2], s[3], 16);
	  MIX4(s[0], s[1], s[2], s[3]);

	  AES4(s[0], s[1], s[2], s[3], 24);
	  MIX4(s[0], s[1], s[2], s[3]);

	  AES4(s[0], s[1], s[2], s[3], 32);
	  MIX4(s[0], s[1], s[2], s[3]);

	  s[0] = _mm_xor_si128(s[0], LOAD(in));
	  s[1] = _mm_xor_si128(s[1], LOAD(in + 16));
	  s[2] = _mm_xor_si128(s[2], LOAD(in + 32));
	  s[3] = _mm_xor_si128(s[3], LOAD(in + 48));

	  (void) STORE(out,s[0]);
	  (void) STORE(out+16,s[1]);
	  (void) STORE(out+32,s[2]);
	  (void) STORE(out+48,s[3]);


}

void haraka512_perm(unsigned char *out, const unsigned char *in)
{
    int i, j;

    unsigned char s[64], tmp[16];

    memcpy(s, in, 16);
    memcpy(s + 16, in + 16, 16);
    memcpy(s + 32, in + 32, 16);
    memcpy(s + 48, in + 48, 16);

    for (i = 0; i < 5; ++i) {
        // aes round(s)
        for (j = 0; j < 2; ++j) {
            aesenc(s, rc_[4*2*i + 4*j]);
            aesenc(s + 16, rc_[4*2*i + 4*j + 1]);
            aesenc(s + 32, rc_[4*2*i + 4*j + 2]);
            aesenc(s + 48, rc_[4*2*i + 4*j + 3]);
        }

        // mixing
        unpacklo32(tmp, s, s + 16);
        unpackhi32(s, s, s + 16);
        unpacklo32(s + 16, s + 32, s + 48);
        unpackhi32(s + 32, s + 32, s + 48);
        unpacklo32(s + 48, s, s + 32);
        unpackhi32(s, s, s + 32);
        unpackhi32(s + 32, s + 16, tmp);
        unpacklo32(s + 16, s + 16, tmp);
    }

    memcpy(out, s, 64);
}


//################################################

void load_constants() {
  rc[0] = _mm_set_epi32(0x0684704c,0xe620c00a,0xb2c5fef0,0x75817b9d);
  rc[1] = _mm_set_epi32(0x8b66b4e1,0x88f3a06b,0x640f6ba4,0x2f08f717);
  rc[2] = _mm_set_epi32(0x3402de2d,0x53f28498,0xcf029d60,0x9f029114);
  rc[3] = _mm_set_epi32(0x0ed6eae6,0x2e7b4f08,0xbbf3bcaf,0xfd5b4f79);
  rc[4] = _mm_set_epi32(0xcbcfb0cb,0x4872448b,0x79eecd1c,0xbe397044);
  rc[5] = _mm_set_epi32(0x7eeacdee,0x6e9032b7,0x8d5335ed,0x2b8a057b);
  rc[6] = _mm_set_epi32(0x67c28f43,0x5e2e7cd0,0xe2412761,0xda4fef1b);
  rc[7] = _mm_set_epi32(0x2924d9b0,0xafcacc07,0x675ffde2,0x1fc70b3b);
  rc[8] = _mm_set_epi32(0xab4d63f1,0xe6867fe9,0xecdb8fca,0xb9d465ee);
  rc[9] = _mm_set_epi32(0x1c30bf84,0xd4b7cd64,0x5b2a404f,0xad037e33);
  rc[10] = _mm_set_epi32(0xb2cc0bb9,0x941723bf,0x69028b2e,0x8df69800);
  rc[11] = _mm_set_epi32(0xfa0478a6,0xde6f5572,0x4aaa9ec8,0x5c9d2d8a);
  rc[12] = _mm_set_epi32(0xdfb49f2b,0x6b772a12,0x0efa4f2e,0x29129fd4);
  rc[13] = _mm_set_epi32(0x1ea10344,0xf449a236,0x32d611ae,0xbb6a12ee);
  rc[14] = _mm_set_epi32(0xaf044988,0x4b050084,0x5f9600c9,0x9ca8eca6);
  rc[15] = _mm_set_epi32(0x21025ed8,0x9d199c4f,0x78a2c7e3,0x27e593ec);
  rc[16] = _mm_set_epi32(0xbf3aaaf8,0xa759c9b7,0xb9282ecd,0x82d40173);
  rc[17] = _mm_set_epi32(0x6260700d,0x6186b017,0x37f2efd9,0x10307d6b);
  rc[18] = _mm_set_epi32(0x5aca45c2,0x21300443,0x81c29153,0xf6fc9ac6);
  rc[19] = _mm_set_epi32(0x9223973c,0x226b68bb,0x2caf92e8,0x36d1943a);
  rc[20] = _mm_set_epi32(0xd3bf9238,0x225886eb,0x6cbab958,0xe51071b4);
  rc[21] = _mm_set_epi32(0xdb863ce5,0xaef0c677,0x933dfddd,0x24e1128d);
  rc[22] = _mm_set_epi32(0xbb606268,0xffeba09c,0x83e48de3,0xcb2212b1);
  rc[23] = _mm_set_epi32(0x734bd3dc,0xe2e4d19c,0x2db91a4e,0xc72bf77d);
  rc[24] = _mm_set_epi32(0x43bb47c3,0x61301b43,0x4b1415c4,0x2cb3924e);
  rc[25] = _mm_set_epi32(0xdba775a8,0xe707eff6,0x03b231dd,0x16eb6899);
  rc[26] = _mm_set_epi32(0x6df3614b,0x3c755977,0x8e5e2302,0x7eca472c);
  rc[27] = _mm_set_epi32(0xcda75a17,0xd6de7d77,0x6d1be5b9,0xb88617f9);
  rc[28] = _mm_set_epi32(0xec6b43f0,0x6ba8e9aa,0x9d6c069d,0xa946ee5d);
  rc[29] = _mm_set_epi32(0xcb1e6950,0xf957332b,0xa2531159,0x3bf327c1);
  rc[30] = _mm_set_epi32(0x2cee0c75,0x00da619c,0xe4ed0353,0x600ed0d9);
  rc[31] = _mm_set_epi32(0xf0b1a5a1,0x96e90cab,0x80bbbabc,0x63a4a350);
  rc[32] = _mm_set_epi32(0xae3db102,0x5e962988,0xab0dde30,0x938dca39);
  rc[33] = _mm_set_epi32(0x17bb8f38,0xd554a40b,0x8814f3a8,0x2e75b442);
  rc[34] = _mm_set_epi32(0x34bb8a5b,0x5f427fd7,0xaeb6b779,0x360a16f6);
  rc[35] = _mm_set_epi32(0x26f65241,0xcbe55438,0x43ce5918,0xffbaafde);
  rc[36] = _mm_set_epi32(0x4ce99a54,0xb9f3026a,0xa2ca9cf7,0x839ec978);
  rc[37] = _mm_set_epi32(0xae51a51a,0x1bdff7be,0x40c06e28,0x22901235);
  rc[38] = _mm_set_epi32(0xa0c1613c,0xba7ed22b,0xc173bc0f,0x48a659cf);
  rc[39] = _mm_set_epi32(0x756acc03,0x02288288,0x4ad6bdfd,0xe9c59da1);
  rc[40] = _mm_set_epi32(0x2ff37238,0x0de7d31e,0x367e4778,0x848f2ad2);
  rc[41] = _mm_set_epi32(0x08d95c6a,0xcf74be8b,0xee36b135,0xb73bd58f);
  rc[42] = _mm_set_epi32(0x5880f434,0xc9d6ee98,0x66ae1838,0xa3743e4a);
  rc[43] = _mm_set_epi32(0x593023f0,0xaefabd99,0xd0fdf4c7,0x9a9369bd);
  rc[44] = _mm_set_epi32(0x329ae3d1,0xeb606e6f,0xa5cc637b,0x6f1ecb2a);
  rc[45] = _mm_set_epi32(0xe00207eb,0x49e01594,0xa4dc93d6,0xcb7594ab);
  rc[46] = _mm_set_epi32(0x1caa0c4f,0xf751c880,0x942366a6,0x65208ef8);
  rc[47] = _mm_set_epi32(0x02f7f57f,0xdb2dc1dd,0xbd03239f,0xe3e67e4a);
  rc[48] = _mm_set_epi32(0xb3a7acd3,0x27607901,0x12fdb4d7,0x6ec59da1);
  rc[49] = _mm_set_epi32(0x6d012d56,0x86698185,0x403dcfc5,0x3a0ea163);
  rc[50] = _mm_set_epi32(0x390eb3c9,0x5e1f9ff6,0xf3409b27,0xf73a0258);
  rc[51] = _mm_set_epi32(0x2569c3ae,0xcf581a52,0xb3ab648e,0xaa2e4352);
  rc[52] = _mm_set_epi32(0xf3d2eeb8,0xdf07c691,0x7fd1bb0a,0x99ecddf8);
  rc[53] = _mm_set_epi32(0x1f66da6b,0x6ad2ea51,0x600c0545,0xb4bed33d);
  rc[54] = _mm_set_epi32(0x74a27afc,0x60848518,0xcdbdf7ae,0xe24cf7f8);
  rc[55] = _mm_set_epi32(0x523be598,0xd3d558be,0x5506e575,0xb14165e3);
  rc[56] = _mm_set_epi32(0xac02f6c8,0x366d7f43,0x3e5e8352,0x290fbc8f);
  rc[57] = _mm_set_epi32(0x3574342e,0xf4fec873,0x21674c3e,0xb6f0b369);
  rc[58] = _mm_set_epi32(0xe3542348,0xcf29710c,0x02527547,0xe33c8ead);
  rc[59] = _mm_set_epi32(0x23a3cd5f,0x30727c04,0xabe31e1e,0x76d6e51e);
  rc[60] = _mm_set_epi32(0x93004d4a,0x62addb14,0xb1834b16,0x8216dae7);
  rc[61] = _mm_set_epi32(0x64b4181a,0x7f64b068,0xeb578e81,0x184ac2c1);
  rc[62] = _mm_set_epi32(0xa3a05694,0x044a1c0f,0xba0d642f,0x04609c15);
  rc[63] = _mm_set_epi32(0x7c3790ca,0xaad8fb75,0x56b84477,0xdaa7b265);
  rc[64] = _mm_set_epi32(0x531d9161,0xf0bfbaf9,0xd69df86e,0xe3731acd);
  rc[65] = _mm_set_epi32(0xf8c24d97,0x77c009d1,0x06f7fe3c,0x97ff9193);
  rc[66] = _mm_set_epi32(0x46738c52,0xe231e5de,0x7c12e797,0x13fa282f);
  rc[67] = _mm_set_epi32(0x9576b4ad,0x67820e25,0x6b7c2583,0xd8525d8f);
  rc[68] = _mm_set_epi32(0x7e8e64b9,0x386cee2b,0xb42a5b63,0xa5ecb5ad);
  rc[69] = _mm_set_epi32(0x9a28122a,0x73d6e49c,0x09000e88,0x40b3fd43);
  rc[70] = _mm_set_epi32(0xb13dbc04,0x6a828bc9,0x10b733b4,0xa4a6547c);
  rc[71] = _mm_set_epi32(0xa2a202aa,0x47b4ade7,0x533d92c3,0xe6eea97c);
  rc[72] = _mm_set_epi32(0xd016b655,0x7c080028,0x872e6434,0x23ad2814);
  rc[73] = _mm_set_epi32(0xc49fda88,0x87729cbe,0x5acd9452,0xa1b0db1f);
  rc[74] = _mm_set_epi32(0x6af4654c,0xbdc396f5,0xc954cc61,0x772aa124);
  rc[75] = _mm_set_epi32(0x24eb5a10,0x50ca5594,0xfd8d22c7,0x656e3577);
  rc[76] = _mm_set_epi32(0x0931d729,0x216851e0,0x9b866bea,0x0a6c6a48);
  rc[77] = _mm_set_epi32(0x271d2e85,0x1a4e73e5,0x40c88966,0x622dfbce);
  rc[78] = _mm_set_epi32(0x6958e916,0x18678312,0xae97d60c,0xccc95d6a);
  rc[79] = _mm_set_epi32(0xfa04f89c,0x4eadb6d9,0xb5230d67,0x38b8dfed);
}

void test_implementations() {
	  unsigned char *in = (unsigned char *)calloc(64*8, sizeof(unsigned char));
	  unsigned char *out256 = (unsigned char *)calloc(32*8, sizeof(unsigned char));
	  unsigned char *out512 = (unsigned char *)calloc(32*8, sizeof(unsigned char));
	  unsigned char testvector256[32] = {0x80, 0x27, 0xcc, 0xb8, 0x79, 0x49, 0x77, 0x4b,
	                                     0x78, 0xd0, 0x54, 0x5f, 0xb7, 0x2b, 0xf7, 0x0c,
	                                     0x69, 0x5c, 0x2a, 0x09, 0x23, 0xcb, 0xd4, 0x7b,
	                                     0xba, 0x11, 0x59, 0xef, 0xbf, 0x2b, 0x2c, 0x1c};

	 unsigned char testvector512[32] = {0xbe, 0x7f, 0x72, 0x3b, 0x4e, 0x80, 0xa9, 0x98,
	                                    0x13, 0xb2, 0x92, 0x28, 0x7f, 0x30, 0x6f, 0x62,
	                                    0x5a, 0x6d, 0x57, 0x33, 0x1c, 0xae, 0x5f, 0x34,
	                                    0xdd, 0x92, 0x77, 0xb0, 0x94, 0x5b, 0xe2, 0xaa};



	  int i;

	  // Input for testvector
	  for(i = 0; i < 512; i++) {
	    in[i] = i % 64;
	  }

	  load_constants();
	  haraka512_8x(out512, in);

	  // Verify output
	  for(i = 0; i < 32; i++) {
	    if (out512[i % 32] != testvector512[i]) {
	      printf("Error: testvector incorrect.\n");
	      return;
	    }
	  }

	  free(in);
	  free(out256);
	free(out512);
}

void haraka256(unsigned char *out, const unsigned char *in) {
  __m128i s[2], tmp;

  s[0] = LOAD(in);
  s[1] = LOAD(in + 16);

  AES2(s[0], s[1], 0);
  MIX2(s[0], s[1]);

  AES2(s[0], s[1], 4);
  MIX2(s[0], s[1]);

  AES2(s[0], s[1], 8);
  MIX2(s[0], s[1]);

  AES2(s[0], s[1], 12);
  MIX2(s[0], s[1]);

  AES2(s[0], s[1], 16);
  MIX2(s[0], s[1]);

  s[0] = _mm_xor_si128(s[0], LOAD(in));
  s[1] = _mm_xor_si128(s[1], LOAD(in + 16));

  STORE(out, s[0]);
  STORE(out + 16, s[1]);
}

void haraka256_4x(unsigned char *out, const unsigned char *in) {
  __m128i s[4][2], tmp;

  s[0][0] = LOAD(in);
  s[0][1] = LOAD(in + 16);
  s[1][0] = LOAD(in + 32);
  s[1][1] = LOAD(in + 48);
  s[2][0] = LOAD(in + 64);
  s[2][1] = LOAD(in + 80);
  s[3][0] = LOAD(in + 96);
  s[3][1] = LOAD(in + 112);

  // Round 1
  AES2_4x(s[0], s[1], s[2], s[3], 0);

  MIX2(s[0][0], s[0][1]);
  MIX2(s[1][0], s[1][1]);
  MIX2(s[2][0], s[2][1]);
  MIX2(s[3][0], s[3][1]);

  // Round 2
  AES2_4x(s[0], s[1], s[2], s[3], 4);

  MIX2(s[0][0], s[0][1]);
  MIX2(s[1][0], s[1][1]);
  MIX2(s[2][0], s[2][1]);
  MIX2(s[3][0], s[3][1]);

  // Round 3
  AES2_4x(s[0], s[1], s[2], s[3], 8);

  MIX2(s[0][0], s[0][1]);
  MIX2(s[1][0], s[1][1]);
  MIX2(s[2][0], s[2][1]);
  MIX2(s[3][0], s[3][1]);

  // Round 4
  AES2_4x(s[0], s[1], s[2], s[3], 12);

  MIX2(s[0][0], s[0][1]);
  MIX2(s[1][0], s[1][1]);
  MIX2(s[2][0], s[2][1]);
  MIX2(s[3][0], s[3][1]);

  // Round 5
  AES2_4x(s[0], s[1], s[2], s[3], 16);

  MIX2(s[0][0], s[0][1]);
  MIX2(s[1][0], s[1][1]);
  MIX2(s[2][0], s[2][1]);
  MIX2(s[3][0], s[3][1]);

  // Feed Forward
  s[0][0] = _mm_xor_si128(s[0][0], LOAD(in));
  s[0][1] = _mm_xor_si128(s[0][1], LOAD(in + 16));
  s[1][0] = _mm_xor_si128(s[1][0], LOAD(in + 32));
  s[1][1] = _mm_xor_si128(s[1][1], LOAD(in + 48));
  s[2][0] = _mm_xor_si128(s[2][0], LOAD(in + 64));
  s[2][1] = _mm_xor_si128(s[2][1], LOAD(in + 80));
  s[3][0] = _mm_xor_si128(s[3][0], LOAD(in + 96));
  s[3][1] = _mm_xor_si128(s[3][1], LOAD(in + 112));

  STORE(out, s[0][0]);
  STORE(out + 16, s[0][1]);
  STORE(out + 32, s[1][0]);
  STORE(out + 48, s[1][1]);
  STORE(out + 64, s[2][0]);
  STORE(out + 80, s[2][1]);
  STORE(out + 96, s[3][0]);
  STORE(out + 112, s[3][1]);
}

void haraka256_8x(unsigned char *out, const unsigned char *in) {
  // This is faster on Skylake, the code below is faster on Haswell.
  haraka256_4x(out, in);
  haraka256_4x(out + 128, in + 128);
  return;
  // __m128i s[8][2], tmp;
  //
  // int i;
  //
  // s[0][0] = LOAD(in);
  // s[0][1] = LOAD(in + 16);
  // s[1][0] = LOAD(in + 32);
  // s[1][1] = LOAD(in + 48);
  // s[2][0] = LOAD(in + 64);
  // s[2][1] = LOAD(in + 80);
  // s[3][0] = LOAD(in + 96);
  // s[3][1] = LOAD(in + 112);
  // s[4][0] = LOAD(in + 128);
  // s[4][1] = LOAD(in + 144);
  // s[5][0] = LOAD(in + 160);
  // s[5][1] = LOAD(in + 176);
  // s[6][0] = LOAD(in + 192);
  // s[6][1] = LOAD(in + 208);
  // s[7][0] = LOAD(in + 224);
  // s[7][1] = LOAD(in + 240);
  //
  // // Round 1
  // AES2_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 0);
  //
  // MIX2(s[0][0], s[0][1]);
  // MIX2(s[1][0], s[1][1]);
  // MIX2(s[2][0], s[2][1]);
  // MIX2(s[3][0], s[3][1]);
  // MIX2(s[4][0], s[4][1]);
  // MIX2(s[5][0], s[5][1]);
  // MIX2(s[6][0], s[6][1]);
  // MIX2(s[7][0], s[7][1]);
  //
  //
  // // Round 2
  // AES2_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 4);
  //
  // MIX2(s[0][0], s[0][1]);
  // MIX2(s[1][0], s[1][1]);
  // MIX2(s[2][0], s[2][1]);
  // MIX2(s[3][0], s[3][1]);
  // MIX2(s[4][0], s[4][1]);
  // MIX2(s[5][0], s[5][1]);
  // MIX2(s[6][0], s[6][1]);
  // MIX2(s[7][0], s[7][1]);
  //
  // // Round 3
  // AES2_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 8);
  //
  // MIX2(s[0][0], s[0][1]);
  // MIX2(s[1][0], s[1][1]);
  // MIX2(s[2][0], s[2][1]);
  // MIX2(s[3][0], s[3][1]);
  // MIX2(s[4][0], s[4][1]);
  // MIX2(s[5][0], s[5][1]);
  // MIX2(s[6][0], s[6][1]);
  // MIX2(s[7][0], s[7][1]);
  //
  // // Round 4
  // AES2_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 12);
  //
  // MIX2(s[0][0], s[0][1]);
  // MIX2(s[1][0], s[1][1]);
  // MIX2(s[2][0], s[2][1]);
  // MIX2(s[3][0], s[3][1]);
  // MIX2(s[4][0], s[4][1]);
  // MIX2(s[5][0], s[5][1]);
  // MIX2(s[6][0], s[6][1]);
  // MIX2(s[7][0], s[7][1]);
  //
  // // Round 5
  // AES2_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 16);
  //
  // MIX2(s[0][0], s[0][1]);
  // MIX2(s[1][0], s[1][1]);
  // MIX2(s[2][0], s[2][1]);
  // MIX2(s[3][0], s[3][1]);
  // MIX2(s[4][0], s[4][1]);
  // MIX2(s[5][0], s[5][1]);
  // MIX2(s[6][0], s[6][1]);
  // MIX2(s[7][0], s[7][1]);
  //
  // // Feed Forward
  // s[0][0] = _mm_xor_si128(s[0][0], LOAD(in));
  // s[0][1] = _mm_xor_si128(s[0][1], LOAD(in + 16));
  // s[1][0] = _mm_xor_si128(s[1][0], LOAD(in + 32));
  // s[1][1] = _mm_xor_si128(s[1][1], LOAD(in + 48));
  // s[2][0] = _mm_xor_si128(s[2][0], LOAD(in + 64));
  // s[2][1] = _mm_xor_si128(s[2][1], LOAD(in + 80));
  // s[3][0] = _mm_xor_si128(s[3][0], LOAD(in + 96));
  // s[3][1] = _mm_xor_si128(s[3][1], LOAD(in + 112));
  // s[4][0] = _mm_xor_si128(s[4][0], LOAD(in + 128));
  // s[4][1] = _mm_xor_si128(s[4][1], LOAD(in + 144));
  // s[5][0] = _mm_xor_si128(s[5][0], LOAD(in + 160));
  // s[5][1] = _mm_xor_si128(s[5][1], LOAD(in + 176));
  // s[6][0] = _mm_xor_si128(s[6][0], LOAD(in + 192));
  // s[6][1] = _mm_xor_si128(s[6][1], LOAD(in + 208));
  // s[7][0] = _mm_xor_si128(s[7][0], LOAD(in + 224));
  // s[7][1] = _mm_xor_si128(s[7][1], LOAD(in + 240));
  //
  // STORE(out, s[0][0]);
  // STORE(out + 16, s[0][1]);
  // STORE(out + 32, s[1][0]);
  // STORE(out + 48, s[1][1]);
  // STORE(out + 64, s[2][0]);
  // STORE(out + 80, s[2][1]);
  // STORE(out + 96, s[3][0]);
  // STORE(out + 112, s[3][1]);
  // STORE(out + 128, s[4][0]);
  // STORE(out + 144, s[4][1]);
  // STORE(out + 160, s[5][0]);
  // STORE(out + 176, s[5][1]);
  // STORE(out + 192, s[6][0]);
  // STORE(out + 208, s[6][1]);
  // STORE(out + 224, s[7][0]);
  // STORE(out + 240, s[7][1]);
}

//void haraka512(unsigned char *out, const unsigned char *in) 
void haraka512(unsigned char *out, unsigned long long outlen, const unsigned char *in, unsigned long long inlen)
{
  u128 s[4], tmp;

  s[0] = LOAD(in);
  s[1] = LOAD(in + 16);
  s[2] = LOAD(in + 32);
  s[3] = LOAD(in + 48);

  AES4(s[0], s[1], s[2], s[3], 0);
  MIX4(s[0], s[1], s[2], s[3]);

  AES4(s[0], s[1], s[2], s[3], 8);
  MIX4(s[0], s[1], s[2], s[3]);

  AES4(s[0], s[1], s[2], s[3], 16);
  MIX4(s[0], s[1], s[2], s[3]);

  AES4(s[0], s[1], s[2], s[3], 24);
  MIX4(s[0], s[1], s[2], s[3]);

  AES4(s[0], s[1], s[2], s[3], 32);
  MIX4(s[0], s[1], s[2], s[3]);

  s[0] = _mm_xor_si128(s[0], LOAD(in));
  s[1] = _mm_xor_si128(s[1], LOAD(in + 16));
  s[2] = _mm_xor_si128(s[2], LOAD(in + 32));
  s[3] = _mm_xor_si128(s[3], LOAD(in + 48));

  TRUNCSTORE(out, s[0], s[1], s[2], s[3]);
}

/*
void haraka1024_split(unsigned char *out, const unsigned char *in) {
	unsigned char tmp[32];
	unsigned char tmp2[32];
	haraka512(tmp, 32, in, 64);
	haraka512(tmp2, 32, in, 64);
	memcpy(in, tmp, 32*sizeof(unsigned char));
	memcpy(in + 32, tmp2, 32*sizeof(unsigned char));
	haraka512(out, 32, in, 64);
}
*/

void haraka768(unsigned char *out, unsigned long long outlen, const unsigned char *in, unsigned long long inlen)
{
	  u128 s[6], tmp0, tmp1, tmp2;

	  s[0] = LOAD(in);
	  s[1] = LOAD(in + 16);
	  s[2] = LOAD(in + 32);
	  s[3] = LOAD(in + 48);
	  s[4] = LOAD(in + 64);
	  s[5] = LOAD(in + 80);

	  AES6(s[0], s[1], s[2], s[3], s[4], s[5], 0);
	  MIX6(s[0], s[1], s[2], s[3], s[4], s[5]);

	  AES6(s[0], s[1], s[2], s[3], s[4], s[5], 16);
	  MIX6(s[0], s[1], s[2], s[3], s[4], s[5]);

	  AES6(s[0], s[1], s[2], s[3], s[4], s[5], 32);
	  MIX6(s[0], s[1], s[2], s[3], s[4], s[5]);

	  AES6(s[0], s[1], s[2], s[3], s[4], s[5], 48);
	  MIX6(s[0], s[1], s[2], s[3], s[4], s[5]);

	  AES6(s[0], s[1], s[2], s[3], s[4], s[5], 64);
	  MIX6(s[0], s[1], s[2], s[3], s[4], s[5]);

	  s[0] = _mm_xor_si128(s[0], LOAD(in));
	  s[1] = _mm_xor_si128(s[1], LOAD(in + 16));
	  s[2] = _mm_xor_si128(s[2], LOAD(in + 32));
	  s[3] = _mm_xor_si128(s[3], LOAD(in + 48));
	  s[4] = _mm_xor_si128(s[4], LOAD(in + 64));
	  s[5] = _mm_xor_si128(s[5], LOAD(in + 80));

	  TRUNCSTORE3(out, s[0], s[1], s[2], s[3], s[4], s[5]);
}


void haraka1024(unsigned char *out, unsigned long long outlen, const unsigned char *in, unsigned long long inlen)
{
	  u128 s[8], tmp0, tmp1, tmp2, tmp3;

	  s[0] = LOAD(in);
	  s[1] = LOAD(in + 16);
	  s[2] = LOAD(in + 32);
	  s[3] = LOAD(in + 48);
	  s[4] = LOAD(in + 64);
	  s[5] = LOAD(in + 80);
	  s[6] = LOAD(in + 96);
	  s[7] = LOAD(in + 112);

	  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 0);
	  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

	  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 16);
	  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

	  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 32);
	  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

	  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 48);
	  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

	  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 64);
	  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

	  s[0] = _mm_xor_si128(s[0], LOAD(in));
	  s[1] = _mm_xor_si128(s[1], LOAD(in + 16));
	  s[2] = _mm_xor_si128(s[2], LOAD(in + 32));
	  s[3] = _mm_xor_si128(s[3], LOAD(in + 48));
	  s[4] = _mm_xor_si128(s[4], LOAD(in + 64));
	  s[5] = _mm_xor_si128(s[5], LOAD(in + 80));
	  s[6] = _mm_xor_si128(s[6], LOAD(in + 96));
	  s[7] = _mm_xor_si128(s[7], LOAD(in + 112));

	  TRUNCSTORE4(out, s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);
}

void haraka1024_perm_NI(unsigned char *out, unsigned long long outlen, const unsigned char *in, unsigned long long inlen)
{
      //printf(">>haraka1024_perm_NI\n");
      u128 s[8], tmp0, tmp1, tmp2, tmp3;

	  s[0] = LOAD(in);
	  s[1] = LOAD(in + 16);
	  s[2] = LOAD(in + 32);
	  s[3] = LOAD(in + 48);
	  s[4] = LOAD(in + 64);
	  s[5] = LOAD(in + 80);
	  s[6] = LOAD(in + 96);
	  s[7] = LOAD(in + 112);

	  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 0);
	  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

	  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 16);
	  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

	  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 32);
	  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

	  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 48);
	  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

	  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 64);
	  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

	  s[0] = _mm_xor_si128(s[0], LOAD(in));
	  s[1] = _mm_xor_si128(s[1], LOAD(in + 16));
	  s[2] = _mm_xor_si128(s[2], LOAD(in + 32));
	  s[3] = _mm_xor_si128(s[3], LOAD(in + 48));
	  s[4] = _mm_xor_si128(s[4], LOAD(in + 64));
	  s[5] = _mm_xor_si128(s[5], LOAD(in + 80));
	  s[6] = _mm_xor_si128(s[6], LOAD(in + 96));
	  s[7] = _mm_xor_si128(s[7], LOAD(in + 112));

      (void) STORE(out, s[0]);
      (void) STORE(out+16, s[1]);
      (void) STORE(out+32, s[2]);
      (void) STORE(out+48, s[3]);
      (void) STORE(out+64, s[4]);
      (void) STORE(out+80, s[5]);
      (void) STORE(out+96, s[6]);
      (void) STORE(out+112, s[7]);

}


void haraka512_4x(unsigned char *out, const unsigned char *in) {
  u128 s[4][4], tmp;

  s[0][0] = LOAD(in);
  s[0][1] = LOAD(in + 16);
  s[0][2] = LOAD(in + 32);
  s[0][3] = LOAD(in + 48);
  s[1][0] = LOAD(in + 64);
  s[1][1] = LOAD(in + 80);
  s[1][2] = LOAD(in + 96);
  s[1][3] = LOAD(in + 112);
  s[2][0] = LOAD(in + 128);
  s[2][1] = LOAD(in + 144);
  s[2][2] = LOAD(in + 160);
  s[2][3] = LOAD(in + 176);
  s[3][0] = LOAD(in + 192);
  s[3][1] = LOAD(in + 208);
  s[3][2] = LOAD(in + 224);
  s[3][3] = LOAD(in + 240);

  AES4_4x(s[0], s[1], s[2], s[3], 0);
  MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
  MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
  MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
  MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);

  AES4_4x(s[0], s[1], s[2], s[3], 8);
  MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
  MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
  MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
  MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);

  AES4_4x(s[0], s[1], s[2], s[3], 16);
  MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
  MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
  MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
  MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);

  AES4_4x(s[0], s[1], s[2], s[3], 24);
  MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
  MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
  MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
  MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);

  AES4_4x(s[0], s[1], s[2], s[3], 32);
  MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
  MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
  MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
  MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);


  s[0][0] = _mm_xor_si128(s[0][0], LOAD(in));
  s[0][1] = _mm_xor_si128(s[0][1], LOAD(in + 16));
  s[0][2] = _mm_xor_si128(s[0][2], LOAD(in + 32));
  s[0][3] = _mm_xor_si128(s[0][3], LOAD(in + 48));
  s[1][0] = _mm_xor_si128(s[1][0], LOAD(in + 64));
  s[1][1] = _mm_xor_si128(s[1][1], LOAD(in + 80));
  s[1][2] = _mm_xor_si128(s[1][2], LOAD(in + 96));
  s[1][3] = _mm_xor_si128(s[1][3], LOAD(in + 112));
  s[2][0] = _mm_xor_si128(s[2][0], LOAD(in + 128));
  s[2][1] = _mm_xor_si128(s[2][1], LOAD(in + 144));
  s[2][2] = _mm_xor_si128(s[2][2], LOAD(in + 160));
  s[2][3] = _mm_xor_si128(s[2][3], LOAD(in + 176));
  s[3][0] = _mm_xor_si128(s[3][0], LOAD(in + 192));
  s[3][1] = _mm_xor_si128(s[3][1], LOAD(in + 208));
  s[3][2] = _mm_xor_si128(s[3][2], LOAD(in + 224));
  s[3][3] = _mm_xor_si128(s[3][3], LOAD(in + 240));

  TRUNCSTORE(out, s[0][0], s[0][1], s[0][2], s[0][3]);
  TRUNCSTORE(out + 32, s[1][0], s[1][1], s[1][2], s[1][3]);
  TRUNCSTORE(out + 64, s[2][0], s[2][1], s[2][2], s[2][3]);
  TRUNCSTORE(out + 96, s[3][0], s[3][1], s[3][2], s[3][3]);
}

void haraka512_8x(unsigned char *out, const unsigned char *in) {
  // This is faster on Skylake, the code below is faster on Haswell.
  haraka512_4x(out, in);
  haraka512_4x(out + 128, in + 256);

  // u128 s[8][4], tmp;
  //
  // s[0][0] = LOAD(in);
  // s[0][1] = LOAD(in + 16);
  // s[0][2] = LOAD(in + 32);
  // s[0][3] = LOAD(in + 48);
  // s[1][0] = LOAD(in + 64);
  // s[1][1] = LOAD(in + 80);
  // s[1][2] = LOAD(in + 96);
  // s[1][3] = LOAD(in + 112);
  // s[2][0] = LOAD(in + 128);
  // s[2][1] = LOAD(in + 144);
  // s[2][2] = LOAD(in + 160);
  // s[2][3] = LOAD(in + 176);
  // s[3][0] = LOAD(in + 192);
  // s[3][1] = LOAD(in + 208);
  // s[3][2] = LOAD(in + 224);
  // s[3][3] = LOAD(in + 240);
  // s[4][0] = LOAD(in + 256);
  // s[4][1] = LOAD(in + 272);
  // s[4][2] = LOAD(in + 288);
  // s[4][3] = LOAD(in + 304);
  // s[5][0] = LOAD(in + 320);
  // s[5][1] = LOAD(in + 336);
  // s[5][2] = LOAD(in + 352);
  // s[5][3] = LOAD(in + 368);
  // s[6][0] = LOAD(in + 384);
  // s[6][1] = LOAD(in + 400);
  // s[6][2] = LOAD(in + 416);
  // s[6][3] = LOAD(in + 432);
  // s[7][0] = LOAD(in + 448);
  // s[7][1] = LOAD(in + 464);
  // s[7][2] = LOAD(in + 480);
  // s[7][3] = LOAD(in + 496);
  //
  // AES4_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 0);
  // MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
  // MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
  // MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
  // MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);
  // MIX4(s[4][0], s[4][1], s[4][2], s[4][3]);
  // MIX4(s[5][0], s[5][1], s[5][2], s[5][3]);
  // MIX4(s[6][0], s[6][1], s[6][2], s[6][3]);
  // MIX4(s[7][0], s[7][1], s[7][2], s[7][3]);
  //
  // AES4_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 8);
  // MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
  // MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
  // MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
  // MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);
  // MIX4(s[4][0], s[4][1], s[4][2], s[4][3]);
  // MIX4(s[5][0], s[5][1], s[5][2], s[5][3]);
  // MIX4(s[6][0], s[6][1], s[6][2], s[6][3]);
  // MIX4(s[7][0], s[7][1], s[7][2], s[7][3]);
  //
  // AES4_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 16);
  // MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
  // MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
  // MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
  // MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);
  // MIX4(s[4][0], s[4][1], s[4][2], s[4][3]);
  // MIX4(s[5][0], s[5][1], s[5][2], s[5][3]);
  // MIX4(s[6][0], s[6][1], s[6][2], s[6][3]);
  // MIX4(s[7][0], s[7][1], s[7][2], s[7][3]);
  //
  // AES4_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 24);
  // MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
  // MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
  // MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
  // MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);
  // MIX4(s[4][0], s[4][1], s[4][2], s[4][3]);
  // MIX4(s[5][0], s[5][1], s[5][2], s[5][3]);
  // MIX4(s[6][0], s[6][1], s[6][2], s[6][3]);
  // MIX4(s[7][0], s[7][1], s[7][2], s[7][3]);
  //
  // AES4_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 32);
  // MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
  // MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
  // MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
  // MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);
  // MIX4(s[4][0], s[4][1], s[4][2], s[4][3]);
  // MIX4(s[5][0], s[5][1], s[5][2], s[5][3]);
  // MIX4(s[6][0], s[6][1], s[6][2], s[6][3]);
  // MIX4(s[7][0], s[7][1], s[7][2], s[7][3]);
  //
  //
  // s[0][0] = _mm_xor_si128(s[0][0], LOAD(in));
  // s[0][1] = _mm_xor_si128(s[0][1], LOAD(in + 16));
  // s[0][2] = _mm_xor_si128(s[0][2], LOAD(in + 32));
  // s[0][3] = _mm_xor_si128(s[0][3], LOAD(in + 48));
  // s[1][0] = _mm_xor_si128(s[1][0], LOAD(in + 64));
  // s[1][1] = _mm_xor_si128(s[1][1], LOAD(in + 80));
  // s[1][2] = _mm_xor_si128(s[1][2], LOAD(in + 96));
  // s[1][3] = _mm_xor_si128(s[1][3], LOAD(in + 112));
  // s[2][0] = _mm_xor_si128(s[2][0], LOAD(in + 128));
  // s[2][1] = _mm_xor_si128(s[2][1], LOAD(in + 144));
  // s[2][2] = _mm_xor_si128(s[2][2], LOAD(in + 160));
  // s[2][3] = _mm_xor_si128(s[2][3], LOAD(in + 176));
  // s[3][0] = _mm_xor_si128(s[3][0], LOAD(in + 192));
  // s[3][1] = _mm_xor_si128(s[3][1], LOAD(in + 208));
  // s[3][2] = _mm_xor_si128(s[3][2], LOAD(in + 224));
  // s[3][3] = _mm_xor_si128(s[3][3], LOAD(in + 240));
  // s[4][0] = _mm_xor_si128(s[4][0], LOAD(in + 256));
  // s[4][1] = _mm_xor_si128(s[4][1], LOAD(in + 272));
  // s[4][2] = _mm_xor_si128(s[4][2], LOAD(in + 288));
  // s[4][3] = _mm_xor_si128(s[4][3], LOAD(in + 304));
  // s[5][0] = _mm_xor_si128(s[5][0], LOAD(in + 320));
  // s[5][1] = _mm_xor_si128(s[5][1], LOAD(in + 336));
  // s[5][2] = _mm_xor_si128(s[5][2], LOAD(in + 352));
  // s[5][3] = _mm_xor_si128(s[5][3], LOAD(in + 368));
  // s[6][0] = _mm_xor_si128(s[6][0], LOAD(in + 384));
  // s[6][1] = _mm_xor_si128(s[6][1], LOAD(in + 400));
  // s[6][2] = _mm_xor_si128(s[6][2], LOAD(in + 416));
  // s[6][3] = _mm_xor_si128(s[6][3], LOAD(in + 432));
  // s[7][0] = _mm_xor_si128(s[7][0], LOAD(in + 448));
  // s[7][1] = _mm_xor_si128(s[7][1], LOAD(in + 464));
  // s[7][2] = _mm_xor_si128(s[7][2], LOAD(in + 480));
  // s[7][3] = _mm_xor_si128(s[7][3], LOAD(in + 496));
  //
  // TRUNCSTORE(out, s[0][0], s[0][1], s[0][2], s[0][3]);
  // TRUNCSTORE(out + 32, s[1][0], s[1][1], s[1][2], s[1][3]);
  // TRUNCSTORE(out + 64, s[2][0], s[2][1], s[2][2], s[2][3]);
  // TRUNCSTORE(out + 96, s[3][0], s[3][1], s[3][2], s[3][3]);
  // TRUNCSTORE(out + 128, s[4][0], s[4][1], s[4][2], s[4][3]);
  // TRUNCSTORE(out + 160, s[5][0], s[5][1], s[5][2], s[5][3]);
  // TRUNCSTORE(out + 192, s[6][0], s[6][1], s[6][2], s[6][3]);
  // TRUNCSTORE(out + 224, s[7][0], s[7][1], s[7][2], s[7][3]);
}

