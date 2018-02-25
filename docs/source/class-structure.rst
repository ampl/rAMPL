.. _secClassStructure:

Class structure
===============

AMPL API library consists of a collection of classes to interact with the underlying AMPL interpreter and to access
its inputs and outputs. It uses generic collections to represent the various entities which comprise a mathematical
model. The structure of these entities is explained in this section.

The main class used to interact with AMPL, instantiate and interrogate the models is :class:`AMPL`.
One object of this class represents an execution of an AMPL translator, and is the first class that has to be instantiated when
developing a solution based on AMPL API. It allows the interaction with the underlying AMPL translator, issuing commands,
getting diagnostics and controlling the process.

The model entities are represented by a set of classes, schematized in figure :ref:`figCDModelEntities`. These classes
represent the optimisation model being created and allow some manipulation and data assignments operations on such entities
and will be presented more in detail in the section :ref:`secModellingClasses`.

.. _figCDModelEntities:

.. figure:: images/ClassDiagramModelEntitiesNew.*
   :align: center
   :width: 836 px
   :height: 480 px
   :alt: Model entities class diagram
   :figClass: align-center

   Model entities classes overview


.. _secAMPLClass:

AMPL class
----------

For all calculations, AMPL API uses an underlying AMPL execution engine, which is wrapped by the class :class:`AMPL`.
Thus, one instance of this class is the first object to be created when writing a program which uses the AMPL API
library. The object is quite resource-heavy, therefore it should be explicitly closed as soon as it is not needed anymore,
with a call to :meth:`.AMPL.close()`
.

All the model creation and structural alteration operations are to be expressed in AMPL language through the
AMPL main object; moreover, the class provides access to the current state represented via the classes derived
from :class:`Entity`, as shown in section :ref:`secRAlgebraicEntitiesReference` and provides several other functionalities
(see :ref:`secReferenceR`).

The functions can be split in three groups: direct AMPL interaction, model interrogation and commands.

Direct interaction with AMPL
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The methods available to input AMPL commands are :meth:`.AMPL.eval()`, :meth:`.AMPL.read()` and :meth:`.AMPL.readData()`;
they send the strings specified (or the specified files) to the AMPL engine for interpretation.


Model interrogation
~~~~~~~~~~~~~~~~~~~

Evaluating AMPL files or statements creates various kind of entities in the underlying AMPL process.
To get the object (or, in general, programmatic) representation of such entities, the programmer can follow two main courses.

* Get a list of all available entities. The methods to obtain such lists are:

  * :meth:`.AMPL.getVariables()` gets the list of all the defined variables
  * :meth:`.AMPL.getConstraints()` gets the list of all the defined constraints
  * :meth:`.AMPL.getObjectives()` gets the list of all the defined objectives
  * :meth:`.AMPL.getSets()` gets the list of all the defined sets
  * :meth:`.AMPL.getParameters()` gets the list of all the defined parameters

* Knowing the AMPL name of an entity, use commands to get the specific entity directly:

  * :meth:`.AMPL.getVariable()` returns the :class:`Variable` representing the AMPL variable with the specified name, if it exists
  * :meth:`.AMPL.getConstraint()` returns the :class:`Constraint` representing the AMPL constraint with the specified name, if it exists
  * :meth:`.AMPL.getObjective()` returns the :class:`Objective` representing the AMPL objective with the specified name, if it exists
  * :meth:`.AMPL.getParameter()` returns the :class:`Parameter` representing the AMPL parameter with the specified name, if it exists
  * :meth:`.AMPL.getSet()` returns the :class:`Set` representing the AMPL set with the specified name, if it exists


