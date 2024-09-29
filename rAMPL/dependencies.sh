#!/bin/bash
BASEDIR=`dirname $0`
cd $BASEDIR
set -ex

R --no-save -q -e "install.packages(c('Rcpp', 'testthat'), repos='http://cran.us.r-project.org', INSTALL_opts=c('--no-multiarch'))"
