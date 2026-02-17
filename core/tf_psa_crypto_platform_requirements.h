/**
 * \file tf_psa_crypto_platform_requirements.h
 *
 * \brief Declare macros that tell system headers what we expect of them.
 *
 * This file must be included before any system header, and so in particular
 * before build_info.h (which includes the user config, which may include
 * system headers).
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#ifndef TF_PSA_CRYPTO_TF_PSA_CRYPTO_PLATFORM_REQUIREMENTS_H
#define TF_PSA_CRYPTO_TF_PSA_CRYPTO_PLATFORM_REQUIREMENTS_H

#if defined(__clang__) &&  (__clang_major__ >= 4)

/* Ideally, we would simply use MBEDTLS_ARCH_IS_ARMV8_A below,
 * but that is defined by build_info.h, and we need this block to happen first. */
#if defined(__ARM_ARCH) && (__ARM_ARCH_PROFILE == 'A')
#if __ARM_ARCH >= 8
#define MBEDTLS_INTERNAL_ARCH_IS_ARMV8_A
#endif
#endif

#if defined(MBEDTLS_INTERNAL_ARCH_IS_ARMV8_A) && !defined(__ARM_FEATURE_CRYPTO)
/* The intrinsic declaration are guarded by predefined ACLE macros in clang:
 * these are normally only enabled by the -march option on the command line.
 * By defining the macros ourselves we gain access to those declarations without
 * requiring -march on the command line.
 *
 * `arm_neon.h` is included by tf_psa_crypto_common.h, so we put these defines
 * at the top of this file, before any includes. This is necessary with
 * Clang <=15.x. With Clang 16.0 and above, these macro definitions are
 * no longer required, but they're harmless. See
 * https://reviews.llvm.org/D131064
 */
#define __ARM_FEATURE_CRYPTO 1
/* See: https://arm-software.github.io/acle/main/acle.html#cryptographic-extensions
 *
 * `__ARM_FEATURE_CRYPTO` is deprecated, but we need to continue to specify it
 * for older compilers.
 */
#define __ARM_FEATURE_AES    1
#define MBEDTLS_ENABLE_ARM_CRYPTO_EXTENSIONS_COMPILER_FLAG
#endif

#if defined(MBEDTLS_INTERNAL_ARCH_IS_ARMV8_A) && !defined(__ARM_FEATURE_CRYPTO)
/*
 * The intrinsic declaration are guarded by predefined ACLE macros in clang:
 * these are normally only enabled by the -march option on the command line.
 * By defining the macros ourselves we gain access to those declarations without
 * requiring -march on the command line.
 *
 * `arm_neon.h` is included by tf_psa_crypto_common.h, so we put these defines
 * at the top of this file, before any includes but after the intrinsic
 * declaration. This is necessary with
 * Clang <=15.x. With Clang 16.0 and above, these macro definitions are
 * no longer required, but they're harmless. See
 * https://reviews.llvm.org/D131064
 */
#define __ARM_FEATURE_CRYPTO 1
/* See: https://arm-software.github.io/acle/main/acle.html#cryptographic-extensions
 *
 * `__ARM_FEATURE_CRYPTO` is deprecated, but we need to continue to specify it
 * for older compilers.
 */
#define __ARM_FEATURE_SHA2   1
#define MBEDTLS_ENABLE_ARM_CRYPTO_EXTENSIONS_COMPILER_FLAG
#endif

#endif /* defined(__clang__) &&  (__clang_major__ >= 4) */

#if defined(__aarch64__) && !defined(__ARM_FEATURE_SHA512) && \
    defined(__clang__) && __clang_major__ >= 7
/*
 * The intrinsic declaration are guarded by predefined ACLE macros in clang:
 * these are normally only enabled by the -march option on the command line.
 * By defining the macros ourselves we gain access to those declarations without
 * requiring -march on the command line.
 *
 * `arm_neon.h` is included by tf_psa_crypto_common.h, so we put these defines
 * at the top of this file, before any includes but after the intrinsic
 * declaration. This is necessary with
 * Clang <=15.x. With Clang 16.0 and above, these macro definitions are
 * no longer required, but they're harmless. See
 * https://reviews.llvm.org/D131064
 */
#define __ARM_FEATURE_SHA512 1
#define MBEDTLS_ENABLE_ARM_SHA3_EXTENSIONS_COMPILER_FLAG
#endif


#ifndef __STDC_WANT_LIB_EXT1__
/* Ask for the C11 gmtime_s() and memset_s() if available */
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#if !defined(_POSIX_C_SOURCE)
/* For standards-compliant access to
 * clock_gettime(), gmtime_r(), ...
 */
#define _POSIX_C_SOURCE 200112L
#endif

/* With GNU libc, define all the things, even when compiling with -pedantic.
 * Things we like to see include:
 * - syscall() for getrandom() on Linux
 * - explicit_bzero() to implement mbedtls_platform_zeroize()
 * - SIG_SETMASK for runtime detection of Arm CPU extensions
 */
#if !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif

/* On NetBSD, needed to include <sys/sysctl.h>, which we do in platform_util.c
 * to get sysctl() and KERN_ARND. */
#if defined(__NetBSD__) && !defined(_NETBSD_SOURCE)
#define _NETBSD_SOURCE
#endif

/* On OpenBSD, needed to make <string.h> declare explicit_bzero()
 * (<strings.h> doesn't declare it). Not used on FreeBSD or NetBSD,
 * but causes Glibc to complain. */
#if defined(__OpenBSD__) && !defined(_BSD_SOURCE)
#define _BSD_SOURCE
#endif

/* On Mingw-w64, force the use of a C99-compliant printf() and friends.
 * This is necessary on older versions of Mingw and/or Windows runtimes
 * where snprintf does not always zero-terminate the buffer, and does
 * not support formats such as "%zu" for size_t and "%lld" for long long.
 *
 * Defining __USE_MINGW_ANSI_STDIO=0 may work and provide a small code size
 * and performance benefit for some combinations of older Mingw and Windows
 * versions. Do this at your own risk and make sure that least
 * test_suite_platform_printf passes.
 */
#if !defined(__USE_MINGW_ANSI_STDIO)
#define __USE_MINGW_ANSI_STDIO 1
#endif

#endif /* TF_PSA_CRYPTO_TF_PSA_CRYPTO_PLATFORM_REQUIREMENTS_H */
