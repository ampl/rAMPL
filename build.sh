#!/bin/bash
cd `dirname $0`
BASEDIR=`pwd`

cd docs
source venv/bin/activate
make html
deactivate
cd $BASEDIR
rm -rf rAMPL_*.tar.gz
cd ..
R CMD build rAMPL
mv rAMPL_*.tar.gz rAMPL/
