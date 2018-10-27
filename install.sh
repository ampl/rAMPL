#!/bin/bash
BASEDIR=`dirname $0`
cd $BASEDIR

R CMD INSTALL `ls rAMPL_*.tar.gz` --no-multiarch

