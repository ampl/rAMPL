#!/bin/bash
BASEDIR=`dirname $0`
cd $BASEDIR
set -ex

# Install testhat:
# $ R
# > library(remotes)
# > install_github("r-lib/testthat")
R --no-save -q -e "library(testthat); test_package('rAMPL');" 2>&1
