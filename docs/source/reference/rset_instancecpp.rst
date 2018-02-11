.. _secRrefSetInstance:
.. highlight:: r

SetInstance
===========


.. class:: SetInstance



.. method:: SetInstance.name()

  Returns the name of this instance.

  :return: Name of the instance.

.. method:: SetInstance.toString()

  Returns a string representation of this instance.

  :return: String representation of this instance.

.. method:: SetInstance.size()

  Get the number of tuples in this set. Valid only for non indexed sets.

  :return: The number of tuples in the set.

.. method:: SetInstance.members()

  Get the members of this Set. Valid only for non indexed sets.

  :return: The list of members of the set.

.. method:: SetInstance.contains(tuple)

  Check wether this set instance contains the specified tuple.

  :return: `TRUE` if this set instance contains the specified tuple.

.. method:: SetInstance.getValues()

  Get values of this set in a data.frame. Valid only for non indexed sets.

  :return: `data.frame` containing the values of this set.

.. method:: SetInstance.setValues(values)

  Set values. Valid only for non indexed sets.

