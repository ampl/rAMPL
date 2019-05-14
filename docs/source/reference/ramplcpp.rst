.. _secRrefAMPL:
.. highlight:: r

AMPL
====


.. class:: AMPL

  An AMPL translator.

  An object of this class can be used to do the following tasks:

  - Run AMPL code. See :meth:`~.AMPL.eval` and
    :meth:`~.AMPL.evalAsync`.
  - Read models and data from files. See :meth:`~.AMPL.read`,
    :meth:`~.AMPL.readData`, :meth:`~.AMPL.readAsync`, and
    :meth:`~.AMPL.readDataAsync`.
  - Solve optimization problems constructed from model and data (see
    :meth:`~.AMPL.solve` and :meth:`~.AMPL.solveAsync`).
  - Access single Elements of an optimization problem. See
    :meth:`~.AMPL.getVariable`, :meth:`~.AMPL.getConstraint`,
    :meth:`~.AMPL.getObjective`, :meth:`~.AMPL.getSet`,
    and :meth:`~.AMPL.getParameter`.
  - Access lists of available entities of an optimization problem. See
    :meth:`~.AMPL.getVariables`, :meth:`~.AMPL.getConstraints`,
    :meth:`~.AMPL.getObjectives`, :meth:`~.AMPL.getSets`,
    and :meth:`~.AMPL.getParameters`.

  Error handling is two-faced:

  - Errors coming from the underlying AMPL translator (e.g. syntax errors and
    warnings obtained calling the eval method) are handled by
    the :class:`~amplpy.ErrorHandler` which can be set and get via
    :meth:`~.AMPL.getErrorHandler` and
    :meth:`~.AMPL.setErrorHandler`.
  - Generic errors coming from misusing the API, which are detected in
    R, are thrown as exceptions.

  The default implementation of the error handler prints errors and warnings to the console.

  The output of every user interaction with the underlying translator is
  handled implementing the abstract class :class:`~amplpy.OutputHandler`.
  The (only) method is called at each block of output from the translator.
  The current output handler can be accessed and set via
  :meth:`~.AMPL.getOutputHandler` and
  :meth:`~.AMPL.setOutputHandler`.

.. function:: AMPL()

  Default constructor.

  :raises Error: If no valid AMPL license has been found or if the translator
    cannot be started for any other reason.

.. function:: AMPL(environment)

  Constructor: creates a new AMPL instance with the specified environment.
  This allows the user to specify the location of the AMPL binaries to be used
  and to modify the environment variables in which the AMPL interpreter will
  run.

  :param env: The AMPL environment.
  :type env: :py:class:`Environment`
  :raises Error: If no valid AMPL license has been found or if the translator
    cannot be started for any other reason.

.. method:: AMPL.toString()

  Get a string describing the object. Returns the version of the API and
  either the version of the interpreter or the message "AMPL is not
  running" if the interpreter is not running (e.g. due to unexpected
  internal error or to a call AMPL::close)

  :return: A string that represents this object.

