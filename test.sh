#!/bin/bash
BASEDIR=`dirname $0`
cd $BASEDIR

echo "library(testthat); test_package('rAMPL'); quit()" | R --no-save

