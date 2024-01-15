/*************************************************************************
* Copyright (C) 2023 Intel Corporation
*
* Licensed under the Apache License,  Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* 	http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law  or agreed  to  in  writing,  software
* distributed under  the License  is  distributed  on  an  "AS IS"  BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the  specific  language  governing  permissions  and
* limitations under the License.
*************************************************************************/
#ifdef MBX_FIPS_MODE

#include <crypto_mb/fips_cert.h>
#include <internal/fips_cert/common.h>
#include <internal/rsa/ifma_rsa_method.h>

#include <crypto_mb/rsa.h>

/* KAT TEST (generated via internal tests) */
/* moduli */
static const int8u moduli[MBX_RSA3K_DATA_BYTE_LEN] = {
  0x05,0x6b,0x8e,0xc4,0x89,0x9d,0x19,0xd4,0x44,0x4b,0x0b,0x32,0xc7,0xbb,0x22,0x05,
  0xa4,0x53,0x33,0x4c,0x60,0xd3,0xcd,0xfb,0xa9,0xae,0xa3,0xba,0x83,0xfe,0xe8,0x67,
  0x56,0x10,0x7c,0x9d,0x89,0xd3,0xb7,0x8b,0x03,0xa7,0x07,0xcb,0x4c,0x4b,0x62,0xa3,
  0x33,0x02,0x5d,0x32,0xd0,0xb3,0xff,0xef,0xa0,0x1a,0x7c,0x48,0xb1,0x4b,0x70,0xe7,
  0xc7,0xdf,0x7c,0xd3,0xad,0x7d,0xf6,0x2f,0xef,0x9b,0xfa,0x63,0x22,0x33,0x2e,0x84,
  0xab,0x93,0x8c,0x11,0x56,0x2a,0xe9,0xb0,0xba,0xcc,0x53,0xbc,0x30,0xd2,0xf2,0xb5,
  0x70,0xc0,0xca,0x5d,0xb7,0xd5,0x9a,0x7d,0xad,0x63,0xfc,0x81,0xc1,0x8e,0x3d,0x7f,
  0x66,0xa0,0x80,0xd5,0x73,0x65,0x15,0x68,0x71,0x3b,0xe3,0xb2,0xa9,0x85,0x82,0x40,
  0x5e,0x90,0x62,0x72,0xa9,0xdc,0x6a,0x94,0x7c,0x85,0x04,0x30,0x9b,0xed,0xb9,0x41,
  0x00,0x66,0xf4,0x59,0x45,0xfd,0x33,0x65,0x15,0x8c,0x18,0x03,0xb9,0x3c,0x8d,0x9a,
  0x89,0x73,0xea,0x99,0x02,0x3a,0xcc,0xde,0x20,0xf6,0x6f,0xfa,0x34,0x75,0x0e,0x40,
  0x07,0x6f,0xc0,0x13,0xd4,0x0c,0x7f,0x29,0xf1,0xd2,0x92,0xec,0xb4,0x35,0x74,0x90,
  0x81,0x3e,0xc9,0x93,0x4e,0xbc,0x10,0x81,0x90,0x9d,0x21,0xe7,0x1d,0x04,0x90,0x55,
  0xc8,0xc1,0x11,0x10,0x73,0xee,0x0d,0x9e,0xeb,0xbb,0x54,0xc8,0x2d,0xe4,0x8a,0x68,
  0x11,0x08,0xc9,0x03,0x0e,0xdf,0x71,0x09,0xdc,0x5a,0x94,0xcf,0xfe,0xdf,0xc5,0x36,
  0xf4,0x4c,0x72,0xe7,0xe4,0xce,0xb6,0x3d,0xf0,0x46,0xcf,0x1d,0x33,0x43,0xdc,0x16,
  0xc7,0x3b,0x03,0x77,0x5d,0x43,0xcc,0x76,0xed,0xd7,0xb8,0xc4,0x2a,0xec,0x47,0x63,
  0x5c,0xe1,0xfc,0xe1,0x0c,0xae,0x5b,0x49,0xc0,0x23,0x89,0xe8,0x71,0x32,0x48,0xcf,
  0x61,0xba,0xcf,0x97,0x55,0x16,0x34,0x5f,0xfa,0x85,0x9c,0xdb,0x5b,0xeb,0xeb,0xfd,
  0xf5,0xf7,0x1a,0x97,0xd1,0xde,0xd6,0xe5,0xce,0x62,0xc2,0xe4,0x49,0xff,0xa2,0x13,
  0xa7,0x0e,0x1f,0x7d,0x06,0x22,0xb8,0xb2,0xf9,0x99,0x1a,0x15,0xf7,0xa1,0xc4,0xc4,
  0x51,0xb0,0x9b,0x52,0x20,0x5c,0xa8,0x50,0xea,0xa1,0xfb,0xb9,0x5a,0x2b,0xb4,0x4f,
  0x16,0x55,0x07,0x20,0xf2,0x47,0x6a,0x95,0xb6,0x5d,0x92,0x1a,0x43,0x06,0x33,0xcb,
  0x28,0xd6,0x7b,0x5c,0x88,0x31,0x94,0x6f,0x99,0xbf,0x36,0x6e,0xf2,0x94,0x0c,0xbe};
