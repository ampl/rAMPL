#!/bin/bash
if [ "$#" -eq 0 ]; then
  echo "Usage: $0 <version>"
else
  version=$1
  sed -i~ "s/^release.*$/release = \'$version\'/" docs/source/conf.py; rm docs/source/conf.py~
  sed -i~ "s/^Version:.*$/Version: $version/" DESCRIPTION; rm DESCRIPTION~
fi
