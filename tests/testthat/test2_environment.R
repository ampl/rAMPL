context("Test 2: test Environment")

# Example 1: Create an Environment object
test_that("creating an Environment object", {
  ampl <- new(AMPL)
  expect_equal(ampl$cd(), ampl$cd())
})


# Example 2: Create and use an Environment object
test_that("creating and using an Environment object", {
  env <- new(Environment)
  ampl <- new(AMPL, env)
  expect_equal(ampl$cd(), ampl$cd())
})
