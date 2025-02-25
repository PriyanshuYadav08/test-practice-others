pmf <- function(k) {
  if (k >= 2) {
    return(1 / (2^(k-1)))
  } else {
    return(0)  # X starts from 2
  }
}
mean_X <- 2
var_X <- 2
sd_X <- sqrt(var_X)
P_X_leq_3 <- pmf(2) + pmf(3)
P_X_geq_6 <- 1 - sum(sapply(2:5, pmf))
P_X_eq_5 <- pmf(5)
cat("Mean:", mean_X, "\n")
cat("Variance:", var_X, "\n")
cat("Standard Deviation:", sd_X, "\n")
cat("P(X <= 3):", P_X_leq_3, "\n")
cat("P(X >= 6):", P_X_geq_6, "\n")
cat("P(X = 5):", P_X_eq_5, "\n")