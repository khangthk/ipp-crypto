/*************************************************************************
* Copyright (C) 2020 Intel Corporation
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

/*
//
//  Purpose:
//     Cryptography Primitive.
//     AES GCM optimized for AVX512 and AVX512-VAES features
//     Internal Definitions
//
//
*/

#ifndef _CP_AESAUTH_GCM_AVX512_H
#define _CP_AESAUTH_GCM_AVX512_H

#include "owndefs.h"
#include "owncp.h"

#if(_IPP32E>=_IPP32E_K0)

#include "pcprij.h"

#include "aes_gcm_vaes.h"
#include "aes_gcm_avx512.h"
#include "aes_gcm_avx512_structures.h"

// Prototypes for internal functions from IPsec

// IV processing
IPP_OWN_FUNPTR (void, IvUpdate_, (const struct gcm_key_data *key_data, struct gcm_context_data *context_data, const Ipp8u *iv, const Ipp64u iv_len))
IPP_OWN_FUNPTR (void, IvFinalize_, (const struct gcm_key_data *key_data, struct gcm_context_data *context_data, const Ipp8u *iv, const Ipp64u iv_len, const Ipp64u iv_general_len))

//  AAD processing
IPP_OWN_FUNPTR (void, AadUpdate_, (const struct gcm_key_data *key_data, struct gcm_context_data *context_data, const Ipp8u *aad, const Ipp64u aad_len))

// GCM multiplication
IPP_OWN_FUNPTR (void, MulGcm_, (const struct gcm_key_data *key_data, Ipp8u *ghash))

//  Encryption-authentication
IPP_OWN_FUNPTR (void, EncryptUpdate_, (const struct gcm_key_data *key_data, struct gcm_context_data *context_data, Ipp8u *out, const Ipp8u *in, Ipp64u len))

// Decryption-verification
IPP_OWN_FUNPTR (void, DecryptUpdate_, (const struct gcm_key_data *key_data, struct gcm_context_data *context_data, Ipp8u *out, const Ipp8u *in, Ipp64u len))

// Get tag
IPP_OWN_FUNPTR (void, GetTag_, (const struct gcm_key_data *key_data, const struct gcm_context_data *context_data, Ipp8u *auth_tag, Ipp64u auth_tag_len))

typedef enum {
   GcmInit,
   GcmIVprocessing,
   GcmAADprocessing,
   GcmTXTprocessing
} GcmState;

#define BLOCK_SIZE (MBS_RIJ128)

// Structure modified to work with functions from IPsec

struct _cpAES_GCM {

   Ipp32u   idCtx;                  /* AES-GCM id                    */
   GcmState state;                  /* GCM state: Init, IV|AAD|TXT processing */
   Ipp64u   ivLen;                  /* IV length (bytes)             */
   Ipp64u   aadLen;                 /* header length (bytes)         */
   Ipp64u   txtLen;                 /* text length (bytes)           */

   int      bufLen;                 /* stuff buffer length           */
   __ALIGN16                        /* aligned buffers               */
   Ipp8u    counter[BLOCK_SIZE];    /* counter                       */
   Ipp8u    ecounter0[BLOCK_SIZE];  /* encrypted initial counter     */
   Ipp8u    ecounter[BLOCK_SIZE];   /* encrypted counter             */
   Ipp8u    ghash[BLOCK_SIZE];      /* ghash accumulator             */

   __ALIGN16
   struct gcm_key_data key_data;
   __ALIGN16
   struct gcm_context_data context_data;
   Ipp64u   keyLen;  /* key length (bytes)             */

   IvUpdate_        ivUpdateFunc;         // IV processing
   IvFinalize_      ivFinalizeFunc;
   AadUpdate_       aadUpdateFunc;        // AAD processing
   MulGcm_          gcmMulFunc;           // GCM multiplication
   EncryptUpdate_   encryptUpdateFunc;    // Encryption-authentication
   DecryptUpdate_   decryptUpdateFunc;    // Decryption-verification
   GetTag_          getTagFunc;           // Get tag

#if (_AES_PROB_NOISE == _FEATURE_ON_)
   __ALIGN16
   cpAESNoiseParams noiseParams;
#endif
};

// Alignment
#define AESGCM_ALIGNMENT   (16)

// Useful macros
#define AESGCM_SET_ID(context)       ((context)->idCtx = (Ipp32u)idCtxAESGCM ^ (Ipp32u)IPP_UINT_PTR(context))
#define AESGCM_STATE(context)        ((context)->state)

#define AESGCM_IV_LEN(context)       ((context)->ivLen)

#define AESGCM_COUNTER(context)      ((context)->counter)
#define AESGCM_ECOUNTER0(context)    ((context)->ecounter0)
#define AESGCM_ECOUNTER(context)     ((context)->ecounter)

#define AES_GCM_KEY_DATA(context)          ((context)->key_data)
#define AES_GCM_CONTEXT_DATA(context)      ((context)->context_data)
#define AES_GCM_KEY_LEN(context)           ((context)->keyLen)

#define AES_GCM_IV_UPDATE(context)         ((context)->ivUpdateFunc)
#define AES_GCM_IV_FINALIZE(context)       ((context)->ivFinalizeFunc)
#define AES_GCM_AAD_UPDATE(context)        ((context)->aadUpdateFunc)
#define AES_GCM_GMUL(context)              ((context)->gcmMulFunc)
#define AES_GCM_ENCRYPT_UPDATE(context)    ((context)->encryptUpdateFunc)
#define AES_GCM_DECRYPT_UPDATE(context)    ((context)->decryptUpdateFunc)
#define AES_GCM_GET_TAG(context)           ((context)->getTagFunc)

// Fields retargeted to IPsec context
#define AESGCM_GHASH(context)              (&(AES_GCM_CONTEXT_DATA(context).aad_hash[0]))
#define AESGCM_TXT_LEN(context)            (AES_GCM_CONTEXT_DATA(context).in_length)
#define AESGCM_AAD_LEN(context)            (AES_GCM_CONTEXT_DATA(context).aad_length)
#define AESGCM_BUFLEN(context)             (AES_GCM_CONTEXT_DATA(context).partial_block_length)

#if (_AES_PROB_NOISE == _FEATURE_ON_)
#define AESGCM_NOISE_PARAMS(ctx)           ((ctx)->noiseParams)
#endif

#define AESGCM_VALID_ID(context)     ((((context)->idCtx) ^ (Ipp32u)IPP_UINT_PTR((context))) == (Ipp32u)idCtxAESGCM)

static int cpSizeofCtx_AESGCM(void)
{
   return (Ipp32s)sizeof(IppsAES_GCMState) + AESGCM_ALIGNMENT-1;
}

#endif // (_IPP32E>=_IPP32E_K0)

#endif // _CP_AESAUTH_GCM_AVX512_H
