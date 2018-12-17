#include "haraka.h"
#include <stdio.h>

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
  unsigned char *in1024 = (unsigned char *)calloc(128*8, sizeof(unsigned char));
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



 unsigned char testvector1024[64] = {0xbe, 0x7f, 0x72, 0x3b, 0x4e, 0x80, 0xa9, 0x98,
                                    0x13, 0xb2, 0x92, 0x28, 0x7f, 0x30, 0x6f, 0x62,
                                    0x5a, 0x6d, 0x57, 0x33, 0x1c, 0xae, 0x5f, 0x34,
                                    0xdd, 0x92, 0x77, 0xb0, 0x94, 0x5b, 0xe2, 0xaa,
									0xbe, 0x7f, 0x72, 0x3b, 0x4e, 0x80, 0xa9, 0x98,
									0x13, 0xb2, 0x92, 0x28, 0x7f, 0x30, 0x6f, 0x62,
									0x5a, 0x6d, 0x57, 0x33, 0x1c, 0xae, 0x5f, 0x34,
									0xdd, 0x92, 0x77, 0xb0, 0x94, 0x5b, 0xe2, 0xaa};


  int i;

  // Input for testvector
  for(i = 0; i < 512; i++) {
    in[i] = i % 64;
  }

  for(i = 0; i < 1024; i++) {
	  in1024[i] = i % 64;
  }


  load_constants();

  haraka1024(out256, in);

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

void haraka512(unsigned char *out, const unsigned char *in) {
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

void haraka1024_split(unsigned char *out, const unsigned char *in) {
	unsigned char tmp[32];
	unsigned char tmp2[32];
	haraka512(tmp, in);
	haraka512(tmp2, in);
	memcpy(in, tmp, 32*sizeof(unsigned char));
	memcpy(in + 32, tmp2, 32*sizeof(unsigned char));
	haraka512(out, in);
}

void haraka1024(unsigned char *out, const unsigned char *in) {
  u128 s[8], tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;

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

  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 8);
  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 16);
  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 24);
  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 32);
  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 48);
  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 64);
  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 80);
  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 96);
  MIX8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);

  AES8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 112);
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