/* private exponent */
static const int8u d[MBX_RSA3K_DATA_BYTE_LEN] = {
  0xc1,0x3c,0x85,0x92,0xe2,0x9c,0x5f,0x15,0x50,0x18,0x72,0x44,0x64,0xb9,0xbb,0x6b,
  0x4e,0x3c,0x1c,0x32,0x67,0x84,0xef,0xb8,0xfb,0x93,0x53,0x4c,0x71,0x54,0x53,0xdc,
  0x28,0x89,0xcb,0x2e,0x09,0x31,0xa3,0x8b,0x1f,0xd5,0x35,0x89,0x8d,0x24,0x09,0x84,
  0x93,0x1e,0x60,0x2e,0xed,0xf2,0x2d,0xbe,0x30,0xd0,0x54,0xb0,0x19,0x43,0x5d,0xf0,
  0x05,0x49,0xb4,0x0b,0x82,0xc7,0x5d,0xc2,0x6e,0xda,0x70,0xa1,0xfb,0xe4,0x6b,0x6c,
  0x3a,0xa8,0x50,0xf8,0x65,0x75,0x39,0x5c,0x59,0x57,0xdb,0x47,0xb1,0xe8,0x6e,0x0a,
  0x63,0xbf,0xf2,0xf8,0xe1,0xf0,0x67,0x8c,0x2e,0x96,0xf4,0x00,0xa8,0x1b,0x94,0x6b,
  0x5a,0x17,0x14,0xd1,0x33,0x72,0x29,0x95,0x60,0x70,0xb3,0xaa,0x25,0x7e,0xf8,0x72,
  0x0f,0x30,0x46,0xf8,0xa6,0x02,0x02,0x98,0x4a,0xae,0xb4,0x48,0x8d,0x64,0x61,0xf0,
  0x61,0x8c,0xb0,0x63,0x6a,0xc5,0x9d,0x42,0x3a,0x52,0x6a,0x7b,0xb4,0x2d,0xa2,0x7a,
  0xd4,0x16,0xda,0x5d,0x3e,0x25,0x01,0x2b,0xa5,0xfe,0x08,0x0a,0x1c,0x94,0xc6,0xce,
  0xe6,0x24,0x07,0x59,0x56,0x69,0x44,0xc4,0x4c,0x42,0x55,0xa9,0xaf,0x91,0x44,0x8d,
  0xdc,0x5c,0x10,0x5f,0xb1,0xe2,0xaf,0x52,0x26,0xa2,0xb9,0x3f,0x33,0x6d,0x61,0x02,
  0x59,0x75,0x38,0x4f,0x9b,0x07,0xd8,0x6a,0x0f,0x53,0x65,0xff,0x7d,0x56,0xe9,0x28,
  0xe8,0x67,0x55,0xa9,0x93,0x94,0xb7,0xc7,0xc5,0x71,0x59,0x98,0x68,0xb2,0xac,0x85,
  0x21,0x80,0x0a,0xf0,0x50,0x16,0xd3,0x45,0x5e,0xc7,0xb7,0x73,0x98,0x5e,0x35,0xb3,
  0x46,0xa2,0x8a,0xea,0xaa,0xaa,0x27,0xef,0x82,0xd2,0x10,0x90,0x8a,0x53,0x04,0xd2,
  0x03,0xda,0x73,0x80,0x62,0x7e,0xcc,0x3c,0xea,0xaa,0xa5,0x78,0x4b,0x91,0xb7,0x22,
  0xc8,0x8a,0xe6,0x62,0x5b,0xa9,0xcb,0xbe,0xda,0x04,0x70,0x12,0x15,0x61,0xb8,0xc4,
  0x38,0x4b,0x71,0x04,0xf4,0x99,0x1e,0x22,0x5d,0xae,0xd5,0x81,0x19,0x37,0xb0,0x44,
  0x17,0xb2,0xb6,0x84,0xa6,0xcb,0xbf,0x2b,0x57,0x57,0x3f,0x48,0x90,0xfa,0x9a,0x2f,
  0xad,0x96,0xde,0x0e,0xc1,0x25,0x11,0xb4,0x63,0x4c,0x78,0x49,0x0f,0xdc,0xe5,0x46,
  0x43,0x7e,0xfa,0x39,0xab,0x40,0x04,0xef,0xf1,0x70,0x91,0x6a,0x38,0x81,0x8c,0xcd,
  0x39,0x08,0xbf,0x09,0x20,0x81,0xbc,0x14,0x10,0x63,0x14,0xe2,0xe5,0x8b,0x2b,0x5d};
