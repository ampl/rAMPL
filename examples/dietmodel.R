dietmodel <- function(solver=NULL, modelDirectory=NULL) {
  library(rAMPL)
  ampl <- new(AMPL)

  if (!is.null(solver)) {
    ampl$setOption("solver", solver)
  }

  # Read the model file.
  if (is.null(modelDirectory)) {
    modelDirectory <- "./models"
  }
  ampl$read(paste(modelDirectory, "/diet/diet.mod", sep=""))

  # Set the values for the set FOOD, and for the parameters cost, f_min, and f_max
  foods <- c("BEEF", "CHK", "FISH", "HAM", "MCH", "MTL", "SPG", "TUR")
  costs <- c(3.59, 2.59, 2.29, 2.89, 1.89, 1.99, 1.99, 2.49)
  fmin <- c(2, 2, 2, 2, 2, 2, 2, 2)
  fmax <- c(10, 10, 10, 10, 10, 10, 10, 10)
  ampl$setData(data.frame(FOODS=foods, cost=costs, f_min=fmin, f_max=fmax), 1, "FOOD")

  # Set the values for the set NUTR, and for the parameters n_min and n_max
  nutrients <- c("A", "C", "B1", "B2", "NA", "CAL")
  nmin <- c(700, 700, 700, 700, 0, 16000)
  nmax <- c(20000, 20000, 20000, 20000, 50000, 24000)
  ampl$setData(data.frame(NUTR=nutrients, n_min=nmin, n_max=nmax), 1, "NUTR")

  amounts = rbind(
    c( 60,    8,   8,  40,   15,  70,   25,   60),
    c( 20,    0,  10,  40,   35,  30,   50,   20),
    c( 10,   20,  15,  35,   15,  15,   25,   15),
    c( 15,   20,  10,  10,   15,  15,   15,   10),
    c(928, 2180, 945, 278, 1182, 896, 1329, 1397),
    c(295,  770, 440, 430,  315, 400,  379,  450)
  )
  dimnames(amounts) <- list(nutrients, foods)

  # Convert matrix into data.frame
  df <- data.frame(as.table(amounts))
  colnames(df) <- c("NUTR", "FOOD", "amt")
  # Set the values for the parameter "amt"
  ampl$setData(df, 2, "")

  # Solve the model
  ampl$solve()

  # Print out the result
  cat(sprintf("Objective: %f\n", ampl$getObjective("total_cost")$value()))

  # Get the values of the variable Buy in a data.frame
  df <- ampl$getVariable("Buy")$getValues()
  print(df)
}
