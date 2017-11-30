example <- function(){
  ampl <- new(AMPL)
  cat(ampl$cd(), '\n')

  ampl$eval('var x;')
  ampl$eval('display x;')

  var <- ampl$getVariable('x')
  cat(var$value(), '\n')

  ampl$eval('s.t. c: x = 10;')
  cat(ampl$getConstraint('c')$isLogical(), '\n')

  ampl$eval('maximize obj: x;')
  cat(ampl$getObjective('obj')$value(), '\n')

  ampl$eval('set s := 1..10;')
  cat(ampl$getSet('s')$arity(), '\n')

  ampl$eval('param p := "hello";')
  cat(ampl$getParameter('p')$isSymbolic(), '\n')

  ampl$eval('var x1; var x2; var x3;')
  cat(ampl$getVariables()$x1$value(), '\n')
}
