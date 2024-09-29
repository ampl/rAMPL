.. _secRrefConInstance:
.. highlight:: r

ConstraintInstance
==================


.. class:: ConstraintInstance

  This class represent an instance of a constraint.

  In general, all AMPL suffixes for a constraint are available through methods
  with the same name in this class. See http://www.ampl.com/NEW/suffbuiltin.html
  for a list of the available suffixes.

  Note that, since this class represents instances of both algebraic and logical
  constraints, some suffixes might not be available for every instance.
  If a wrong suffix for the specific class
  of constraint is accessed, an error is thrown.

  All the accessors in this class throw an error if the instance
  has been deleted in the underlying AMPL interpreter.

.. method:: ConstraintInstance.name()

  Returns the name of this instance.

  :return: Name of the instance.

.. method:: ConstraintInstance.toString()

  Returns a string representation of this instance.

  :return: String representation of this instance.

.. method:: ConstraintInstance.drop()

  Drop this constraint instance, corresponding to the AMPL
  code: `drop constraintname;`

.. method:: ConstraintInstance.restore()

  Restore this constraint instance, corresponding to the
  AMPL code: `restore constraintname;`

.. method:: ConstraintInstance.body()

  Get the current value of the constraint's body.

  :return: The current value of the constraint's body.

.. method:: ConstraintInstance.astatus()

  Get the current AMPL status (dropped, presolved, or substituted out).

  :return: The current AMPL status.

.. method:: ConstraintInstance.defvar()

  Get the index in `_var` of "defined variable" substituted out by the constraint.

  :return: The index of the variable substituted out by the constraint.

.. method:: ConstraintInstance.dinit()

  Get the current initial guess for the constraint's dual variable.

  :return: The current initial guess for the constraint's dual variable.

.. method:: ConstraintInstance.dinit0()

  Get the original initial guess for the constraint's dual variable.

  :return: The original initial guess for the constraint's dual variable.

.. method:: ConstraintInstance.dual()

  Get the current value of the constraint's dual variable.

  Note that dual values are often reset by the underlying AMPL interpreter by
  the presolve functionalities triggered by some methods.
  A possible workaround is to set the option `presolve;` to `false`
  (see :meth:`~.AMPL.setOption`).

  :return: The current value of the constraint's dual variable.

.. method:: ConstraintInstance.lb()

  Get the current value of the constraint's lower bound.

  :return: The current value of the constraint's lower bound.

.. method:: ConstraintInstance.ub()

  Get the current value of the constraint's upper bound.

  :return: The current value of the constraint's upper bound.

.. method:: ConstraintInstance.lbs()

  Get the constraint lower bound sent to the solver (reflecting adjustment
  for fixed variables).

  :return: The constraint lower bound sent to the solver.

.. method:: ConstraintInstance.ubs()

  Get the constraint upper bound sent to the solver (reflecting adjustment
  for fixed variables).

  :return: The constraint upper bound sent to the solver.

.. method:: ConstraintInstance.ldual()

  Get the current dual value associated with the lower bound.

  :return: The current dual value associated with the lower bound.

.. method:: ConstraintInstance.udual()

  Get the current dual value associated with the upper bounds

  :return: The current dual value associated with the upper bound.

.. method:: ConstraintInstance.lslack()

  Get the slack at lower bound `body - lb`.

  :return: The slack at lower bound.

.. method:: ConstraintInstance.uslack()

  Get the slack at upper bound `ub - body`

  :return: The slack at upper bound.

.. method:: ConstraintInstance.slack()

  Constraint slack (the lesser of lslack and uslack).

  :return: The constraint slack.

.. method:: ConstraintInstance.sstatus()

  Get the solver status (basis status of constraint's slack or artificial variable)

  :return: The solver status.

.. method:: ConstraintInstance.status()

  Get the AMPL status if not `in`, otherwise solver status.

  :return: The AMPL status.

.. method:: ConstraintInstance.setDual(dual)

  Set the value of the dual variable associated to this constraint (valid
  only if the constraint is scalar). Equivalent to the AMPL statement:

  `let c := dual;`

  Note that dual values are often reset by the underlying AMPL interpreter by
  the presolve functionalities triggered by some methods.
  A possible workaround is to set the option `presolve` to `false`
  (see :meth:`~.AMPL.setOption`).

  :param float dual: The value to be assigned to the dual variable.

.. method:: ConstraintInstance.val()

  Get the AMPL val suffix. Valid only for logical constraints.

  :return: The val suffix.

