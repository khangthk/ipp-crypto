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

#include <crypto_mb/ec_nistp521.h>

#ifndef BN_OPENSSL_DISABLE
  #include <openssl/ecdsa.h>
#endif

#define NISTP521_MAX_DATA_BYTE_LEN ((((MBX_NISTP521_DATA_BYTE_LEN - 1) / 8) + 1) * 8)

/* Pairwise Consistency Test for EC p521 keypair */
/* KAT data taken from FIPS 186-4 examples */
// msg ==
// "9ecd500c60e701404922e58ab20cc002651fdee7cbc9336adda33e4c1088fab1"
// "964ecb7904dc6856865d6c8e15041ccf2d5ac302e99d346ff2f686531d255216"
// "78d4fd3f76bbf2c893d246cb4d7693792fe18172108146853103a51f824acc62"
// "1cb7311d2463c3361ea707254f2b052bc22cb8012873dcbb95bf1a5cc53ab89f"

/* msgDigest == SHA-521(msg) */
static const int8u msg_digest[MBX_NISTP521_DATA_BYTE_LEN] = {
  0x00,0x00,0x65,0xf8,0x34,0x08,0x09,0x22,0x61,0xbd,0xa5,0x99,0x38,0x9d,0xf0,0x33,
  0x82,0xc5,0xbe,0x01,0xa8,0x1f,0xe0,0x0a,0x36,0xf3,0xf4,0xbb,0x65,0x41,0x26,0x3f,
  0x80,0x16,0x27,0xc4,0x40,0xe5,0x08,0x09,0x71,0x2b,0x0c,0xac,0xe7,0xc2,0x17,0xe6,
  0xe5,0x05,0x1a,0xf8,0x1d,0xe9,0xbf,0xec,0x32,0x04,0xdc,0xd6,0x3c,0x4f,0x9a,0x74,
  0x10,0x47};
/* private key */
static const int8u d[MBX_NISTP521_DATA_BYTE_LEN] = {
  0x26,0xb9,0x4c,0xa1,0x7a,0x56,0x5e,0x6c,0xee,0x9f,0xcf,0xcc,0xc0,0x55,0x86,0x8c,
  0x21,0x0f,0x9a,0xc2,0xcc,0x74,0xf5,0x72,0x9b,0x35,0xa2,0xdc,0x80,0x00,0xab,0x2f,
  0xf0,0xfa,0x7f,0x26,0x86,0xb8,0x7d,0xed,0x15,0xe5,0x78,0x26,0x8d,0xf0,0x67,0xba,
  0x4f,0x8f,0x3d,0x10,0xcf,0x0a,0xef,0x2c,0xa8,0x3c,0x53,0xbc,0x04,0x27,0xd3,0x49,
  0xf7,0x00};
static const int8u k[MBX_NISTP521_DATA_BYTE_LEN] = {
  0xf1,0x6d,0x4c,0x86,0x3e,0x59,0xc7,0x83,0xbb,0xec,0xd4,0x33,0xa7,0x0a,0x3f,0xec,
  0xfc,0x81,0xf8,0xdc,0xc9,0x9a,0xdb,0xf3,0xe1,0xcf,0x46,0xcf,0xfe,0x12,0x2d,0x81,
  0x60,0xac,0xde,0xdd,0x3c,0x05,0xe3,0x9b,0x76,0x0c,0xc6,0xb5,0x52,0xcd,0xff,0x17,
  0x6a,0xb1,0xc3,0x83,0xaa,0xb9,0xba,0xa5,0x86,0xde,0xa6,0x29,0xaa,0x6c,0xab,0xf5,
  0x3a,0x00};
/* output signature buffers */
static int8u out_r[MBX_LANES][NISTP521_MAX_DATA_BYTE_LEN];
static int8u out_s[MBX_LANES][NISTP521_MAX_DATA_BYTE_LEN];

