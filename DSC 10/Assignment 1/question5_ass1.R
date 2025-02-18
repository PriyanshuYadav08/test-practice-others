oct29 <- c(0, 1, 1, 1, 0, 1, 2, 1, 4, 1, 2, 3)
oct30 <- c(0, 3, 0, 1, 0, 1, 1, 2, 3, 0, 2, 2)
calls <- c(oct29, oct30)

sample_mean <- mean(calls)
sample_variance <- var(calls)

hist(calls, breaks = max(calls) - min(calls) + 1, 
     freq = FALSE, col = "lightblue", 
     main = "Relative Frequency Histogram", 
     xlab = "Number of Calls", 
     ylab = "Density")

x_vals <- min(calls):max(calls)
lines(x_vals, dpois(x_vals, lambda = mean(calls)), col = "red")

cat("Sample Mean:", mean(calls), "\n")
cat("Sample Variance:", var(calls), "\n")