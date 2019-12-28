.. _secRQuickStart:

R quick start
==================

This section will show a simple example to illustrate various functionalities of the AMPL R interface.
The full example prints the version of the AMPL interpreter used, loads a model from file and the corresponding
data file, solves it, gets some of the AMPL entities in R and uses them to get the results and to assign data
programmatically. This section assumes that you are already familiar with the R language.
Full class reference is given in :ref:`secReferenceR`.


Complete listing
----------------

This is the complete listing of the example. Please note that, for clarity of presentation, all the code in the examples below does not include exception handling.

.. code-block:: R

  library(rAMPL)
  # Create an AMPL instance
  ampl <- new(AMPL)

  ## If the AMPL installation directory is not in the system search path:
  # env <- new(Environment, "full path to the AMPL installation directory")
  # ampl <- new(AMPL, env)

  # Interpret the two files
  ampl$read("models/diet.mod")
  ampl$readData("models/diet.dat")

  # Solve
  ampl$solve()

  # Get objective entity by AMPL name
  totalcost <- ampl$getObjective("Total_Cost")
  # Print it
  cat(sprintf("Objective is: %g\n", totalcost$value()))

  # Reassign data - specific instances
  cost <- ampl$getParameter("cost")
  cost$setValues(data.frame(index=c("BEEF", "HAM"), value=c(5.01, 4.55)))
  cat("Increased costs of beef and ham.\n")

  # Resolve and display objective
  ampl$solve()
  cat(sprintf("New objective value: %g\n", totalcost$value()))

  # Reassign data - all instances
  cost$setValues(c(3, 5, 5, 6, 1, 2, 5.01, 4.55))

  cat("Updated all costs.\n")

  # Resolve and display objective
  ampl$solve()
  cat(sprintf("New objective value: %g\n", totalcost$value()))

  # Get the values of the variable Buy in a dataframe object
  buy <- ampl$getVariable("Buy")
  df <- buy$getValues()
  # Print them
  print(df)

  # Get the values of an expression into a DataFrame object
  df2 <- ampl$getData("{j in FOOD} 100*Buy[j]/Buy[j].ub")
  # Print them
  print(df2)

Needed headers and AMPL environment creation
--------------------------------------------

For a simple hello world program, first load the `rAMPL` library.

.. code-block:: R

  library(rAMPL)

Then copy the following statements to have a hello world application which gets the value
of the option `version` as defined in the underlying AMPL executable and prints the result
on the console.

.. code-block:: R

   ampl <- new(AMPL)
   cat(ampl$getOption("version"), "\n")


The first line creates a new AMPL object with all default settings, incapsulated in a smart pointer to ensure resource deletion.
The second, which is the preferred way to access AMPL options, gets the value of the option
`version` from AMPL as a string and prints the result on the active console.


If the AMPL installation directory is not in the system search path, you should create
the AMPL object as follows instead:

.. code-block:: R

   library(rAMPL)
   env <- new(Environment, "full path to the AMPL installation directory")
   ampl <- new(AMPL, env)

Note that you may need to escape backslashes (e.g., `'C:\\\\\\ampl\\\\\\ampl.mswin64'`) if included in the path.


Load a model from file
----------------------

The following lines use the method :meth:`AMPL.read` to load a model and data stored in external (AMPL) files.
If the files are not found, an IOError is thrown.

.. code-block:: R

   ampl$read("models/diet/diet.mod")
   ampl$readData("models/diet/diet.dat")

Once these commands are executed, the AMPL interpreter will have interpreted the content of the two files.
No further communication is made between the AMPL interpreter and the R object, as every entity is created lazily (as needed).

Solve a problem
---------------

To solve the currently loaded problem instance, it is sufficient to issue the command:

.. code-block:: R

   ampl$solve()


Get an AMPL entity in the programming environment (get objective value)
-----------------------------------------------------------------------

AMPL API provides R representations of the AMPL entities. Usually, not all the entities are
of interest for the programmer. The generic procedure is:

