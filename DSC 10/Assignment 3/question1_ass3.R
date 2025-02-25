calls <- c(0, 1, 1, 1, 0, 1, 2, 1, 4, 1, 2, 3, 
           0, 3, 0, 1, 0, 1, 1, 2, 3, 0, 2, 2)
sample_mean <- mean(calls)
sample_variance <- var(calls)
cat("Sample Mean:", sample_mean, "\n")
cat("Sample Variance:", sample_variance, "\n")
library(ggplot2)
calls_table <- table(calls) / length(calls)
lambda <- 1.3
x_vals <- 0:max(calls)
poisson_probs <- dpois(x_vals, lambda)
df_data <- data.frame(x = as.numeric(names(calls_table)), freq = as.numeric(calls_table))
df_poisson <- data.frame(x = x_vals, prob = poisson_probs)
p <- ggplot() +
  geom_bar(data = df_data, aes(x = x, y = freq), stat = "identity", fill = "blue", alpha = 0.5) +
  geom_point(data = df_poisson, aes(x = x, y = prob), color = "red", size = 3) +
  geom_line(data = df_poisson, aes(x = x, y = prob), color = "red") +
  labs(title = "Relative Frequency Histogram vs Poisson Distribution",
       x = "Number of Calls",
       y = "Probability/Frequency") +
  theme_minimal()
print(p)
cat("The Poisson model is reasonable if the sample mean is approximately equal to the variance.\n")
cat("Since Sample Mean:", sample_mean, "and Sample Variance:", sample_variance, 
    "are close, a Poisson model with λ =", lambda, "seems appropriate.")