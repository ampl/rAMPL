trackingmodel <- function(solver=NULL, modelDirectory=NULL) {
  library(rAMPL)
  # Create an AMPL instance
  ampl <- new(AMPL)

  ## If the AMPL installation directory is not in the system search path:
  # env <- new(Environment, "full path to the AMPL installation directory")
  # ampl <- new(AMPL, env)

  if (!is.null(solver)) {
    ampl$setOption("solver", solver)
  }

  # Read the model file.
  if (is.null(modelDirectory)) {
    modelDirectory <- "./models"
  }
  modelDirectory <- paste(modelDirectory, "tracking", sep="/")

  # Load the AMPL model from file
  ampl$read(paste(modelDirectory, "/tracking.mod", sep=""))
  # Read data
  ampl$readData(paste(modelDirectory, "/tracking.dat", sep=""))
  # Read table declarations
  ampl$read(paste(modelDirectory, "/trackingbit.run", sep=""))
  # Set tables directory (parameter used in the script above)
  ampl$getParameter("data_dir")$set(modelDirectory)
  # Read tables
  ampl$readTable("assets")
  ampl$readTable("indret")
  ampl$readTable("returns")

  hold = ampl$getVariable("hold")
  ifinuniverse = ampl$getParameter("ifinuniverse")

  # Relax the integrality
  ampl$setOption("relax_integrality", TRUE)
  # Solve the problem
  ampl$solve("", "")
  cat(sprintf("QP objective value ", ampl$getObjectives()[[1]]$value()))

  lowcutoff <- 0.04
  highcutoff <- 0.1

  # Get the variable representing the (relaxed) solution vector
  holdvalues = hold$getValues()
  toHold <- c()
  # For each asset, if it was held by more than the highcutoff,
  # forces it in the model, if less than lowcutoff, forces it out
  for (value in holdvalues[, 2]) {
    if (value < lowcutoff)
      toHold <- c(toHold, 0)
    else if (value > highcutoff)
      toHold <- c(toHold, 2)
    else
      toHold <- c(toHold, 1)
  }
  # uses those values for the parameter ifinuniverse, which controls
  # which stock is included or not in the solution
  ifinuniverse$setValues(toHold)

  # Get back to the integer problem
  ampl$setOption("relax_integrality", FALSE)
  # Solve the (integer) problem
<<<<<<< HEAD
  ampl$solve("", "gurobi")
=======
  ampl$solve("", "")
>>>>>>> master
  cat(sprintf("QMIP objective value %g\n", ampl$getObjectives()[[1]]$value()))
}