1. Identify the entities that need interaction (either data read or modification)
2. For each of these entities, get the entity through the AMPL API using one of the
   following functions: :meth:`AMPL.getVariable()`,
   :meth:`AMPL.getConstraint()`, :meth:`AMPL.getObjective()`,
   :meth:`AMPL.getParameter()` and :meth:`AMPL.getSet()`.


.. code-block:: R

    totalcost <- ampl$getObjective("Total_Cost")
    cat(sprintf("Objective is: %g\n", totalcost$get()$value()))

It can be noted that we access an Objective to interrogate AMPL API about the objective function.
It is a collections of objectives. To access the single instance, the function get() should be used in
case of the objective, which gets the only instance of the objective.
Since objectives are often single instance, the value() function has been implemented in the class  :class:`Objective`.
So, equivalently to the call above, the following call would return the same value, as it gives direct access
to the objective function value:

.. code-block:: R

   totalcost$value()

The output of the snippet above is::

   Objective is: 118.05940323955669

The same is true for all other entities.

Modify model data (assign values to parameters)
-----------------------------------------------

The input data of an optimization model is stored in its parameters; these can be scalar or vectorial entities.
Two ways are provided to change the value of vectorial parameter: change specific values or change all values at
once. The example shows an example of both ways, reassigning the values of the parameter costs firstly specifically,
then altogether. Each time, it then solves the model and get the objective function. The function used to change the
values is overloaded, and is in both cases :meth:`Parameter.setValues()`.

.. code-block:: R

   cost <- ampl$getParameter("cost")
   cost$setValues(data.frame(index=c("BEEF", "HAM"), value=c(5.01, 4.55)))
   cat("Increased costs of beef and ham.\n")
   ampl$solve()
   cat(sprintf("New objective value: %g\n", totalcost$value()))

The code above assigns the values 5.01 and 4.55 to the parameter cost for the objects beef and ham respectively.
If the order of the indexing of an entity is known (i.e. for multiple reassignment), it is not necessary to specify
both the index and the value. A collection of values is assigned to each of the parameter values, in the order they are represented in AMPL.

.. code-block:: R

   cost$setValues(c(3, 5, 5, 6, 1, 2, 5.01, 4.55))
   cat("Updated all costs.\n")
   ampl$solve()
   cat(sprintf("New objective value: %g\n", totalcost$value()))

The statements above produce the following output::

   Objective is: 118.05940323955669
   Increased costs of beef and ham.
   New objective value: 144.41572037510653
   Updated all costs
   New objective value: 164.54375000000002

Get numeric values from variables
---------------------------------

To access all the numeric values contained in a Variable or any other entity, use a R ``data.frame`` object. Doing so, the data is detached from the entity, and there is a considerable performance gain. To do so, we first get the Variable object from AMPL, then we get its data with the function :meth:`Entity.getValues()`.

.. code-block:: R

   # Get the values of the variable Buy in a dataframe object
   buy <- ampl$getVariable("Buy")
   df <- buy$getValues()
   # Print the data.frame
   print(df)


Get arbitrary values via ampl expressions
-----------------------------------------

Often we are interested in very specific values coming out of the optimization session. To make use of the power of AMPL expressions and avoiding
cluttering up the environment by creating entities, fetching data through arbitrary AMPL expressions is possible. For this model, we are interested
in knowing how close each decision variable is to its upper bound, in percentage.
We can obtain this data into a dataframe using the function :meth:`AMPL.getData()` with the code :

.. code-block:: R

  # Get the values of an expression into a DataFrame object
  df2 = ampl$getData("{j in FOOD} 100*Buy[j]/Buy[j].ub")
  # Print the data.frame
  print(df2)


Delete the AMPL object to free the resources
-----------------------------------------------------

It is good practice to make sure that the AMPL object is closed and all its resources released when it is not needed any more.
All the internal resources are automatically deallocated by the destructor of the AMPL object, so it is suggested to keep it stored
by value.
