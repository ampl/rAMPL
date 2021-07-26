.. _secRrefEntity:
.. highlight:: r

Entity
======


.. class:: Entity

  Infrastructure class to enable the inheriting classes type-safe access to instances.


.. method:: Entity.name()

  Get the name of this entity.

  :return: The name of this entity.

.. method:: Entity.toString()

   Returns a string representation of this entity (its declaration).

  :return: The string representation of this entity.

.. method:: Entity.indexarity()

  Get the indexarity of this entity (sum of the dimensions of the indexing
  sets).
  This value indicates the arity of the Tuple to be passed to the method
  :meth:`~.Entity.get` in order to access an instance of this entity.
  See the following AMPL examples::

    var x;               # indexarity = 0
    var y {1..2};        # indexarity = 1
    var z {1..2,3..4};   # indexarity = 2
    var zz {{(1, 2)}};   # indexarity = 2

  :return: The sum of the dimensions of the indexing sets or 0 if the entity is not indexed.

.. method:: Entity.isScalar()

  Check whether this entity is scalar. Equivalent to testing whether
  indexarity is equal to zero.

  :return: ``TRUE`` if the entity is scalar (not indexed over any set).

.. method:: Entity.numInstances()

  Get the number of instances in this entity.

  :return: The number of instances in this entity.

.. method:: Entity.getIndexingSets()

  Get a list with the AMPL string representation of the sets on which this entity is
  indexed.

  :return: The string representation of the indexing sets for this entity or an empty list if the entity is scalar.

.. method:: Entity.xref()

  Get the names of all entities which depend on this one.

  :return: A list with the names of all entities which depend on this one.

.. method:: Entity.getValues()

  Get the principal values of this entity as a `data.frame`. The specific returned
  value depends on the type of entity (see list below).

  For:
  * Variables and Objectives it returns the suffix ``val``
  * Parameters it returns their values
  * Constraints it returns the suffix ``dual``
  * Sets it returns all the members of the set. Note that it does not
  * apply to indexed sets. See :meth:`~.SetInstance.getValues`

  :return: A `data.frame` containing the values for all instances.

.. method:: Entity.getValues(suffixes)

  Get the specified suffixes value for all instances in a `data.frame`.

  :param list suffixes: Suffixes to get.

  :return: A `data.frame` containing the specified values.

.. method:: Entity.setValues(data)

  Set the values of this entiy to the correponding values of a
  DataFrame indexed over the same sets (or a subset).
  This function assigns the values in the first data column of
  the passed dataframe to the entity the function is called from.
  In particular, the statement::

    x.setValues(y.getValues())

  is semantically equivalent to the AMPL statement::

    let {s in S} x[s] := y[s];

  :param `data.frame` data: The data to set the entity to.

.. method:: Entity.get(index)

  Get the instance with the specified index.
  Throws an error if an instance with the specified index does not exist,
  if it has been deleted in the underlying AMPL interpreter, or if the index does not match the indexarity.
  Also works for scalar entities with an empty list as argument.

  :param tuple index: The list specifying the index.

  :return: The corresponding instance.

.. method:: Entity.find(index)

  Searches the current entity for an instance with the specified index.

  :return: The wanted entity if found, or ``NULL`` otherwise.

.. method:: Entity.getInstances()

  Get all the instances of this entity.

  :return: A list with all the instances of this entity.