/* plaintext */
static const int8u plaintext[MBX_RSA3K_DATA_BYTE_LEN] = {
  0x43,0x9a,0x10,0x7a,0xf5,0x23,0x48,0x2a,0xb9,0xf7,0x67,0xe7,0x57,0x65,0xbe,0x90,
  0xb9,0x50,0x8a,0xc1,0xb0,0x97,0xf5,0x64,0x93,0x8a,0xb0,0xe6,0xdf,0xd9,0x44,0x17,
  0xd0,0x29,0x84,0xad,0xf8,0xb0,0xad,0xe2,0xd3,0xda,0xb7,0xf5,0x12,0x47,0x6c,0x25,
  0xb2,0x9f,0x7f,0xac,0x04,0x33,0x90,0x9f,0x2c,0x96,0xe9,0x1c,0xae,0x02,0x96,0x12,
  0x6c,0x6a,0x88,0x10,0x06,0x9b,0x54,0xc7,0x9d,0x1b,0xd0,0xfd,0x5c,0x46,0xb4,0xe1,
  0x13,0x09,0x12,0xfc,0xfb,0xc2,0x2a,0xe8,0x74,0x95,0xda,0xfa,0xd3,0x69,0x2f,0xc7,
  0x8a,0xbe,0xea,0x0b,0xd7,0x8e,0xd1,0x39,0x58,0xe6,0x0d,0xa9,0xad,0x22,0x64,0x27,
  0x13,0x37,0x12,0x16,0xd6,0xb7,0x8f,0x47,0x86,0x18,0xbb,0x6e,0x79,0xc2,0x92,0xfc,
  0x68,0xbc,0x8a,0xc5,0x14,0xe2,0xa0,0x2f,0xd8,0xa1,0x4c,0xf9,0x39,0xb5,0xe5,0x3e,
  0xcb,0x55,0x11,0x22,0xd7,0x19,0xc4,0x02,0x33,0xea,0x34,0x6e,0x23,0xde,0x1d,0x6e,
  0x3c,0x6f,0x13,0x20,0xb3,0x19,0x97,0xd7,0x14,0xc3,0x3b,0x18,0x13,0xd9,0x1f,0x13,
  0x22,0x34,0xc0,0x17,0xa3,0x54,0x2f,0x37,0x35,0xcc,0x53,0xa9,0xc9,0x6f,0x5a,0xaf,
  0x52,0x4c,0xe0,0x5e,0x77,0xa6,0x2f,0xba,0xf9,0x15,0x3e,0x37,0x65,0x28,0x2d,0x69,
  0x2f,0xcc,0x6e,0xb3,0x68,0x8b,0xe5,0xfb,0xd4,0xb1,0xb0,0x41,0xc8,0xb7,0x8a,0xd5,
  0xc5,0x83,0x49,0x8c,0xfc,0x96,0x21,0xab,0x94,0xd8,0x4c,0x82,0x67,0x2a,0x6f,0x95,
  0x42,0x83,0xe0,0xb1,0xc2,0xa0,0x10,0xed,0x31,0x26,0xbd,0xe2,0x73,0xb3,0x92,0x91,
  0x06,0x70,0xf8,0x10,0xb8,0x01,0xc9,0x34,0x3d,0xd7,0x8e,0x61,0x4e,0x37,0x9e,0x1c,
  0xd4,0x62,0x76,0xb2,0x15,0x15,0xd8,0x44,0x46,0xe5,0xc3,0x5d,0xf0,0xb1,0xe5,0xa0,
  0xbd,0x70,0x17,0x6f,0x84,0x81,0xa7,0xd4,0x64,0xda,0x0a,0xe0,0xf0,0xd7,0x85,0xe9,
  0x86,0x6f,0xe6,0x09,0xed,0x41,0xe3,0x3f,0xfc,0xa6,0xa1,0x30,0x5b,0x36,0x77,0x4d,
  0x96,0xf1,0x58,0x99,0x00,0x27,0x4d,0xdf,0xf2,0x9e,0x94,0x0c,0xe3,0xf3,0xe0,0xeb,
  0x2b,0xa2,0x02,0x6b,0x88,0xa8,0x10,0xb9,0x36,0xcf,0x41,0xb5,0x8c,0xca,0x33,0x69,
  0xeb,0x22,0x6d,0x7d,0xf0,0x66,0x29,0x08,0x79,0x21,0x30,0x47,0x93,0x9d,0x7b,0xbb,
  0xa3,0x05,0x8c,0xc6,0x80,0x04,0x78,0x2c,0x27,0xc5,0xfc,0xfd,0xd6,0x12,0x82,0x2c};
