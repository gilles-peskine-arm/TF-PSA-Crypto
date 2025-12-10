# Helper code for the make build system in Mbed TLS.
# This file is only meant to exist for a short transition period.
# It may change or be removed without notice.
# Do not use it if you are not Mbed TLS!

# Assume that this makefile is located in a first-level subdirectory of the
# TF-PSA-Crypto root, and is accessed directly (not via VPATH or such).
TF_PSA_CRYPTO_PATH := $(dir $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST)))))
