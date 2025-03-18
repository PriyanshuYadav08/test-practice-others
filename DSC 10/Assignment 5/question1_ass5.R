# Given parameters
mu <- 11
sigma <- 3.5

# (a) Probability that a person will score between 10 and 15
prob_a <- pnorm(15, mean = mu, sd = sigma) - pnorm(10, mean = mu, sd = sigma)
cat("Probability of scoring between 10 and 15:", prob_a, "\n")

# (b) Probability that a person will score less than 5
prob_b <- pnorm(5, mean = mu, sd = sigma)
cat("Probability of scoring less than 5:", prob_b, "\n")