/* ciphertext */
static const int8u ciphertext[MBX_RSA3K_DATA_BYTE_LEN] = {
  0x14,0x65,0xbe,0x8a,0x00,0xef,0x3e,0xc3,0x36,0xfd,0xa0,0x30,0x4d,0x34,0x22,0xd2,
  0x12,0xde,0x7c,0xfa,0x47,0x0c,0x66,0x6b,0x1c,0x2a,0xd2,0x48,0xee,0xf6,0x7d,0x0e,
  0x75,0x68,0xf4,0x50,0xa6,0x14,0x5b,0xec,0xc2,0xd4,0xc0,0xfd,0x01,0xdc,0x9d,0xa6,
  0x79,0x5d,0x3c,0xc2,0xf7,0x8e,0xb9,0xdc,0x5b,0xd6,0xc9,0xe3,0xb3,0xe5,0xad,0xb6,
  0xfc,0x77,0x22,0x48,0xf9,0x5d,0x7d,0xfe,0x71,0x5a,0xb5,0x1e,0x9f,0x48,0x13,0xd0,
  0xa6,0x3c,0xf4,0xed,0x7e,0x45,0x21,0x46,0x08,0x99,0x04,0x94,0xc5,0x35,0x9a,0xe7,
  0x2f,0x13,0xc4,0x24,0xf9,0xb4,0x79,0x03,0xd5,0x68,0x13,0x89,0x6b,0x31,0x78,0x5a,
  0x84,0x11,0x50,0x18,0x2d,0x3b,0x02,0x48,0x44,0xbc,0xaf,0x48,0xe0,0xe9,0x56,0xef,
  0xfa,0xaf,0xef,0xb7,0x05,0xac,0xdb,0xf7,0x42,0x0f,0x9b,0xc0,0xaa,0xc7,0x50,0x79,
  0x25,0x86,0x60,0x53,0x12,0x37,0x58,0xcd,0xbc,0x29,0x19,0x0f,0xb3,0x66,0xdb,0x36,
  0x31,0x55,0x69,0xf5,0xb8,0x8f,0x4f,0x7d,0xdf,0x3a,0xda,0xe0,0xc2,0xe4,0xcb,0x28,
  0x70,0x72,0xf5,0x32,0x3a,0xb8,0xbb,0x78,0x7e,0x3a,0xfa,0x1f,0xe7,0x14,0xb4,0x4e,
  0x77,0xf1,0xbe,0x80,0x19,0x10,0x75,0xaa,0x1f,0xd0,0x80,0x78,0xcf,0xce,0x9c,0x8e,
  0x70,0xd9,0x24,0xa2,0xbb,0x6b,0xd6,0x5c,0xdb,0xe4,0xc5,0x51,0x49,0x1a,0xba,0xaf,
  0x94,0x37,0xc2,0xb7,0xfe,0x85,0xcc,0xff,0xcb,0x81,0xb4,0x47,0x5a,0x46,0xd8,0xff,
  0x36,0xc9,0x14,0x19,0x25,0x9e,0x6b,0x41,0x0c,0x73,0xe9,0xc6,0xd8,0xcf,0x61,0xdd,
  0x82,0xd4,0xc5,0xae,0x53,0x89,0x83,0xc5,0x39,0x47,0x56,0x0d,0x77,0xf0,0xa8,0x76,
  0x04,0x07,0xe8,0x34,0xbf,0x54,0x02,0x84,0xf8,0x00,0x36,0xe0,0x46,0x01,0x96,0xca,
  0x0a,0xdb,0x99,0x61,0x3f,0x1b,0x86,0x36,0xea,0x6b,0xdb,0xe4,0x1b,0xcf,0x3c,0xe6,
  0x16,0x6d,0x48,0x20,0xd7,0xfa,0x4f,0xf3,0xdc,0xd8,0x5c,0x68,0x28,0xe6,0x8a,0x6d,
  0x96,0x9f,0xa5,0x71,0x86,0x90,0xc4,0x97,0x4c,0xe5,0x66,0x25,0xed,0xf7,0x07,0xd6,
  0xbd,0xbb,0xb7,0xef,0x43,0xc2,0xba,0x6e,0xcc,0x00,0xca,0xb2,0x57,0x3f,0xef,0xdb,
  0x08,0x24,0x65,0x7d,0x09,0xd1,0x2f,0x1c,0x1a,0xed,0x35,0x63,0xf6,0xea,0xec,0xea,
  0xc3,0x2a,0xe8,0xb0,0xf0,0xa5,0x8f,0xb6,0x21,0xfb,0xf0,0x91,0x72,0x35,0x7e,0xb2};