Once the desired entities have been created, it is possible to use their properties and methods to manipulate the model
and to extract or assign data. Updating the state of the programmatic entities is implemented lazily and uses proper
dependency handling. Communication with the underlying engine is therefore executed only when an entity's properties
are being accessed and only when necessary.
An entity is invalidated (needs refreshing) if one of the entities it depends from has been manipulated or if a generic
AMPL statement evaluation is performed (through :meth:`.AMPL.eval()` or similar routines). This is one of the reasons
why it is generally better to use the embedded functionalities (e.g. fixing a variable through the corresponding API
function call) than using AMPL statements: in the latter case, the API invalidates all entities, as the effects of
such generic statements cannot be predicted.
Refreshing is transparent to the user, but must be taken into account when implementing functions
which access data or modify entities frequently.


Commands and options
~~~~~~~~~~~~~~~~~~~~

Some AMPL commands are encapsulated by functions in the :class:`AMPL` class for ease of access.
These comprise :meth:`.AMPL.solve()` and others.
To access and set options in AMPL, the functions :meth:`.AMPL.getOption()` and :meth:`.AMPL.setOption()` are provided.
These functions provide an easier programmatic access to the AMPL options.
In general, when an encapsulation is available for an AMPL command, the programmatic access to it is to be preferred to calling the same command using
:meth:`.AMPL.eval()`.


Output and errors handling
~~~~~~~~~~~~~~~~~~~~~~~~~~

The output from the AMPL translator is handled implementing an output handling function,
which will be called at each block of output from the translator. The current output handler
can be accessed and set via :meth:`.AMPL.getOutputHandler()` and :meth:`.AMPL.setOutputHandler()`;
the default output handler prints each block to the standard console output.

Error handling is two-faced:

* Errors coming from the underlying AMPL translator (e.g. syntax errors and warnings obtained calling the :meth:`.AMPL.eval()` method)
  are handled by the error handling function which can be set and get via :meth:`.AMPL.getErrorHandler()`
  and :meth:`.AMPL.setErrorHandler()`.
* Generic errors coming from the API, which are detected outside the translator are thrown as exceptions.

The default implementation of the error handler prints errors and warnings to stdout.



.. _secModellingClasses:

Modelling entities classes
--------------------------

This group of classes represents the basic entities of an AMPL optimisation
model: variables, constraints, objectives, parameters and sets.
They are used to access the current state of the AMPL translator
(e.g. to find the values of a variable), and to some extent they can be
used for data input (e.g. assign values to a parameter, fix a variable).

Objects of these classes cannot be created programmatically by the user: the model creation and structural
modification is handled in AMPL (see section :ref:`secAMPLClass`), through the methods :meth:`.AMPL.eval()`
and :meth:`.AMPL.read()`. The base class is :class:`Entity`.

The classes derived from :class:`Entity` represent algebraic entites
(e.g. a variable indexed over a set in AMPL), and are implemented as a map
from an object (number, string or tuple) to an instance which allow access
to its instances (method
:meth:`Entity.get()`, or ``[[ ]]`` operator).
The case of scalar entities (like the AMPL entity defined by ``var x;``) is handled at Entity level, and will be
illustrated in the paragraph regarding instances below.
The derived classes are: :class:`Variable`, :class:`Constraint`, :class:`Parameter`,
:class:`Objective` and :class:`Set`.

Any instance object represents a single instance of an algebraic entity
(e.g.  the value of a variable for a specific value of its indexing set),
and is treated as a scalar entity.
Entities and instances are both handled by the class :class:`Entity`.
An entity (algebraic entity in AMPL)
can contain various instance objects (instances in AMPL), while each instance has to be part of exactly one
entity. The exact methods and properties of the entity depend on the particular kind of entity under consideration
(i.e. variable, constraint, parameter).

As an example, for indexed entities, the class :class:`Variable` has functionalities like :meth:`Variable.fix()` and :meth:`Variable.unfix()`,
which would fix or unfix all instances which are part of the algebraic entity, and for instances the
class :class:`Variable` has properties like :meth:`Variable.value()`
and :meth:`Variable.dual()` (together with instance level fix and unfix methods).

