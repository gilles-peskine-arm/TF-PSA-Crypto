/**
 * \file platform_threading.h
 *
 * \brief Platform interface for threading.
 *
 * Alternative implementations of the threading abstraction need to
 * implement the header, types and functions documented in this file:
 *
 * - Provide a header file `"threading_alt.h"` that defines the following:
 *     - The type `mbedtls_platform_mutex_t` of mutex objects.
 *
 * - Either define inline versions of the functions listed in this file
 *   in `"threading_alt.h"`, or provide linkable versions of the functions
 *   at link time.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */
#ifndef MBEDTLS_PLATFORM_THREADING_H
#define MBEDTLS_PLATFORM_THREADING_H
#include "mbedtls/private_access.h"

#include "tf-psa-crypto/build_info.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_THREADING_C11)
#include <threads.h>
typedef mtx_t mbedtls_platform_mutex_t;
#endif

#if defined(MBEDTLS_THREADING_PTHREAD)
#include <pthread.h>
typedef pthread_mutex_t mbedtls_platform_mutex_t;
#endif

#if defined(MBEDTLS_THREADING_ALT)
/* You should define the type mbedtls_platform_mutex_t type in your header */
#include "threading_alt.h"
#endif /* MBEDTLS_THREADING_ALT */

#if defined(MBEDTLS_THREADING_C)

/** Platform callback to initialize and set up a mutex.
 *
 * \note    The mutex may not be used until one thread has completed a call
 *          to mbedtls_mutex_init().
 *
 * \note    This function may allocate resources. Call mbedtls_mutex_free()
 *          to free these resources.
 *
 * \note    mbedtls_mutex_init() does not return a status code.
 *          If it fails, it should leave its argument (the mutex)
 *          in a state such that mbedtls_mutex_lock() will fail when
 *          called with this argument.
 *
 * \param[out] mutex    The mutex to initialize.
 */
void mbedtls_platform_mutex_init(mbedtls_platform_mutex_t *mutex);

/** Platform callback to destroy a mutex.
 *
 * A destroyed mutex does not hold any resources.
 *
 * \note    As soon as one thread has started a call to this function,
 *          no other thread may access the mutex in any way, including
 *          concurrent calls to this function. Once the call returns,
 *          you may call mbedtls_mutex_init() again on the mutex.
 *
 * \param[in,out] mutex The mutex to destroy.
 */
void mbedtls_platform_mutex_free(mbedtls_platform_mutex_t *mutex);

/** Platform callback to lock a mutex.
 *
 * \note    The mutex must have been initialized and must not be
 *          already locked by the same state (no recursive locking).
 *          Otherwise the behavior is undefined.
 *
 * \param[in,out] mutex The mutex to lock.
 *
 * \retval 0            Success.
 * \retval #MBEDTLS_ERR_THREADING_MUTEX_ERROR
 *                      The mutex could not be locked.
 * \retval #MBEDTLS_ERR_THREADING_BAD_INPUT_DATA
 *                      The mutex is in an invalid state.
 */
int mbedtls_platform_mutex_lock(mbedtls_platform_mutex_t *mutex);

/** Platform callback to unlock a mutex.
 *
 * \note    The mutex must have been locked by the same thread.
 *          Otherwise the behavior is undefined.
 *
 * \param[in,out] mutex The mutex to unlock.
 *
 * \retval 0            Success.
 * \retval #MBEDTLS_ERR_THREADING_MUTEX_ERROR
 *                      The mutex could not be unlocked.
 * \retval #MBEDTLS_ERR_THREADING_BAD_INPUT_DATA
 *                      The mutex is in an invalid state.
 */
int mbedtls_platform_mutex_unlock(mbedtls_platform_mutex_t *mutex);

#endif /* MBEDTLS_THREADING_C */

#ifdef __cplusplus
}
#endif

#endif /* platform_threading.h */
