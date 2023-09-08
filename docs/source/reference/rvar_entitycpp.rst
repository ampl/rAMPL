.. _secRrefVarEntity:
.. highlight:: r

Variable
========


.. class:: Variable

  Represents an AMPL decision variable. Note that, in case of a scalar
  variable, all the properties of the variable instance can be accessed
  through methods like :meth:`~.Variable.value`. The methods have the
  same name of the corresponding AMPL suffixes.
  See https://www.ampl.com/NEW/suffbuiltin.html for a list of the available
  suffixes.

  All these methods throw an error if called on an entity which has been deleted
  in the underlying intepreter.

  To gain access to all the values in an entity (for all instances and all
  suffixes for that entities), see :meth:`~.Entity.getValues` and the
  :class:`DataFrame` class.


.. method:: Variable.value()

  Get the current value of this variable.

  :return: Value of the variable.

.. method:: Variable.integrality()

  Get the integrality type for this variable.

  :return: Integrality type of the variable ("C" - continuous, "B" - binary, "I" - integer).
  :rtype: str

.. method:: Variable.fix(value=NULL)

  Fix all instances of this variable to their current value, or to the specified value if provided.

  :param float value: The value the variable must be set to.

  :return: ``NULL``.

.. method:: Variable.unfix()

  Unfix this variable instances.

  :return: ``NULL``.

.. method:: Variable.setValue()

  Set the current value of this variable (does not fix it),
  equivalent to the AMPL command `let`

  :param float value: Value to be set.

  :return: ``NULL``.

.. method:: Variable.astatus()

  Get the variable status (fixed, presolved, or substituted out).

  :return: Variable status.
  :rtype: str

.. method:: Variable.defeqn()

  Get the index in `_con` of "defining constraint" used to substitute variable out.

  :return: Index of the defining constraint.
  :rtype: int

.. method:: Variable.dual()

  Get the dual value on defining constraint of variable substituted out.

  :return: Dual value.
  :rtype: float

.. method:: Variable.init()

  Get the current initial guess.

  :return: The initial guess.
  :rtype: float

.. method:: Variable.init0()

  Get the original initial guess (set by `:=` or`default` or by a data statement)

  :return: The original initial guess.
  :rtype: float

.. method:: Variable.lb()

  Returns the current lower bound. See :ref:`secVariableSuffixesNotes`.

  :return: The current lower bound.
  :rtype: float

.. method:: Variable.ub()

  Returns the current upper bound. See :ref:`secVariableSuffixesNotes`.

  :return: The current upper bound.
  :rtype: float

.. method:: Variable.lb0()

  Returns the initial lower bound, from the var declaration.

  :return: The intial lower bound.
  :rtype: float

.. method:: Variable.ub0()

  Returns the initial upper bound, from the var declaration.

  :return: The intial upper bound.
  :rtype: float

.. method:: Variable.lb1()

  Returns the weaker lower bound from AMPL's presolve phase.

  :return: The weaker lower bound.
  :rtype: float

.. method:: Variable.ub1()

  Returns the weaker upper bound from AMPL's presolve phase.

  :return: The weaker upper bound.
  :rtype: float

.. method:: Variable.lb2()

  Returns the stronger lower bound from AMPL's presolve phase.

  :return: The stronger lower bound.
  :rtype: float

.. method:: Variable.ub2()

  Returns the stronger upper bound from AMPL's presolve phase.

  :return: The stronger upper bound.
  :rtype: float

.. method:: Variable.lrc()

  Returns the reduced cost at lower bound.

  :return: The reduced cost at lower bound.
  :rtype: float

.. method:: Variable.urc()

  Returns the reduced cost at upper bound.

  :return: The reduced cost at upper bound.
  :rtype: float

.. method:: Variable.lslack()

  Returns the slack at lower bound (``val - lb``). See :ref:`secVariableSuffixesNotes`.

  :return: The slack at lower bound.
  :rtype: float

.. method:: Variable.uslack()

  Returns the slack at upper bound (``ub - val``). See :ref:`secVariableSuffixesNotes`.

  :return: The slack at upper bound.
  :rtype: float

.. method:: Variable.rc()

  Get the reduced cost (at the nearer bound).

  :return: The reduced cost.
  :rtype: float

.. method:: Variable.slack()

  Returns the bound slack which is the lesser of lslack() and uslack(). See :ref:`secVariableSuffixesNotes`.

  :return: The smaller slack.
  :rtype: float

.. method:: Variable.sstatus()

  Solver status (basis status of variable).

  :return: The basis status of the variable.
  :rtype: str

.. method:: Variable.status()

  AMPL status if not `in`, otherwise solver status

  :return: The status of the variable.
  :rtype: str

