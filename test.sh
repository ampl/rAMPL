#!/bin/bash
BASEDIR=`dirname $0`
cd $BASEDIR

# Install testhat:
# $ R
# > library(remotes)
# > install_github("r-lib/testthat")

echo "library(testthat); test_package('rAMPL'); quit()" | R --no-save