DLL_PUBLIC
fips_test_status fips_selftest_mbx_nistp521_ecpublic_key_mb8(void) {
  fips_test_status test_result = MBX_ALGO_SELFTEST_OK;

  /* function input parameters */
  // private key
  const int64u *const pa_prv_d[MBX_LANES] = {
    (int64u *)d, (int64u *)d, (int64u *)d, (int64u *)d,
    (int64u *)d, (int64u *)d, (int64u *)d, (int64u *)d};
  const int64u *const pa_prv_k[MBX_LANES] = {
    (int64u *)k, (int64u *)k, (int64u *)k, (int64u *)k,
    (int64u *)k, (int64u *)k, (int64u *)k, (int64u *)k};
  // msg digest
  const int8u *const pa_pub_msg_digest[MBX_LANES] = {
      msg_digest, msg_digest, msg_digest, msg_digest,
      msg_digest, msg_digest, msg_digest, msg_digest};

  /* function output parameters */
  // output public key
  int8u out_Qx[MBX_LANES][NISTP521_MAX_DATA_BYTE_LEN];
  int8u out_Qy[MBX_LANES][NISTP521_MAX_DATA_BYTE_LEN];
  // public key
  int64u *pa_pub_Qx[MBX_LANES] = {
      (int64u *)out_Qx[0], (int64u *)out_Qx[1],
      (int64u *)out_Qx[2], (int64u *)out_Qx[3],
      (int64u *)out_Qx[4], (int64u *)out_Qx[5],
      (int64u *)out_Qx[6], (int64u *)out_Qx[7]};
  int64u *pa_pub_Qy[MBX_LANES] = {
      (int64u *)out_Qy[0], (int64u *)out_Qy[1],
      (int64u *)out_Qy[2], (int64u *)out_Qy[3],
      (int64u *)out_Qy[4], (int64u *)out_Qy[5],
      (int64u *)out_Qy[6], (int64u *)out_Qy[7]};
  // output signature
  int8u *pa_sign_r[MBX_LANES] = {
      out_r[0], out_r[1], out_r[2], out_r[3],
      out_r[4], out_r[5], out_r[6], out_r[7]};
  int8u *pa_sign_s[MBX_LANES] = {
      out_s[0], out_s[1], out_s[2], out_s[3],
      out_s[4], out_s[5], out_s[6], out_s[7]};

  /* test function */
  mbx_status expected_status_mb8 = MBX_SET_STS_ALL(MBX_STATUS_OK);
  mbx_status sts;
  sts = mbx_nistp521_ecpublic_key_mb8(pa_pub_Qx, pa_pub_Qy, NULL, pa_prv_d, NULL);
  if (sts != expected_status_mb8){
    test_result = MBX_ALGO_SELFTEST_BAD_ARGS_ERR;
    return test_result;
  }
  // Add const qualifiers to arrays
  const int64u* const * _pa_pub_Qx = (const int64u* const *)pa_pub_Qx;
  const int64u* const * _pa_pub_Qy = (const int64u* const *)pa_pub_Qy;

  // sign and verify with the generated keypair
  sts = mbx_nistp521_ecdsa_sign_mb8(pa_sign_r, pa_sign_s, pa_pub_msg_digest, pa_prv_k, pa_prv_d, NULL);
  if (sts != expected_status_mb8) {
    test_result = MBX_ALGO_SELFTEST_BAD_ARGS_ERR;
    return test_result;
  }
  // Add const qualifiers to arrays
  const int8u* const * _pa_sign_r = (const int8u* const *)pa_sign_r;
  const int8u* const * _pa_sign_s = (const int8u* const *)pa_sign_s;

  sts = mbx_nistp521_ecdsa_verify_mb8(_pa_sign_r, _pa_sign_s, pa_pub_msg_digest, _pa_pub_Qx, _pa_pub_Qy, NULL, NULL);

  // check the result of verification
  if (expected_status_mb8 != sts) {
    test_result = MBX_ALGO_SELFTEST_KAT_ERR;
  }

  return test_result;
}

#ifndef BN_OPENSSL_DISABLE

// memory free macro
#define MEM_FREE(BN_PTR_ARR1, BN_PTR_ARR2, SIG_PTR_ARR3, BN_PTR4, BN_PTR5) { \
  for (int i = 0; i < MBX_LANES; ++i) {                                      \
    BN_free(BN_PTR_ARR1[i]);                                                 \
    BN_free(BN_PTR_ARR2[i]);                                                 \
    ECDSA_SIG_free(SIG_PTR_ARR3[i]);                                         \
  }                                                                          \
  BN_free(BN_PTR4);                                                          \
  BN_free(BN_PTR5); }

