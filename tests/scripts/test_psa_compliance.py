#!/usr/bin/env python3
"""Run the PSA Crypto API compliance test suite.

Clone the repo and check out the commit specified by PSA_ARCH_TEST_REPO and PSA_ARCH_TEST_REF,
then compile and run the test suite. The clone is stored at <repository root>/psa-arch-tests.
Known defects in either the test suite or Mbed TLS - identified by their test
number - are ignored, while unexpected failures AND successes are reported as errors, to help
keep the list of known defects as up to date as possible.
"""

# Copyright The Mbed TLS Contributors
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later

from typing import List

import scripts_path # pylint: disable=unused-import
from mbedtls_framework import psa_compliance

PSA_ARCH_TESTS_REF = 'v25.02_API1.8_CRYPTO_1.2.1'

# PSA Compliance tests we expect to fail due to known defects in Mbed TLS /
# TF-PSA-Crypto (or the test suite).
# The test numbers correspond to the numbers used by the console output of the test suite.
# Test number 2xx corresponds to the files in the folder
# psa-arch-tests/api-tests/dev_apis/crypto/test_c0xx
EXPECTED_FAILURES = [
] # type: List[int]

# Patch content:
# * Edit pal_crypto_config.h to declare which mechanisms we support.
# * Minimal fix for a build failure in test_c080.c (independently done
#   upstream in 232fb5801273dbc97789cb9079f1168499e34a2a).
PATCH = r'''diff --git a/api-tests/dev_apis/crypto/test_c080/test_c080.c b/api-tests/dev_apis/crypto/test_c080/test_c080.c
index ae62705..345a802 100644
--- a/api-tests/dev_apis/crypto/test_c080/test_c080.c
+++ b/api-tests/dev_apis/crypto/test_c080/test_c080.c
@@ -85,7 +85,8 @@ int32_t psa_key_agreement_test(caller_security_t caller __UNUSED)
         TEST_ASSERT_DUAL(status, check1[i].expected_status[0],
                                  check1[i].expected_status[1], TEST_CHECKPOINT_NUM(4));

-        if (check1[i].expected_status == PSA_SUCCESS)
+        if (check1[i].expected_status[0] == PSA_SUCCESS &&
+            check1[i].derv_type == PSA_KEY_TYPE_DERIVE)
         {
         /* Set up a key derivation operation */
         status =  val->crypto_function(VAL_CRYPTO_KEY_DERIVATION_SETUP,
diff --git a/api-tests/platform/targets/tgt_dev_apis_stdc/nspe/pal_crypto_config.h b/api-tests/platform/targets/tgt_dev_apis_stdc/nspe/pal_crypto_config.h
index dad40ec..8d19699 100644
--- a/api-tests/platform/targets/tgt_dev_apis_stdc/nspe/pal_crypto_config.h
+++ b/api-tests/platform/targets/tgt_dev_apis_stdc/nspe/pal_crypto_config.h
@@ -53,7 +53,7 @@
  */
 #define ARCH_TEST_ECC
 #define ARCH_TEST_ECC_CURVE_SECP192R1
-#define ARCH_TEST_ECC_CURVE_SECP224R1
+//#define ARCH_TEST_ECC_CURVE_SECP224R1
 #define ARCH_TEST_ECC_CURVE_SECP256R1
 #define ARCH_TEST_ECC_CURVE_SECP384R1

@@ -105,7 +105,7 @@
  *
  * Enable the ARC4 key type.
  */
-#define ARCH_TEST_ARC4
+//#define ARCH_TEST_ARC4

 /**
  * \def ARCH_TEST_CHACHA20
@@ -251,8 +251,8 @@
  */
 // #define ARCH_TEST_MD2
 // #define ARCH_TEST_MD4
-//#define ARCH_TEST_MD5
-//#define ARCH_TEST_RIPEMD160
+#define ARCH_TEST_MD5
+#define ARCH_TEST_RIPEMD160
 #define ARCH_TEST_SHA1
 #define ARCH_TEST_SHA224
 #define ARCH_TEST_SHA256
@@ -260,10 +260,10 @@
 #define ARCH_TEST_SHA512
 // #define ARCH_TEST_SHA512_224
 // #define ARCH_TEST_SHA512_256
-// #define ARCH_TEST_SHA3_224
-// #define ARCH_TEST_SHA3_256
-// #define ARCH_TEST_SHA3_384
-// #define ARCH_TEST_SHA3_512
+#define ARCH_TEST_SHA3_224
+#define ARCH_TEST_SHA3_256
+#define ARCH_TEST_SHA3_384
+#define ARCH_TEST_SHA3_512

 /**
  * \def ARCH_TEST_HKDF
@@ -291,8 +291,8 @@
  * Enable the NIST SP800-108 Counter mode KDF algorithm
  *
 */
-#define ARCH_TEST_SP800_108_COUNTER_HMAC
-#define ARCH_TEST_SP800_108_COUNTER_CMAC
+//#define ARCH_TEST_SP800_108_COUNTER_HMAC
+//#define ARCH_TEST_SP800_108_COUNTER_CMAC

 /**
  * \def ARCH_TEST_xMAC
@@ -369,7 +369,7 @@
  * Enable deterministic ECDSA (RFC 6979).
 */
 #define ARCH_TEST_DETERMINISTIC_ECDSA
-#define ARCH_TEST_TWISTED_EDWARDS
+//#define ARCH_TEST_TWISTED_EDWARDS

 /**
  * \def ARCH_TEST_ECC_ASYMMETRIC_API_SUPPORT
@@ -397,10 +397,10 @@
  *
  * Enable support for augmented PAKE: SPAKE2P algorithm
  */
-#define ARCH_TEST_SPAKE2P
-#define ARCH_TEST_SPAKE2P_HMAC
-#define ARCH_TEST_SPAKE2P_CMAC
-#define ARCH_TEST_SPAKE2P_MATTER
+//#define ARCH_TEST_SPAKE2P
+//#define ARCH_TEST_SPAKE2P_HMAC
+//#define ARCH_TEST_SPAKE2P_CMAC
+//#define ARCH_TEST_SPAKE2P_MATTER

 #include "pal_crypto_config_check.h"

'''

if __name__ == '__main__':
    psa_compliance.main(PSA_ARCH_TESTS_REF,
                        patch=PATCH,
                        expected_failures=EXPECTED_FAILURES)
