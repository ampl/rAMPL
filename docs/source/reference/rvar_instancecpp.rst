.. _secRrefVarInstance:
.. highlight:: r

VariableInstance
================


.. class:: VariableInstance

  A decision variable instance. Each member of this class belongs to a single
  Variable.
  Note that accessors available here are replicated at Variable level for ease
  of use when dealing with scalar variables.

  All AMPL suffixes for an algebraic variable are available through methods with
  the same name in this class. See http://www.ampl.com/NEW/suffbuiltin.html
  for a list of the available suffixes.

  All the accessors in this class throw an error if the instance
  has been deleted in the underlying AMPL interpreter.

.. method:: VariableInstance.name()

  Returns the name of this instance.

  :return: Name of the instance.

.. method:: VariableInstance.toString()

  Returns a string representation of this instance.

  :return: String representation of this instance.

.. method:: VariableInstance.value()

  Get the current value of this variable.

  :return: Value of the variable.

.. method:: VariableInstance.fix(value=NULL)

  Fix all instances of this variable to their current value, or to the specified value if provided.

  :param float value: The value the variable must be set to.

  :return: ``NULL``.

.. method:: VariableInstance.unfix()

  Unfix this variable instances.

  :return: ``NULL``.

.. method:: VariableInstance.setValue()

  Set the current value of this variable (does not fix it),
  equivalent to the AMPL command `let`

  :param float value: Value to be set.

  :return: ``NULL``.

.. method:: VariableInstance.astatus()

  Get the variable status (fixed, presolved, or substituted out).

  :return: Variable status.
  :rtype: str

.. method:: VariableInstance.defeqn()

  Get the index in `_con` of "defining constraint" used to substitute variable out.

  :return: Index of the defining constraint.
  :rtype: int

.. method:: VariableInstance.dual()

  Get the dual value on defining constraint of variable substituted out.

  :return: Dual value.
  :rtype: float

.. method:: VariableInstance.init()

  Get the current initial guess.

  :return: The initial guess.
  :rtype: float

.. method:: VariableInstance.init0()

  Get the original initial guess (set by `:=` or`default` or by a data statement)

  :return: The original initial guess.
  :rtype: float

.. method:: VariableInstance.lb()

  Returns the current lower bound. See :ref:`secVariableSuffixesNotes`.

  :return: The current lower bound.
  :rtype: float

.. method:: VariableInstance.ub()

  Returns the current upper bound. See :ref:`secVariableSuffixesNotes`.

  :return: The current upper bound.
  :rtype: float

.. method:: VariableInstance.lb0()

  Returns the initial lower bound, from the var declaration.

  :return: The intial lower bound.
  :rtype: float

.. method:: VariableInstance.ub0()

  Returns the initial upper bound, from the var declaration.

  :return: The intial upper bound.
  :rtype: float

.. method:: VariableInstance.lb1()

  Returns the weaker lower bound from AMPL's presolve phase.

  :return: The weaker lower bound.
  :rtype: float

.. method:: VariableInstance.ub1()

  Returns the weaker upper bound from AMPL's presolve phase.

  :return: The weaker upper bound.
  :rtype: float

.. method:: VariableInstance.lb2()

  Returns the stronger lower bound from AMPL's presolve phase.

  :return: The stronger lower bound.
  :rtype: float

.. method:: VariableInstance.ub2()

  Returns the stronger upper bound from AMPL's presolve phase.

  :return: The stronger upper bound.
  :rtype: float

.. method:: VariableInstance.lrc()

  Returns the reduced cost at lower bound.

  :return: The reduced cost at lower bound.
  :rtype: float

.. method:: VariableInstance.urc()

  Returns the reduced cost at upper bound.

  :return: The reduced cost at upper bound.
  :rtype: float

.. method:: VariableInstance.lslack()

  Returns the slack at lower bound (``val - lb``). See :ref:`secVariableSuffixesNotes`.

  :return: The slack at lower bound.
  :rtype: float

.. method:: VariableInstance.uslack()

  Returns the slack at upper bound (``ub - val``). See :ref:`secVariableSuffixesNotes`.

  :return: The slack at upper bound.
  :rtype: float

.. method:: VariableInstance.rc()

  Get the reduced cost (at the nearer bound).

  :return: The reduced cost.
  :rtype: float

.. method:: VariableInstance.slack()

  Returns the bound slack which is the lesser of lslack() and uslack(). See :ref:`secVariableSuffixesNotes`.

  :return: The smaller slack.
  :rtype: float

.. method:: VariableInstance.sstatus()

  Solver status (basis status of variable).

  :return: The basis status of the variable.
  :rtype: str

.. method:: VariableInstance.status()

  AMPL status if not `in`, otherwise solver status

  :return: The status of the variable.
  :rtype: str

