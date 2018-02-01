optionsexample <- function(solver=NULL, modelDirectory=NULL) {
  library(rAMPL)
  ampl <- new(AMPL)

  # Get the value of the option presolve and print
  presolve <- ampl$getIntOption("presolve")
  cat(sprintf("AMPL presolve is %d\n", presolve))

  # Set the value to FALSE
  ampl$setOption("presolve", FALSE)

  # Get the value of the option presolve and print
  presolve <- ampl$getIntOption("presolve")
  cat(sprintf("AMPL presolve is now %d\n", presolve))

  # Check whether an option with a specified name exists
  if (!is.na(ampl$getOption("solver"))) {
    cat(sprintf("Option solver exists and has value: %s\n", ampl$getOption("solver")))
  }

  # Check again, this time failing
  if (is.na(ampl$getOption("s_o_l_v_e_r"))) {
    cat("Option s_o_l_v_e_r does not exists!\n")
  }
}
