### rAMPL

[![Build Status](https://dev.azure.com/ampldev/rAMPL/_apis/build/status/ampl.rAMPL?branchName=master)](https://dev.azure.com/ampldev/rAMPL/_build/latest?definitionId=10&branchName=master) [![build-and-test](https://github.com/ampl/rAMPL/actions/workflows/build-and-test.yaml/badge.svg)](https://github.com/ampl/rAMPL/actions/workflows/build-and-test.yaml)

AMPL API is an interface that allows developers to access the features of the
AMPL interpreter from within a programming language. All model generation and
solver interaction is handled directly by AMPL, which leads to great stability
and speed; the library just acts as an intermediary, and the added overhead
(in terms of memory and CPU usage) depends mostly on how much data is read
back from AMPL, the size of the model as such is irrelevant. Functions for
directly assigning data to AMPL parameters and sets are provided, which can
be used instead of the normal AMPL data reading procedures.  AMPL API has been
written with usability in mind, and it is easy to access its functionalities
from C++, Java, C#, MATLAB, Python, and R.

The AMPL API can function as an add-on to any existing AMPL installation. If
you do not yet have an AMPL installation on the computer where you will be
working with the API. Use our [Community Edition](http://ampl.com/ce)
to download a working version that can be installed quickly.

#### Documentation

- http://rAMPL.readthedocs.io

#### Setup

In order to install the latest version of the R API you just need to run:
```
> install.packages("Rcpp", type="source")
> install.packages("https://ampl.com/dl/API/rAMPL.tar.gz", repos=NULL)
```

Note: this package requires R development tools on Windows and macOS, which can be installed as follows:
* Windows: https://cran.r-project.org/bin/windows/Rtools/
* macOS: https://cran.r-project.org/bin/macosx/tools/
* On Linux, this package requires a C++ compiler such as g++.

Alternatively, you can download, build, and install the package locally:
```
$ git clone git@github.com:ampl/rAMPL.git
$ cd rAMPL
$ python updatelib.py
$ cd ..
$ R CMD build rAMPL 
$ R CMD INSTALL rAMPL_<version>.tar.gz
```

#### License

BSD-3

***
Copyright © 2023 AMPL Optimization inc. All rights reserved.