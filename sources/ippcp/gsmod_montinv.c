/*******************************************************************************
* Copyright 2017-2018 Intel Corporation
* All Rights Reserved.
*
* If this  software was obtained  under the  Intel Simplified  Software License,
* the following terms apply:
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*
*
* If this  software  was obtained  under the  Apache License,  Version  2.0 (the
* "License"), the following terms apply:
*
* You may  not use this  file except  in compliance  with  the License.  You may
* obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*
* Unless  required  by   applicable  law  or  agreed  to  in  writing,  software
* distributed under the License  is distributed  on an  "AS IS"  BASIS,  WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
* See the   License  for the   specific  language   governing   permissions  and
* limitations under the License.
*******************************************************************************/

/* 
// 
//  Purpose:
//     Cryptography Primitive. Modular Arithmetic Engine. General Functionality
// 
//  Contents:
//        gs_mont_inv()
//
*/

#include "owndefs.h"
#include "owncp.h"
#include "pcpbnumisc.h"
#include "pcpbnuarith.h"
#include "gsmodstuff.h"

/*
// returns r = mont(a^-1)
//    a in desidue domain
//    r in Montgomery domain
*/
BNU_CHUNK_T* gs_mont_inv(BNU_CHUNK_T* pr, const BNU_CHUNK_T* pa, gsModEngine* pME, alm_inv alm_inversion)
{
   int k = alm_inversion(pr, pa, pME);

   if(0==k)
      return NULL;

   {
      int mLen = MOD_LEN(pME);
      int m = mLen*BNU_CHUNK_BITS;
      mod_mul mon_mul = MOD_METHOD(pME)->mul;

      BNU_CHUNK_T* t = gsModPoolAlloc(pME, 1);
      //tbcd: temporary excluded: assert(NULL!=t);

      if(k<=m) {
         mon_mul(pr, pr, MOD_MNT_R2(pME), pME);
         k += m;
      }

      ZEXPAND_BNU(t, 0, mLen);
      SET_BIT(t, 2*m-k); /* t = 2^(2*m-k) */
      mon_mul(pr, pr, t, pME);

      gsModPoolFree(pME, 1);

      return pr;
   }
}
