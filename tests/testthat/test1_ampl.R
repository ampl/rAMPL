context("Test 1: test AMPL")

# Example 1: Create an AMPL object
test_that("creating an AMPL object", {
  ampl <- new(AMPL)
  expect_equal(ampl$cd(), ampl$cd())
})


# Example 2: Displaying the value of variable x
test_that("displaying the value of variable x", {
  ampl <- new(AMPL)
  ampl$eval("var x;")
  ampl$eval("display x;")
  expect_equal(ampl$cd(), ampl$cd())
})
