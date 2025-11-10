/**
 * \file tf-psa-crypto/private/crypto_adjust_config_support.h
 * \brief Adjust TF-PSA-Crypto configuration: support modules
 *
 * This is an internal header. Do not include it directly.
 *
 * Activate parts of support modules, based on the user configuration
 * as well as requirements of generic code and requirements of
 * driver-specific code.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#ifndef TF_PSA_CRYPTO_PRIVATE_CRYPTO_ADJUST_CONFIG_SUPPORT_H
#define TF_PSA_CRYPTO_PRIVATE_CRYPTO_ADJUST_CONFIG_SUPPORT_H

#if !defined(TF_PSA_CRYPTO_CONFIG_FILES_READ)
#error "Do not include mbedtls/config_adjust_*.h manually! This can lead to problems, " \
    "up to and including runtime errors such as buffer overflows. " \
    "If you're trying to fix a complaint from check_config.h, just remove " \
    "it from your configuration file: since Mbed TLS 3.0, it is included " \
    "automatically at the right point."
#endif /* */


#endif /* TF_PSA_CRYPTO_PRIVATE_CRYPTO_ADJUST_CONFIG_SUPPORT_H */
