.. _secRrefSetEntity:
.. highlight:: r

Set
===


.. class:: Set

  Represents an AMPL set. In case of not indexed sets, this class exposes
  iterators for accessing its elements. The members of the set are tuples.
  All these methods throw a TypeError if called for an indexed set.

  In case of indexed sets, you can gain access to the instances using the
  operator [].

  All the accessors in this class throw an RuntimeError if the instance has
  been deleted in the underlying AMPL interpreter.

  Data can be assigned to the set using the methods
  :meth:`~Set.setValues` (for non-indexed sets only) or using
  :meth:`~AMPL.setData` and an object of class
  :class:`~DataFrame`.


.. method:: Set.arity()

  The arity of the set, or number of components in each member of this set.

  :return: The arity of the set.

.. method:: Set.size()

  Get the number of tuples in this set. Valid only for non indexed sets.

  :return: The number of tuples in the set.

.. method:: Set.members()

  Get the members of this Set. Valid only for non indexed sets.

  :return: The list of members of the set.

.. method:: Set.contains(tuple)

  Check wether this set instance contains the specified tuple.

  :return: `TRUE` if this set instance contains the specified tuple.

.. method:: Set.getValues()

  Get values of this set in a data.frame. Valid only for non indexed sets.

  :return: `data.frame` containing the values of this set.

.. method:: Set.setValues(values)

  Set values. Valid only for non indexed sets.

