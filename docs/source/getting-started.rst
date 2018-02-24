.. lblGettingStarted:

Getting started
===============

Installation
------------

The AMPL API can function as an add-on to any existing AMPL installation.
If you do not yet have an AMPL installation on the computer where you will
be working with the API, see our
`demo page <http://ampl.com/try-ampl/download-a-free-demo/>`_ or
`trial page <http://ampl.com/try-ampl/request-a-full-trial/>`_ to download a
working version that can be installed quickly.

In order to install the latest version of the R API you just need to run:

.. code-block:: R

    install.packages("Rcpp", type="source")
    install.packages("https://ampl.com/dl/API/rAMPL.tar.gz", repos=NULL)

Alternatively, you can install a specific version as follows:

.. code-block:: R

    install.packages("https://ampl.com/dl/API/future/<version>/rAMPL_<version>.tar.gz", repos=NULL)

Initial test
------------

To begin, open a R console and set the working directory to the directory containing the examples:

.. code-block:: bash

    setwd(paste(find.package("rAMPL"), "examples", sep="/"))

To complete an initial test, run ``firstexample.R`` with

.. code-block:: R

   source("firstexample.R")
   firstexample(solver=NULL)

where optionally ``solver="<solver>"`` is the name of a solver that has been installed with AMPL.
(If a solver is not specified, AMPL's default choice will be used.) This will solve
several small diet problems and then display the optimal amounts of the foods
from the last solution.

Note that the folder containing the AMPL executable should be in the system search path.
Otherwise, the error message "AMPL could not be started" will be shown.
If the AMPL installation directory is not in the system search path,
you can add it by running the following command before loading the library.

.. code-block:: R

   Sys.setenv(PATH = paste(Sys.getenv("PATH"), "full path to the AMPL installation directory", sep = ";"))

Note that you may need to escape backslashes (e.g., `'C:\\\\\\ampl\\\\\\ampl.mswin64'`) if included in the path.


Development
-----------

Load the ``rAMPL`` library with

.. code-block:: R

   library(rAMPL)

Together with your existing AMPL implementation, this will provide the full
object library and access to all AMPL functions. Please make sure that the
folder containing the AMPL executable is in the system search path.

Deployment
----------

To deploy AMPL API applications to users who do not have their own AMPL installations,
include with your application the AMPL executable (``ampl`` or ``ampl.exe``), and the ``rAMPL`` library.
Note that the folder containing the AMPL executable should be in the system search path.
