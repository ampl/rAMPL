.. _secRrefObjInstance:
.. highlight:: r

ObjectiveInstance
=================


.. class:: ObjectiveInstance

  Represents an AMPL objective. Note that, in case of a scalar objective, all
  the properties (corresponding to AMPL suffixes) of the objective instance
  can be accessed through methods like :meth:`~.ObjectiveInstance.value`.
  The methods have the same name of the corresponding AMPL suffixes.
  See https://www.ampl.com/NEW/suffbuiltin.html for a list of the available
  suffixes.

  All these methods throw an error if called on an entity which has been deleted
  in the underlying intepreter.

  To gain access to all the values in an entity (for all instances and all
  suffixes for that entities), see :meth:`~.Entity.getValues` and the
  :class:`DataFrame` class.

.. method:: ObjectiveInstance.name()

  Returns the name of this instance.

  :return: Name of the instance.

.. method:: ObjectiveInstance.toString()

  Returns a string representation of this instance.

  :return: String representation of this instance.

.. method:: ObjectiveInstance.value()

  Get the value of the objective instance.

  :return: Value of the objective.

.. method:: ObjectiveInstance.astatus()

  Return the AMPL status.

  :return: The AMPL status.

.. method:: ObjectiveInstance.sstatus()

  Return the solver status.

  :return: The solver status.

.. method:: ObjectiveInstance.exitcode()

  Exit code returned by the solver after most recent solve with this objective.

  :return: The exit code returned by the solver.

.. method:: ObjectiveInstance.message()

  Result message returned by solver after most recent solve with this objective.

  :return: The result message returned by the solver.

.. method:: ObjectiveInstance.result()

  Result string returned by solver after most recent solve with this objective.

  :return: The result message returned by the solver.

.. method:: ObjectiveInstance.drop()

  Drop this objective.

.. method:: ObjectiveInstance.restore()

  Restore this objective  (if it had been dropped, no effect otherwise)

.. method:: ObjectiveInstance.message()

  Get the sense of this objective

  :return: ``TRUE`` if minimize, ``FALSE`` if maximize.

