context("Test examples")

test_that("test dietmodel.R", {
  setwd("../../examples/")
  source("dietmodel.R")
  dietmodel()
})

test_that("test firstexample.R", {
  # setwd("../../examples/")
  source("firstexample.R")
  firstexample()
})

test_that("test efficientfrontier.R", {
  # setwd("../../examples/")
  source("efficientfrontier.R")
  efficientfrontier()
})

test_that("test multidimensional.R", {
  # setwd("../../examples/")
  source("multidimensional.R")
  multidimensional()
})

test_that("test optionsexample.R", {
  # setwd("../../examples/")
  source("optionsexample.R")
  optionsexample()
})

if (Sys.getenv("SKIP_BIG_TESTS") != "1") {
  test_that("test trackingmodel.R", {
      # setwd("../../examples/")
      source("trackingmodel.R")
      trackingmodel()
  })
}