DLL_PUBLIC
fips_test_status fips_selftest_mbx_nistp521_ecpublic_key_ssl_mb8(void) {
  fips_test_status test_result = MBX_ALGO_SELFTEST_OK;
  /* function status and expected status */
  mbx_status sts;
  mbx_status expected_status_mb8 = MBX_SET_STS_ALL(MBX_STATUS_OK);

  /* functions input parameters */
  // ssl private key
  BIGNUM *BN_d = BN_new();
  BIGNUM *BN_k = BN_new();
  // public key
  BIGNUM *pa_pub_Qx[MBX_LANES] = {
    BN_new(), BN_new(), BN_new(), BN_new(),
    BN_new(), BN_new(), BN_new(), BN_new()};
  BIGNUM *pa_pub_Qy[MBX_LANES] = {
    BN_new(), BN_new(), BN_new(), BN_new(),
    BN_new(), BN_new(), BN_new(), BN_new()};
  // signature for verify API
  ECDSA_SIG *const pa_sig[MBX_LANES] = {
    ECDSA_SIG_new(), ECDSA_SIG_new(), ECDSA_SIG_new(), ECDSA_SIG_new(),
    ECDSA_SIG_new(), ECDSA_SIG_new(), ECDSA_SIG_new(), ECDSA_SIG_new()};
  /* check if allocated memory is valid */
  if(NULL == BN_d || NULL == BN_k) {
    test_result = MBX_ALGO_SELFTEST_BAD_ARGS_ERR;
  }
  for(int i = 0; (i < MBX_LANES) && (MBX_ALGO_SELFTEST_OK == test_result); ++i) {
    if(NULL == pa_pub_Qx[i] || NULL == pa_pub_Qy[i] || NULL == pa_sig[i]) {
      test_result = MBX_ALGO_SELFTEST_BAD_ARGS_ERR;
    }
  }
  if(MBX_ALGO_SELFTEST_OK != test_result) {
    MEM_FREE(pa_pub_Qx, pa_pub_Qy, pa_sig, BN_d, BN_k)
    return test_result;
  }

  // set ssl private key
  BN_lebin2bn(d, MBX_NISTP521_DATA_BYTE_LEN, BN_d);
  BN_lebin2bn(k, MBX_NISTP521_DATA_BYTE_LEN, BN_k);
  // private key
  const BIGNUM *const pa_prv_d[MBX_LANES] = {
    (const BIGNUM *const)BN_d, (const BIGNUM *const)BN_d, (const BIGNUM *const)BN_d, (const BIGNUM *const)BN_d,
    (const BIGNUM *const)BN_d, (const BIGNUM *const)BN_d, (const BIGNUM *const)BN_d, (const BIGNUM *const)BN_d};
  const BIGNUM *const pa_prv_k[MBX_LANES] = {
    (const BIGNUM *const)BN_k, (const BIGNUM *const)BN_k, (const BIGNUM *const)BN_k, (const BIGNUM *const)BN_k,
    (const BIGNUM *const)BN_k, (const BIGNUM *const)BN_k, (const BIGNUM *const)BN_k, (const BIGNUM *const)BN_k};
  // msg digest
  const int8u *const pa_pub_msg_digest[MBX_LANES] = {
      msg_digest, msg_digest, msg_digest, msg_digest,
      msg_digest, msg_digest, msg_digest, msg_digest};

  /* functions output parameters */
  // output signature for sign API
  int8u *pa_sign_r[MBX_LANES] = {
      out_r[0], out_r[1], out_r[2], out_r[3],
      out_r[4], out_r[5], out_r[6], out_r[7]};
  int8u *pa_sign_s[MBX_LANES] = {
      out_s[0], out_s[1], out_s[2], out_s[3],
      out_s[4], out_s[5], out_s[6], out_s[7]};

  /* test function */
  sts = mbx_nistp521_ecpublic_key_ssl_mb8(pa_pub_Qx, pa_pub_Qy, NULL, pa_prv_d, NULL);
  if (sts != expected_status_mb8){
    test_result = MBX_ALGO_SELFTEST_BAD_ARGS_ERR;
    MEM_FREE(pa_pub_Qx, pa_pub_Qy, pa_sig, BN_d, BN_k)
    return test_result;
  }
  // Add const qualifiers to arrays
  const BIGNUM* const * _pa_pub_Qx = (const BIGNUM* const *)pa_pub_Qx;
  const BIGNUM* const * _pa_pub_Qy = (const BIGNUM* const *)pa_pub_Qy;

 // sign and verify with the generated keypair
  sts = mbx_nistp521_ecdsa_sign_ssl_mb8(pa_sign_r, pa_sign_s, pa_pub_msg_digest, pa_prv_k, pa_prv_d, NULL);
  if (sts != expected_status_mb8){
    test_result = MBX_ALGO_SELFTEST_BAD_ARGS_ERR;
    MEM_FREE(pa_pub_Qx, pa_pub_Qy, pa_sig, BN_d, BN_k)
    return test_result;
  }

  // fill ECDSA_SIG structure with the generated signature for verification
  for (int i = 0; i < MBX_LANES; ++i){
    BIGNUM *BN_r = BN_new();
    BIGNUM *BN_s = BN_new();
    /* check if allocated memory is valid */
    if(NULL == BN_r || NULL == BN_s) {
      test_result = MBX_ALGO_SELFTEST_BAD_ARGS_ERR;
      MEM_FREE(pa_pub_Qx, pa_pub_Qy, pa_sig, BN_d, BN_k)
      // Handled separately, since memory management of
      // these variables is transferred to sig below
      BN_free(BN_r);
      BN_free(BN_s);
      return test_result;
    }

    BN_bin2bn(out_r[i], MBX_NISTP521_DATA_BYTE_LEN, BN_r);
    BN_bin2bn(out_s[i], MBX_NISTP521_DATA_BYTE_LEN, BN_s);
    ECDSA_SIG_set0(pa_sig[i], BN_r, BN_s);
  }
  sts = mbx_nistp521_ecdsa_verify_ssl_mb8((const ECDSA_SIG *const *)pa_sig, pa_pub_msg_digest,
                                          _pa_pub_Qx, _pa_pub_Qy, NULL, NULL);

  // check the result of verification
  if (expected_status_mb8 != sts) {
    test_result = MBX_ALGO_SELFTEST_KAT_ERR;
  }

  MEM_FREE(pa_pub_Qx, pa_pub_Qy, pa_sig, BN_d, BN_k)

  return test_result;
}

#endif // BN_OPENSSL_DISABLE
#endif // MBX_FIPS_MODE
