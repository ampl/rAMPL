#!/bin/bash
cd `dirname $0`
BASEDIR=`pwd`
set -ex

if [[ "$(python -V)" =~ "Python 3" ]]; then
    PYTHON="python"
else
    PYTHON="python3"
fi

cd docs
if [ ! -d "venv" ]; then
    $PYTHON -m pip install virtualenv
    $PYTHON -m virtualenv venv
    source venv/bin/activate
    $PYTHON -m pip install -r requirements.txt
    deactivate
fi
source venv/bin/activate
make html
deactivate
cd $BASEDIR
rm -rf rAMPL_*.tar.gz
R CMD build .
