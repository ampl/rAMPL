context("Test AMPL")

test_that("test AMPL", {
  ampl <- new(AMPL)
  expect_equal(ampl$cd(), ampl$cd())
  expect_true(grepl("^AMPL API", ampl$toString()))

  env <- new(Environment)
  ampl <- new(AMPL, env)
  expect_equal(ampl$cd(), ampl$cd())
  expect_true(grepl("^AMPL API", ampl$toString()))

  path <- ampl$cd(find.package("rAMPL"))
  expect_equal(ampl$cd(), path)

  ampl <- new(AMPL)
  ampl$setOption("x", 1)
  ampl$setOption("y", TRUE)
  ampl$setOption("z", "hello")
  expect_equal(ampl$getOption("x"), "1")
  expect_equal(ampl$getOption("y"), "1")
  expect_equal(ampl$getOption("z"), "hello")
  expect_equal(ampl$getIntOption("x"), 1)
  expect_equal(ampl$getIntOption("y"), 1)
  expect_error(ampl$getIntOption("z"))
  expect_equal(ampl$getDblOption("x"), 1)
  expect_equal(ampl$getDblOption("y"), 1)
  expect_error(ampl$getDblOption("z"))
  expect_equal(ampl$getBoolOption("x"), TRUE)
  expect_equal(ampl$getBoolOption("y"), TRUE)
  expect_error(ampl$getBoolOption("z"))
  ampl$setOption("y", FALSE)
  expect_equal(ampl$getBoolOption("y"), FALSE)

  ampl$read("model.mod")
  ampl$readData("data.dat")
  expect_equal(length(ampl$getSet("S")$members()), 5)
  ampl$reset()
  expect_error(ampl$getSet("S"))
  ampl$eval("set S := 1..3;")
  expect_equal(length(ampl$getSet("S")$members()), 3)

  expect_true(ampl$isRunning())
  ampl$close()
  expect_false(ampl$isRunning())

  ampl <- new(AMPL)
  expect_equal(ampl$getValue("3*5"), 15)
  expect_equal(ampl$getValue("'3*5'"), "3*5")

  ampl$eval("set I;")
  ampl$eval("param p{I} symbolic;")
  I = c(2, 3, 5)
  p = c("aa", "bb", "cc")
  df = data.frame(I, p)
  ampl$setData(df, 1, "I")
  expect_equal(length(ampl$getSet("I")$members()), 3)
  expect_equal(ampl$getParameter("p")[[3]], "bb")
  df2 = ampl$getData("p")
  expect_equal(nrow(df2), 3)
  expect_equal(ncol(df2), 2)

  ampl$readTable("x")
  ampl$writeTable("x")

  ampl$reset()
  ampl$eval("
  set S := 1..10;
  param l := 5;
  var x >= 0;
  maximize obj: x;
  s.t. c: x <= l;
  ")
  expect_equal(ampl$getVariable("x")$name(), "x")
  expect_equal(ampl$getConstraint("c")$name(), "c")
  expect_equal(ampl$getObjective("obj")$name(), "obj")
  expect_equal(ampl$getSet("S")$name(), "S")
  expect_equal(ampl$getParameter("l")$name(), "l")

  expect_equal(ampl$getVariables()$x$name(), "x")
  expect_equal(ampl$getConstraints()$c$name(), "c")
  expect_equal(ampl$getObjectives()$obj$name(), "obj")
  expect_equal(ampl$getSets()$S$name(), "S")
  expect_equal(ampl$getParameters()$l$name(), "l")

  ampl$solve()
  expect_equal(ampl$getObjective("obj")$value(), 5)

  out <- ""
  outh <- function(output) { out <<- paste(out, output, sep="") }
  expect_error(ampl$getOutputHandler())
  ampl$setOutputHandler(outh)
  ampl$eval("option times, gentimes; display 1;")
  expect_equal(out, "option times 0;\noption gentimes 0;\n1 = 1\n\n")

  ampl$getOutputHandler()("test")
  expect_equal(out, "option times 0;\noption gentimes 0;\n1 = 1\n\ntest")

  last_message <- ""
  expect_error(ampl$getErrorHandler())
  erroh <- function(error) { last_message <<- error$message }
  ampl$setErrorHandler(erroh)
  ampl$eval("xx;")
  expect_equal(last_message, "syntax error")
  ampl$getErrorHandler()(list(message="foo"))
  expect_equal(last_message, "foo")

  expect_equal(ampl$getOutput("display 5;"), "5 = 5\n\n")
  expect_error(ampl$getOutput("display 3"))
  expect_error(ampl$getOutput("for {i in 1..10} {"))
  expect_equal(ampl$getOutput("display 5; display 1;"), "5 = 5\n\n1 = 1\n\n")

  ampl$reset()
  ampl$read("model.mod")
  ampl$readData("data.dat")
  modfile <- tempfile(fileext = ".mod")
  datfile <- tempfile(fileext = ".dat")
  ampl$exportModel(modfile)
  ampl$exportData(datfile)
  ampl2 <- new(AMPL)
  ampl2$read(modfile)
  ampl2$readData(datfile)
  expect_equal(length(ampl2$getSet("S")$members()), 5)
})
