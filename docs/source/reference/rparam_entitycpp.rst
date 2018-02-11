.. _secRrefParamEntity:
.. highlight:: r

Parameter
=========


.. class:: Parameter

  Represents an AMPL parameter. The values can be float or string (in case of
  symbolic parameters).

  Data can be assigned to the set using the methods
  :meth:`~Parameter.set` and :meth:`~Parameter.setValues` or
  using :meth:`~AMPL.setData` and an object of class
  :class:`~DataFrame`.

.. method:: Parameter.isSymbolic()

  Returns true if the parameter is declared as symbolic (can store both numerical and string values).

  :return: ``TRUE`` if the parameter is declared as symbolic.

.. method:: Parameter.hasDefault()

  Check if the parameter has a default initial value. In case of the following AMPL code::

    param a;
    param b default a;

  the function will return ``TRUE`` for parameter ``b``.

  :return: ``TRUE`` if the parameter has a default initial value. Please note
           that if the parameter has a default expression which refers to
           another parameter which value is not defined, this will return true.

.. method:: Parameter.setValues(values)

  If the argument is a `list`,
  assign the specified values to this parameter, assigning them to
  the parameter in the same order as the indices in the entity.
  The number of values in the array must be equal to the
  specified size.

  If the argument is a `data.frame`,
  set the values of this parameter to the correponding values of the `data.frame`
  indexed over the same sets (or a subset). All columns but the last are used as index, and the last is used as value.

  :param list/data.frame values: An array of indices of the instances to be set.

.. method:: Parameter.value()

  Get the value of a scalar parameter.

.. method:: Parameter.set(value)

  Set the value of a scalar parameter.

  :param value: Value to be assigned.

.. method:: Parameter.set(index, value)

  Set the value of a single instance of this parameter.

  :param list index: index of the instance to be set.
  :param value: Value to be assigned.

