#!/bin/bash
BASEDIR=`dirname $0`
cd $BASEDIR

cd docs
source venv/bin/activate
make html
deactivate
cd ../..
R CMD build rAMPL
mv rAMPL_*.tar.gz rAMPL/
