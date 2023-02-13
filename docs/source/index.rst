.. _amplapi:



AMPL R API
==========

``rAMPL`` is an interface that allows developers to access the features of `AMPL <https://ampl.com>`_ from within R.
For a quick introduction to AMPL see `Quick Introduction to AMPL <https://dev.ampl.com/ampl/introduction.html>`_.

All model generation and solver interaction is handled directly by AMPL, which leads to
great stability and speed; the library just acts as an intermediary, and the added overhead (in terms of memory and
CPU usage) depends mostly on how much data is sent and read back from AMPL, the size of the expanded model as such is irrelevant.
With ``rAMPL`` you can model and solve large scale optimization problems in R with the performance of heavily optimized C code
without losing model readability.

Contents
--------

.. toctree::
   :maxdepth: 2

   intro
   getting-started
   class-structure
   quick-start
   reference
   examples
