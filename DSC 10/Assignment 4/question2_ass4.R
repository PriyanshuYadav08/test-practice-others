# Poisson Approximation
lambda <- 10
poisson_prob <- dpois(12, lambda) + dpois(13, lambda) + dpois(14, lambda)

# Exact Binomial Probability
n <- 100
p <- 0.1
binomial_prob <- dbinom(12, n, p) + dbinom(13, n, p) + dbinom(14, n, p)

# Normal Approximation with continuity correction
mu <- n * p
sigma <- sqrt(n * p * (1 - p))
normal_prob <- pnorm(14.5, mu, sigma) - pnorm(11.5, mu, sigma)

# Display results
cat("Poisson Approximation: ", poisson_prob, "\n")
cat("Exact Binomial Probability: ", binomial_prob, "\n")
cat("Normal Approximation: ", normal_prob, "\n")