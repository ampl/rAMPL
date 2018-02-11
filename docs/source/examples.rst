.. _secExamplesR:

R API examples
===================

This section lists a few examples in R.
These are the same files that can be found in the *examples* directory of the
distribution, and show the basic usage of the R API.


Example 1: First steps
----------------------

:download:`firstexample.R <../../examples/firstexample.R>`

This example shows how to

* read an AMPL model
* reassign values to parameters
* solve the model
* display the objective function value


Example 2: Get and set AMPL options
-----------------------------------

:download:`optionsexample.R <../../examples/optionsexample.R>`

This example shows how to:

* get and set AMPL options


Example 3: Operate with multidimensional data
---------------------------------------------

:download:`multidimensional.R <../../examples/multidimensional.R>`

This example shows how to:

* Use R ``data.frame`` objects to assign values to multidimensional parameters


Example 4: Assign all data to a model and solve it
--------------------------------------------------

:download:`dietmodel.R <../../examples/dietmodel.R>`

This example shows how to:

* Assign all the data necessary to generate a model instance programmatically


Example 5: Build an efficient frontier
--------------------------------------

:download:`efficientfrontier.R <../../examples/efficientfrontier.R>`

This example shows how to:

* build an efficient frontier by repeteatly solve a portfolio problem in AMPL


Example 6: Simple heuristic
---------------------------

:download:`trackingmodel.R <../../examples/trackingmodel.R>`

This example shows how to:

* Do a simple heuristics for solving a QMIP problem, using the relaxed solution as a hint
