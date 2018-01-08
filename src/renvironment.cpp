#include "renvironment.h"
#include <Rcpp.h>
/*.. _secRrefEnv:
.. highlight:: r

Environment
===========

*/

/*.. class:: Environment

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
*/
REnvironment::REnvironment()  { }
REnvironment::REnvironment(std::string binaryDirectory): _impl(binaryDirectory) { }

/*.. method:: Environment.get(name)

  Searches the current object for an environment variable called name and returns its value if found.

  :param name: Name of the environment variable.
  :type name: `character`
  :return: The value of the variable or ``NA``.
  :rtype: `character`
*/
Rcpp::String REnvironment::get(std::string name) const {
  ampl::Environment::iterator it = _impl.find(name);
  if(it != _impl.end()) {
    return it->second;
  } else {
    return NA_STRING;
  }
}

/*.. method:: Environment.put(name, value)

  Add an environment variable to the environment, or change its value if already defined.

  :param name: Name of the environment variable.
  :type name: `character`
  :param value: Value to be assigned.
  :type value: `character`
*/
void REnvironment::put(std::string name, std::string value) {
  _impl.put(name, value);
}

/*.. method:: Environment.setBinDir(binaryDirectory)

  Set the location where AMPLAPI will search for the AMPL executable.

  :param binaryDirectory: The directory in which look for the AMPL Binary.
  :type binaryDirectory: `character`
*/
void REnvironment::setBinDir(std::string binaryDirectory) {
  return _impl.setBinDir(binaryDirectory);
}

/*.. method:: Environment.getBinDir()

  Get the location where AMPLAPI will search for the AMPL executable.

  :return: The location where AMPLAPI will search for the AMPL executable.
  :rtype: `character`
*/
std::string REnvironment::getBinDir() const {
  return _impl.getBinDir();
}

/*.. method:: Environment.toString()

  Returns all variables in the object as a string.

  :return: All variables in the map.
  :rtype: `character`
*/
std::string REnvironment::toString() const {
  return _impl.toString();
}

/*.. method:: Environment.list()

  Returns all variables in the object as a list.

  :return: All variables in the map.
  :rtype: `list`
*/
Rcpp::List REnvironment::list() const {
  Rcpp::List list;
  for(ampl::Environment::iterator it = _impl.begin(); it != _impl.end(); it++){
    list[it->first] = it->second;
  }
  return list;
}

// *** RCPP_MODULE ***
RCPP_MODULE(renvironment){
  Rcpp::class_<REnvironment>("Environment")
    .constructor()
    .constructor<std::string>()
    .method("get", &REnvironment::get)
    .method("put", &REnvironment::put)
    .method("setBinDir", &REnvironment::setBinDir)
    .method("getBinDir", &REnvironment::getBinDir)
    .method("toString", &REnvironment::toString)
    .method("list", &REnvironment::list)
    ;
}
