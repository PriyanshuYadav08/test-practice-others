factorial_calculator <- function(n) {
  if (n < 0) {
    return("Factorial is not defined for negative numbers")
  } else if (n == 0) {
    return(1)  # Factorial of 0 is 1
  } else {
    fact <- 1
    for (i in 1:n) {
      fact <- fact * i
    }
    return(fact)
  }
}

user_input <- as.integer(readline(prompt = "Enter a number to calculate its factorial = "))

result <- factorial_calculator(user_input)
cat("The factorial of", user_input, "is", result, "\n")