DLL_PUBLIC
fips_test_status fips_selftest_mbx_rsa3k_private_mb8(void) {
  fips_test_status test_result = MBX_ALGO_SELFTEST_OK;

  /* output plaintext */
  int8u out_plaintext[MBX_LANES][MBX_RSA3K_DATA_BYTE_LEN];
  /* key operation */
  const mbx_RSA_Method* method = mbx_RSA3K_private_Method();

  /* function input parameters */
  // ciphertext
  const int8u *pa_ciphertext[MBX_LANES] = {
    ciphertext, ciphertext, ciphertext, ciphertext,
    ciphertext, ciphertext, ciphertext, ciphertext};
  // plaintext
  int8u *pa_plaintext[MBX_LANES] = {
    out_plaintext[0], out_plaintext[1], out_plaintext[2], out_plaintext[3],
    out_plaintext[4], out_plaintext[5], out_plaintext[6], out_plaintext[7]};
  // private exponent
  const int64u *pa_d[MBX_LANES]= {
    (int64u *)d, (int64u *)d, (int64u *)d, (int64u *)d,
    (int64u *)d, (int64u *)d, (int64u *)d, (int64u *)d};
  // moduli
  const int64u *pa_moduli[MBX_LANES] = {
    (int64u *)moduli, (int64u *)moduli, (int64u *)moduli, (int64u *)moduli,
    (int64u *)moduli, (int64u *)moduli, (int64u *)moduli, (int64u *)moduli};

  /* test function */
  mbx_status expected_status_mb8 = MBX_SET_STS_ALL(MBX_STATUS_OK);

  mbx_status sts;
  sts = mbx_rsa_private_mb8(pa_ciphertext, pa_plaintext, pa_d, pa_moduli, MBX_RSA3K_DATA_BIT_LEN, method, NULL);
  if (expected_status_mb8 != sts) {
    test_result = MBX_ALGO_SELFTEST_BAD_ARGS_ERR;
  }
  // compare output plaintext to known answer
  int output_status;
  for (int i = 0; (i < MBX_LANES) && (MBX_ALGO_SELFTEST_OK == test_result); ++i) {
    output_status = mbx_is_mem_eq(pa_plaintext[i], MBX_RSA3K_DATA_BYTE_LEN, plaintext, MBX_RSA3K_DATA_BYTE_LEN);
    if (!output_status) { // wrong output
      test_result = MBX_ALGO_SELFTEST_KAT_ERR;
    }
  }

  return test_result;
}