The class :class:`Constraint` has functionalities like :meth:`Constraint.drop()` and
:meth:`Constraint.restore()` on its entity level,
and on its instance level it has properties like :meth:`Constraint.body()` and
:meth:`Constraint.dual()`
(and methods like drop and restore for the single instance).

Note that the class :class:`Parameter`, which represent an algebraic parameter, represents
its instances by objects (numbers or strings) and therefore does not have special methods
on its instance level.


.. _secAccessInstancesAndValues:

Access to instances and values
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The instances can be accessed from the parent entity through functions like :meth:`Entity.get()`, available for
all entity classes or via the indexing operator.
All data corresponding to the entity can be accessed through the instances, but the computational overhead of such kind of
access is quite considerable. To avoid this, the user can gain bulk data access through a ``data.frame`` object;
reference to these object can be obtained using :meth:`Entity.getValues` methods.
In case of scalar entities (e.g. the entity declared in AMPL with the statement ``var x;``), all the instance specific methods are
replicated at Entity level, to allow the code fragment ``value <- x$value()`` instead of the more explicit ``value <- x$get()$value()``.
See example below:


.. code-block:: R

   library(rAMPL)
   ampl <- new(AMPL)
   ampl$eval("var x;")
   x <- ampl$getVariable("x")
   value <- x$value()        # Compact access to scalar entities
   value <- x$get()$value()  # Access through explicit reference to the instance


**Scalar Entities** In general, as seen above, access to an instance of a scalar entity is not needed, as all functionalities of the instance are replicated at entity level in this case. Anyway,
to gain explicit access to an instance, the function :meth:`Entity.get()` can be used without parameters, as shown below.

.. code-block:: R

   library(rAMPL)
   ampl <- new(AMPL)
   ampl$eval("var x;")
   x <- ampl$getVariable("x")$get()

**Indexed Entities** Instances of indexed entities can be accessed as shown below:

.. code-block:: R

   library(rAMPL)
   ampl <- new(AMPL)
   ampl$eval("var x{1..2, 4..5, 7..8};")
   x <- ampl$getVariable("x")

   # Option 1:
   instance <- x[[c(1, 4, 7)]]
   # Option 2:
   instance <- x$get(c(1, 4, 7))

   index <- c(1, 4, 7)
   # Option 3:
   instance <- x[[index]]
   # Option 4:
   instance <- x$get(index)


AMPL API allows access to the instances through lists. See the examples below which use
the same declarations of the example above to illustrate how to:

* Find if an instance exists or not
* Enumerate all the instances

.. code-block:: R

  # Find using R
  t <- c(1, 2, 100)
  instance <- x$find(t)
  if (is.null(instance)) {
    print("Instance not found")
  }

  # Create a list mapping each instance name to the corresponding instance
  instances <- x$getInstances()

  # Iterate over all instances
  for (instance in instances) {
    print(instance$name())
  }

  # Iterate over all instance names and access each instance using the indexing operator
  for (name in names(instances)) {
    print(instances[[name]]$name())
  }


The currently defined entities are obtained from the various get methods of the :class:`AMPL` object
(see section :ref:`secAMPLClass`). Once a reference to an entity is created, the entity is automatically kept up-to-date
with the corresponding entity in the AMPL interpreter. That is, if a reference to a newly created AMPL variable
is obtained by means of :meth:`.AMPL.getVariable()`, and the model the variable is part of is then solved
by means of :meth:`.AMPL.solve()`, the values of the instances of the variable will automatically be updated.
The following code snippet should demonstrate the concept.

.. code-block:: R

   ampl$eval("var x;")
   ampl$eval("maximize z: x;")
   ampl$eval("subject to c: x<=10;")
   x <- ampl$getVariable("x")

   # At this point x$value() evaluates to 0
   print(x$value())  # prints 0

   ampl$solve()

   # At this point x$value() evaluates to 10
   print(x$value())  # prints 10


Relation between entities and data
----------------------------------

