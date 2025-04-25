#!/usr/bin/env python3

"""Generate C preprocessor code to check for bad configurations.
"""

import scripts_path # pylint: disable=unused-import
from mbedtls_framework import config_checks_generator

CRYPTO_REMOVED_OPTIONS = config_checks_generator.BranchData(
    header_directory='tf-psa-crypto',
    project_cpp_prefix='TF_PSA_CRYPTO',
    removed_options={
        'MBEDTLS_USE_PSA_CRYPTO': 'none (always on)',
    },
)

if __name__ == '__main__':
    config_checks_generator.main(CRYPTO_REMOVED_OPTIONS)
