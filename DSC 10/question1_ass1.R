# Step 1: Data Preparation
weights <- c(
  19.8, 20.3, 20.2, 19.6, 20.0, 19.4, 15.4, 19.9, 20.5, 20.5, 19.8, 15.5, 21.8, 20.0, 15.4, 
  20.6, 15.7, 20.4, 21.3, 16.7, 15.6, 14.2, 15.9, 16.8, 15.2, 15.0, 16.0, 16.4, 15.4, 16.0, 
  16.1, 17.0, 16.0, 15.1, 14.1, 15.8, 15.7, 16.6, 15.2, 15.5, 14.9, 15.3
)

# Step 2: Group Data into Classes and Create a Relative Frequency Histogram
breaks <- seq(13.95, 22.95, by = 1)  # Class boundaries
class_intervals <- cut(weights, breaks, right = FALSE)

# Calculate frequency and relative frequency
freq_table <- table(class_intervals)
rel_freq <- prop.table(freq_table)

# Plot the relative frequency histogram
barplot(
  rel_freq, 
  main = "Relative Frequency Histogram of Weights",
  xlab = "Class Intervals (grams)", 
  ylab = "Relative Frequency",
  col = "skyblue", 
  border = "black"
)

# Step 3: Calculate the Sample Mean and Standard Deviation
sample_mean <- mean(weights)
sample_sd <- sd(weights)

# Print the results
cat("Sample Mean:", sample_mean, "\n")
cat("Sample Standard Deviation:", sample_sd, "\n")

# Step 4: Overlay Mean and Standard Deviation on the Histogram
barplot(
  rel_freq, 
  main = "Relative Frequency Histogram with Mean and SD",
  xlab = "Class Intervals (grams)", 
  ylab = "Relative Frequency",
  col = "skyblue", 
  border = "black"
)

# Add mean and standard deviation lines
abline(v = sample_mean, col = "red", lwd = 2, lty = 2)  # Mean
abline(v = sample_mean + sample_sd, col = "green", lwd = 2, lty = 2)  # +1 SD
abline(v = sample_mean - sample_sd, col = "green", lwd = 2, lty = 2)  # -1 SD
legend("topright", legend = c("Mean", "+1 SD", "-1 SD"), col = c("red", "green", "green"), lty = 2, lwd = 2)