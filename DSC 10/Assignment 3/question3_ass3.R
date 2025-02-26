library(ggplot2)

set.seed(42)

values <- c(1, 2, 3, 4)  # Possible chip values
probabilities <- c(0.2, 0.3, 0.3, 0.2)  # Corresponding probabilities

n <- 100
simulated_samples <- sample(values, size = n, replace = TRUE, prob = probabilities)

relative_freq <- table(simulated_samples) / n

df_hist <- data.frame(x = as.numeric(names(relative_freq)), h_x = as.numeric(relative_freq))
df_pmf <- data.frame(x = values, f_x = probabilities)

ggplot() +
  # Histogram as bars
  geom_bar(data = df_hist, aes(x = x, y = h_x, fill = "Simulated Histogram"), 
           stat = "identity", alpha = 0.6, color = "black") +
  # Theoretical PMF as points and a line
  geom_point(data = df_pmf, aes(x = x, y = f_x, color = "Theoretical PMF"), 
             size = 3) +
  geom_line(data = df_pmf, aes(x = x, y = f_x, color = "Theoretical PMF"), 
            linewidth = 1) +
  # Customizing colors
  scale_fill_manual(name = "", values = c("Simulated Histogram" = "skyblue")) +
  scale_color_manual(name = "", values = c("Theoretical PMF" = "red")) +
  # Titles and labels
  labs(title = "Comparison of Theoretical PMF and Simulated Histogram",
       x = "Chip Number",
       y = "Probability") +
  theme_minimal() +
  theme(legend.position = "top")  # Move legend to the top