The entities and instances in AMPL store data (numbers or strings) and can be indexed, hence the instances available depend
on the values in the indexing set(s).  The order in which these indexing sets is handled in the AMPL entities is
not always consistent with the ordering in which the data for such sets is defined, so it is often desirable, even when interested
in only data (decoupled from the AMPL entities) to keep track of the indexing values which corresponds to each value.

Moreover, when dealing with AMPL entities (like :class:`Variable`), consistency is guaranteed for every instance.
This means that, if a reference to an instance is kept and in the underlying AMPL interpreter the value of the instance
is changed, the value read from the instance object will be always consistent with the AMPL value and, if an instance is
deleted in AMPL, an exception will be thrown when accessing it. This has the obvious benefit of allowing the user to rely
on the values of the instances, but has a price in terms of computational overhead. For example, accessing in this way the value
of 1000 instances:

.. code-block:: R

  library(rAMPL)
  ampl <- new(AMPL)
  ampl$eval("set A := 1..1000; param c{i in A} default 0; var x{i in 1..1000} := c[i];")

  # Enumerate through all the instances of c and set their values
  c <- ampl$getParameter("c")
  for (i in 1:c$numInstances()) {
    c[[i]] <- i*1.1
  }

  # Enumerate through all the instances and print their values
  x <- ampl$getVariable("x")
  for (xi in x$getInstances()) {
    cat(xi$value(), "\n")
  }


will check at each access if the referenced instance is valid or not, resulting in a computational overhead.

To ease data communication and handling, R ``data.frame`` objects can be used to:

* Define data for multiple parameters in one single call to the underlying interpterer
* Decouple data and entities, reducing the computational overhead

R ``data.frame`` objects should therefore be used in these circumnstances, together with the methods
:meth:`.AMPL.setData()` and :meth:`Entity.getValues()`.

.. code-block:: R

  library(rAMPL)
  # Create a new data.frame with one indexing column (A) and another column (c)
  df <- data.frame(A=1:1000, c=1:1000*1.1)

  # Or, alternatively (much slower):
  df <- data.frame(A=c(), c=c())
  for (i in 1:1000) {
    df <- rbind(df, c(i, i*1.1))
  }

  ampl <- new(AMPL)
  ampl$eval("set A; param c{i in A} default 0; var x{i in A} := c[i];")

  # Assign data to the set A and the parameter c in one line
  ampl$setData(df, 1, "A")

  x <- ampl$getVariable("x")
  # From the following line onwards, df is uncoupled from the modelling system
  df <- x$getValues()

  # Prints the data.frame
  print(df)

.. _secAccessToScalars:

Access to scalar values
~~~~~~~~~~~~~~~~~~~~~~~

Simplified access to scalar values, like the value of a scalar variable or parameter or, in general, any
AMPL expression that can be evaluated to a single string or number, is possible using the convenience method :meth:`.AMPL.getValue()`.
This method will fail if called on an AMPL expression which does not evaluate to a single value. See below for an example:


.. code-block:: R

  library(rAMPL)
  ampl <- new(AMPL)
  ampl$eval("var x{i in 1..3} := i;")
  ampl$eval("param p symbolic := 'test';")
  ampl$eval("param pp := 4;")
  # x2 will have the value 2
  print(ampl$getValue("x[2]"))
  # p will have the value "test"
  print(ampl$getValue("p"))
  # pp will have the value 4
  print(ampl$getValue("pp"))


.. _secVariableSuffixesNotes:

Note on variables suffixes
--------------------------

For AMPL versions prior to 20150516, there was a glitch with
v.lb, v.ub, v.lslack, v.uslack, and v.slack where v is a variable
instantiated without need of presolve and after one or more
other variables have been instantiated.  Example:

.. code-block:: ampl

    var x <= 0;
    var y <= 0;
    display y.lb;
    display x.ub;
    # x.ub was wrong (with separate display commands)
    # but all went well with "display y.lb, x.ub;"
