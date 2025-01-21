#! /usr/bin/env bash

# all.sh
#
# Copyright The Mbed TLS Contributors
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later

# This file is executable; it is the entry point for users and the CI.
# See "Files structure" in all-core.sh for other files used.

# This script must be invoked from the project's root.

# Prevent silly mistakes when people would invoke this from mbedtls
if [ -d tf-psa-crypto -a -d include/mbedtls ]; then
    echo "When invoking this script from an mbedtls checkout," >&2
    echo "you must change the working directory to tf-psa-crypto." >&2
    exit 255
fi

case "${MBEDTLS_FRAMEWORK-}" in
    /*) :;; # absolute path -> keep
    "") MBEDTLS_FRAMEWORK="$PWD/framework";; # empty or unset -> use default
    *) MBEDTLS_FRAMEWORK="$PWD/$MBEDTLS_FRAMEWORK";; # relative path -> absolute
esac
source "$MBEDTLS_FRAMEWORK/scripts/all-core.sh"

main "$@"
