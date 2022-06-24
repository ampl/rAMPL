#!/bin/bash
BASEDIR=`dirname $0`
cd $BASEDIR
set -ex

R CMD INSTALL `ls rAMPL_*.tar.gz` --debug --no-multiarch --no-staged-install