.. method:: AMPL.cd(path = NULL)

  Change or display the current working directory (see
  https://en.wikipedia.org/wiki/Working_directory).

  :param str path:  New working directory or null (to display the working directory).
  :type path: str or ``NULL``
  :return: The current working directory.

.. method:: AMPL.setOption(name, value)

  Set an AMPL option to a specified value.

  :param str name: Name of the option to be set (alphanumeric without spaces).
  :param value: string/number/boolean representing the value the option must be set to.
  :raises Error: If the option name is not valid.

.. method:: AMPL.getOption(name)

  Get the current value of the specified option. If the option does not
  exist, returns ``NA``.

  :param str name: Option name (alphanumeric)
  :return: Value of the option as a string or ``NA``.
  :raises Error: If the option name is not valid.

.. method:: AMPL.getDblOption(name)

  Get the current value of the specified double option. If the option does not
  exist, returns ``NA``.

  :param str name: Option name (alphanumeric)
  :return: Value of the option as numeric or ``NA``.
  :raises Error: If the option name is not valid, or if the value could not be casted.

.. method:: AMPL.getIntOption(name)

  Get the current value of the specified integer option. If the option does not
  exist, returns ``NA``.

  :param str name: Option name (alphanumeric)
  :return: Value of the option as numeric or ``NA``.
  :raises Error: If the option name is not valid, or if the value could not be casted.

.. method:: AMPL.getBoolOption(name)

  Get the current value of the specified boolean option. If the option does not
  exist, returns ``NA``.

  :param str name: Option name (alphanumeric)
  :return: Value of the option as boolean or ``NA``.
  :raises Error: If the option name is not valid, or if the value could not be casted.

.. method:: AMPL.read(fileName)

  Interprets the specified file (script or model or mixed). As a side effect,
  it invalidates all entities (as the passed file can contain any arbitrary
  command); the lists of entities will be re-populated lazily (at first
  access)

  :param str fileName: Full path to the file.
  :raises Error: In case the file does not exist.

.. method:: AMPL.readData(fileName)

  Interprets the specified file as an AMPL data file. As a side effect, it
  invalidates all entities (as the passed file can contain any arbitrary
  command); the lists of entities will be re-populated lazily (at first
  access). After reading the file, the interpreter is put back to "model"
  mode.

  :param str filName: Full path to the file.
  :raises Error: In case the file does not exist.

.. method:: AMPL.readTable(tableName)

  Read the table corresponding to the specified name, equivalent to the AMPL statement:

  .. code-block:: ampl

    read table tableName;


  :param string tableName: Name of the table to be read.

.. method:: AMPL.writeTable(tableName)

  Write the table corresponding to the specified name, equivalent to the AMPL statement:

  .. code-block:: ampl

    write table tableName;

  :param string tableName: Name of the table to be written.

.. method:: AMPL.eval(amplstatements)

  Parses AMPL code and evaluates it as a possibly empty sequence of AMPL
  declarations and statements.

  As a side effect, it invalidates all entities (as the passed statements
  can contain any arbitrary command); the lists of entities will be
  re-populated lazily (at first access)

  The output of interpreting the statements is passed to the current
  output handler (see :meth:`~.AMPL.getOutputHandler` and
  :meth:`~.AMPL.setOutputHandler`).

  By default, errors and warnings are printed to stdout.
  This behavior can be changed reassigning an
  error handler using setErrorHandler.

  :param str amplstatements: A collection of AMPL statements and declarations
    to be passed to the interpreter.
  :raises Error: if the input is not a complete AMPL statement (e.g.
    if it does not end with semicolon) or if the underlying
    interpreter is not running

.. method:: AMPL.reset()

  Clears all entities in the underlying AMPL interpreter, clears all maps
  and invalidates all entities.

.. method:: AMPL.close()

  Stops the underlying engine, and release all any further attempt to execute
  optimisation commands without restarting it will throw an exception.

.. method:: AMPL.isRunning()

  Returns ``TRUE``  if the underlying engine is running.

.. method:: AMPL.solve()

  Solve the current model.

  :raises Error: If the underlying interpreter is not running.

.. method:: AMPL.getData(statements)

  Get the data corresponding to the display statements. The statements can
  be AMPL expressions, or entities. It captures the equivalent of the
  command:

  .. code-block:: ampl

    display ds1, ..., dsn;


  where ``ds1, ..., dsn`` are the ``statements`` with which the function is called.

  As only one DataFrame is returned, the operation will fail if the results
  of the display statements cannot be indexed over the same set. As a
  result, any attempt to get data from more than one set, or to get data
  for multiple parameters with a different number of indexing sets will
  fail.

  :param list statements: The display statements to be fetched.
  :return: DataFrame capturing the output of the display command in tabular form.
  :rtype: DataFrame
  :raises Error: if the AMPL visualization command does not succeed for one of the reasons listed above.

.. method:: AMPL.getValue(scalarExpression)

  Get a scalar value from the underlying AMPL interpreter, as a double or a string.

  :param string scalarExpression: An AMPL expression which evaluates to a scalar value.
  :return: The value of the expression.

.. method:: AMPL.getOutput(amplstatements)

  Equivalent to :meth:`~.AMPL.eval` but returns the output as a string.

  :param str amplstatements: A collection of AMPL statements and declarations
    to be passed to the interpreter.
  :raises Error: if the input is not a complete AMPL statement (e.g.
    if it does not end with semicolon) or if the underlying
    interpreter is not running
  :return: A string with the output.

.. method:: AMPL.setData(df, numberOfIndexColumns, setName)

  Assign the data in the dataframe to the AMPL entities with the names
  corresponding to the column names. If setName is ``NULL``, only the
  parameters value will be assigned.

  :param DataFrame df: The dataframe containing the data to be assigned.
  :param integer numberOfIndexColumns: Number of index columns.
  :param string setName:  The name of the set to which the indices values of the DataFrame are to be assigned.
  :raises Error: If the data assignment procedure was not successful.

.. method:: AMPL.getVariable(name)

  Get the variable with the corresponding name.

  :param str name: Name of the variable to be found.
  :return: Variable object.
  :rtype: :class:`Variable`
  :raises Error: If the specified variable does not exist.

.. method:: AMPL.getConstraint(name)

  Get the constraint with the corresponding name.

  :param str name: Name of the constraint to be found.
  :return: Constraint object.
  :rtype: :class:`Variable`
  :raises Error: If the specified constraint does not exist.

.. method:: AMPL.getObjective(name)

  Get the objective with the corresponding name.

  :param str name: Name of the objective to be found.
  :return: Objective object.
  :rtype: :class:`Objective`
  :raises Error: If the specified objective does not exist.

.. method:: AMPL.getSet(name)

  Get the set with the corresponding name.

  :param str name: Name of the set to be found.
  :return: Set object.
  :rtype: :class:`Set`
  :raises Error: If the specified set does not exist.

.. method:: AMPL.getParameter(name)

  Get the parameter with the corresponding name.

  :param str name: Name of the parameter to be found.
  :return: Parameter object.
  :rtype: :class:`Parameter`
  :raises Error: If the specified parameter does not exist.

.. method:: AMPL.getVariables()

  Get all the variables declared.

  :return: List of :class:`Variable` objects.

.. method:: AMPL.getConstraints()

  Get all the constraints declared.

  :return: List of :class:`Constraint` objects.

.. method:: AMPL.getObjectives()

  Get all the objectives declared.

  :return: List of :class:`Objective` objects.

.. method:: AMPL.getSets()

  Get all the sets declared.

  :return: List of :class:`Set` objects.

.. method:: AMPL.getParameters()

  Get all the parameters declared.

  :return: List of :class:`Parameter` objects.

.. method:: AMPL.exportModel(modfile)

  Create a .mod file with the model that has been loaded.

  :param str modfile: Path to the file (Relative to the current working directory or absolute).

.. method:: AMPL.exportData(datfile)

  Create a .dat file with the data that has been loaded.

  :param str datfile: Path to the file (Relative to the current working directory or absolute).

.. method:: AMPL.setOutputHandler(outputhandler)

  Sets a new output handler.

  :param function outputhandler: The function handling the AMPL output derived from interpreting user commands.

.. method:: AMPL.getOutputHandler()

  Get the current output handler.

  :return: The current output handler.
  :rtype: function
  :raises Error: If no output handler was set.

.. method:: AMPL.setErrorHandler(errorhandler)

  Sets a new error handler. The error handler receives a list with:
  - ``$type``: type (warning or error);
  - ``$filename``: name of the file where the error was detected;
  - ``$line``: the row where the error is located;
  - ``$offset``: the offset where the error is located;
  - ``$message``: the error message.

  :param function errorhandler: The function handling AMPL errors and warnings.

.. method:: AMPL.getErrorHandler()

  Get the current error handler.

  :return: The current error handler.
  :rtype: function
  :raises Error: If no error handler was set.

