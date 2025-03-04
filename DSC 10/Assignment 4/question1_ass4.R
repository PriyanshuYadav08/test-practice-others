weights <- c(19.8, 20.3, 20.2, 19.6, 20.0, 19.4, 15.4, 19.9, 20.5, 20.5, 19.8,
             15.5, 21.8, 20.0, 15.4, 20.6, 15.7, 20.4, 21.3, 16.7, 15.6, 14.2,
             15.9, 16.8, 15.2, 15.0, 16.4, 15.4, 16.0, 16.1, 17.0, 16.0,
             15.1, 14.1, 15.8, 15.7, 16.6, 15.2, 15.5, 14.9, 15.3)

mean_weight <- mean(weights)
sd_weight <- sd(weights)

cat("Sample Mean:", mean_weight, "\n")
cat("Sample Standard Deviation:", sd_weight, "\n")

breaks <- seq(13.95, max(weights) + 1, by = 1)  # Interval size of 1

hist(weights, breaks = breaks, probability = TRUE, 
     col = "lightblue", border = "black", main = "Relative Frequency Histogram",
     xlab = "Weight (grams)", ylab = "Relative Frequency")

abline(v = mean_weight, col = "red", lwd = 2, lty = 2)
abline(v = mean_weight + sd_weight, col = "blue", lwd = 2, lty = 2)
abline(v = mean_weight - sd_weight, col = "blue", lwd = 2, lty = 2)
abline(v = mean_weight + 2 * sd_weight, col = "green", lwd = 2, lty = 2)
abline(v = mean_weight - 2 * sd_weight, col = "green", lwd = 2, lty = 2)

legend("topright", legend = c("Mean", "Mean ± 1 SD", "Mean ± 2 SD"),
       col = c("red", "blue", "green"), lwd = 2, lty = 2)