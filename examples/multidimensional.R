multidimensional <- function(solver=NULL, modelDirectory=NULL) {
  library(rAMPL)
  ampl <- new(AMPL)

  ampl$eval("set CITIES; set LINKS within (CITIES cross CITIES);")
  ampl$eval("param cost {LINKS} >= 0; param capacity {LINKS} >= 0;")
  ampl$eval("data; set CITIES := PITT NE SE BOS EWR BWI ATL MCO;")

  cost <- c(2.5, 3.5, 1.7, 0.7, 1.3, 1.3, 0.8, 0.2, 2.1)
  capacity <- c(250, 250, 100, 100, 100, 100, 100, 100, 100)
  LinksFrom <- c("PITT", "PITT", "NE", "NE", "NE", "SE", "SE", "SE", "SE")
  LinksTo <- c("NE", "SE", "BOS", "EWR", "BWI", "EWR", "BWI", "ATL", "MCO")

  df <- data.frame(LINKSFrom=LinksFrom, LINKSTo=LinksTo, cost=cost, capacity=capacity)
  print(df)

  ampl$setData(df, 2, "LINKS")
  ampl$eval('display cost;')
  ampl$eval('display capacity;')
}
