.. _secRrefEnv:
.. highlight:: r

Environment
===========


.. class:: Environment

  This class provides access to the environment variables and provides
  facilities to specify where to load the underlying AMPL interpreter.

.. function:: Environment()

  Default constructor.

.. function:: Environment(binaryDirectory)

  Constructor with ability to select the location of the AMPL binary.
  Note that if this constructor is used, the automatic lookup for an AMPL
  executable will not be executed.

  :param binaryDirectory: The directory in which look for the AMPL Binary.
  :type binaryDirectory: `character`

.. method:: Environment.get(name)

  Searches the current object for an environment variable called name and returns its value if found.

  :param name: Name of the environment variable.
  :type name: `character`
  :return: The value of the variable or ``NA``.
  :rtype: `character`

.. method:: Environment.put(name, value)

  Add an environment variable to the environment, or change its value if already defined.

  :param name: Name of the environment variable.
  :type name: `character`
  :param value: Value to be assigned.
  :type value: `character`

.. method:: Environment.setBinDir(binaryDirectory)

  Set the location where AMPLAPI will search for the AMPL executable.

  :param binaryDirectory: The directory in which look for the AMPL Binary.
  :type binaryDirectory: `character`

.. method:: Environment.getBinDir()

  Get the location where AMPLAPI will search for the AMPL executable.

  :return: The location where AMPLAPI will search for the AMPL executable.
  :rtype: `character`

.. method:: Environment.setBinName(binaryName)

  Set the name of the AMPL executable.

  :param binaryName: The name of the AMPL binary.
  :type binaryName: `character`

.. method:: Environment.getBinName()

  Get the name of the AMPL executable.

  :return: The name of the AMPL executable.
  :rtype: `character`

.. method:: Environment.toString()

  Returns all variables in the object as a string.

  :return: All variables in the map.
  :rtype: `character`

.. method:: Environment.list()

  Returns all variables in the object as a list.

  :return: All variables in the map.
  :rtype: `list`

