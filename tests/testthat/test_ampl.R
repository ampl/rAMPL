context('Test AMPL')

test_that('test constructor', {
  ampl <- new(AMPL)
  expect_equal(ampl$cd(), ampl$cd())
  env <- new(Environment)
  ampl <- new(AMPL, env)
  expect_equal(ampl$cd(), ampl$cd())
})

test_that('displaying the value of variable x', {
  ampl <- new(AMPL)
  ampl$eval('var x;')
  ampl$eval('display x;')
  expect_equal(ampl$cd(), ampl$cd())
})
