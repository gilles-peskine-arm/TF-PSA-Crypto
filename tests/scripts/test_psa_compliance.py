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

PSA_ARCH_TESTS_REF = 'v23.06_API1.5_ADAC_EAC'

# PSA Compliance tests we expect to fail due to known defects in Mbed TLS /
# TF-PSA-Crypto (or the test suite).
# The test numbers correspond to the numbers used by the console output of the test suite.
# Test number 2xx corresponds to the files in the folder
# psa-arch-tests/api-tests/dev_apis/crypto/test_c0xx
EXPECTED_FAILURES = [
] # type: List[int]

PATCH = r'''diff --git a/api-tests/platform/targets/tgt_dev_apis_stdc/nspe/pal_crypto_config.h b/api-tests/platform/targets/tgt_dev_apis_stdc/nspe/pal_crypto_config.h
index c5a54a9..682b151 100644
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

@@ -79,10 +79,10 @@
  *
  * Comment macros to disable the types
  */
-#define ARCH_TEST_DES
-#define ARCH_TEST_DES_1KEY
-#define ARCH_TEST_DES_2KEY
-#define ARCH_TEST_DES_3KEY
+//#define ARCH_TEST_DES
+//#define ARCH_TEST_DES_1KEY
+//#define ARCH_TEST_DES_2KEY
+//#define ARCH_TEST_DES_3KEY

 /**
  * \def  ARCH_TEST_RAW
@@ -105,7 +105,7 @@
  *
  * Enable the ARC4 key type.
  */
-#define ARCH_TEST_ARC4
+//#define ARCH_TEST_ARC4

 /**
  * \def ARCH_TEST_CIPHER_MODE_CTR
'''

if __name__ == '__main__':
    psa_compliance.main(PSA_ARCH_TESTS_REF,
                        patch=PATCH,
                        expected_failures=EXPECTED_FAILURES)