#ifndef BN_OPENSSL_DISABLE

// memory free macro
#define MEM_FREE(BN_PTR1, BN_PTR2) { \
  BN_free(BN_PTR1);                  \
  BN_free(BN_PTR2); }

DLL_PUBLIC
fips_test_status fips_selftest_mbx_rsa3k_private_ssl_mb8(void) {

  fips_test_status test_result = MBX_ALGO_SELFTEST_OK;

  /* output plaintext */
  int8u out_plaintext[MBX_LANES][MBX_RSA3K_DATA_BYTE_LEN];
  /* ssl private exponent */
  BIGNUM* BN_d = BN_new();
  /* ssl moduli */
  BIGNUM* BN_moduli = BN_new();
  /* check if allocated memory is valid */
  if(NULL == BN_d || NULL == BN_moduli) {
    test_result = MBX_ALGO_SELFTEST_BAD_ARGS_ERR;
    MEM_FREE(BN_d, BN_moduli)
    return test_result;
  }
  /* function status and expected status */
  mbx_status sts;
  mbx_status expected_status_mb8 = MBX_SET_STS_ALL(MBX_STATUS_OK);
  /* output validity status */
  int output_status;

  /* set ssl parameters */
  BN_lebin2bn(d, MBX_RSA3K_DATA_BYTE_LEN, BN_d);
  BN_lebin2bn(moduli, MBX_RSA3K_DATA_BYTE_LEN, BN_moduli);

  /* function input parameters */
  // ciphertext
  const int8u *pa_ciphertext[MBX_LANES] = {
    ciphertext, ciphertext, ciphertext, ciphertext,
    ciphertext, ciphertext, ciphertext, ciphertext};
  // plaintext
  int8u *pa_plaintext[MBX_LANES] = {
    out_plaintext[0], out_plaintext[1], out_plaintext[2], out_plaintext[3],
    out_plaintext[4], out_plaintext[5], out_plaintext[6], out_plaintext[7]};
  // moduli
  const BIGNUM *pa_moduli[MBX_LANES] = {
    (const BIGNUM *)BN_moduli, (const BIGNUM *)BN_moduli, (const BIGNUM *)BN_moduli, (const BIGNUM *)BN_moduli,
    (const BIGNUM *)BN_moduli, (const BIGNUM *)BN_moduli, (const BIGNUM *)BN_moduli, (const BIGNUM *)BN_moduli};
  // private exponent
  const BIGNUM *pa_d[MBX_LANES] = {
    (const BIGNUM *)BN_d, (const BIGNUM *)BN_d, (const BIGNUM *)BN_d, (const BIGNUM *)BN_d,
    (const BIGNUM *)BN_d, (const BIGNUM *)BN_d, (const BIGNUM *)BN_d, (const BIGNUM *)BN_d};

  /* test function */
  sts = mbx_rsa_private_ssl_mb8(pa_ciphertext, pa_plaintext, pa_d, pa_moduli, MBX_RSA3K_DATA_BIT_LEN);
  if (expected_status_mb8 != sts) {
    test_result = MBX_ALGO_SELFTEST_BAD_ARGS_ERR;
  }
  // compare output signature to known answer
  for (int i = 0; (i < MBX_LANES) && (MBX_ALGO_SELFTEST_OK == test_result); ++i) {
    output_status = mbx_is_mem_eq(pa_plaintext[i], MBX_RSA3K_DATA_BYTE_LEN, plaintext, MBX_RSA3K_DATA_BYTE_LEN);
    if (!output_status) { // wrong output
      test_result = MBX_ALGO_SELFTEST_KAT_ERR;
    }
  }

  // memory free
  MEM_FREE(BN_d, BN_moduli)

  return test_result;
}

#endif // BN_OPENSSL_DISABLE
#endif // MBX_FIPS_MODE