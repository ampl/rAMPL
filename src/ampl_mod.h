#ifndef GUARD_RcppAMPL_h
#define GUARD_RcppAMPL_h

#include <string>
#include "ampl/ampl.h"
#include "environment_mod.h"
#include "variable_mod.h"
#include "constraint_mod.h"
#include "objective_mod.h"
#include "set_mod.h"
#include "parameter_mod.h"
#include <Rcpp.h>

class AMPLOutputHandler : public ampl::OutputHandler {
public:
  Rcpp::Function outputhandler;
  AMPLOutputHandler(Rcpp::Function _outputhandler): outputhandler(_outputhandler) { }
  void output(ampl::output::Kind kind, const char* output) {
    outputhandler(output);
  }
};

class RcppAMPL{
private:
  AMPLOutputHandler *OHandler = NULL;
public:
  ampl::AMPL _impl;
  RcppAMPL();
  RcppAMPL(SEXP);
  Rcpp::String cd();
  Rcpp::String cdStr(std::string);
  void setOption(std::string name, std::string value);
  Rcpp::String getOption(std::string);
  void read(std::string fileName);
  void readData(std::string fileName);
  void eval(std::string amplstatements);
  void solve();
  RcppVariable getVariable(std::string name) const;
  RcppConstraint getConstraint(std::string name) const;
  RcppObjective getObjective(std::string name) const;
  RcppSet getSet(std::string name) const;
  RcppParameter getParameter(std::string name) const;

  void setOutputHandler(Rcpp::Function outputhandler);

  Rcpp::List getVariables() const;
  Rcpp::List getConstraints() const;
  Rcpp::List getObjectives() const;
  Rcpp::List getSets() const;
  Rcpp::List getParameters() const;
};

RCPP_EXPOSED_ENUM_NODECL(ampl::output::Kind);

#endif
