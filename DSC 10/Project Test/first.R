# 📦 Load necessary libraries
library(ggplot2)
library(MASS)
library(dplyr)

# 🔢 Set seed for reproducibility
set.seed(123)

setwd("c:/Users/me/test-practice-others/DSC 10/Project Test")

# 👥 Parameters for simulation
population <- 1000
prob_infection <- 0.02  # 2% infection rate
lambda <- 5             # average daily infections

# 📊 Generate simulated data
binom_cases <- rbinom(30, population, prob_infection)  # Binomial
pois_cases <- rpois(30, lambda)                        # Poisson

# 🎯 Fit Negative Binomial to Poisson simulated data
nb_fit <- fitdistr(pois_cases, densfun = "Negative Binomial")
nb_r <- nb_fit$estimate["size"]
nb_mu <- nb_fit$estimate["mu"]
nb_cases <- rnbinom(30, size = nb_r, mu = nb_mu)  # simulate based on fit

# 📈 Create a combined data frame for plotting
data <- data.frame(
  Day = 1:30,
  Binomial = binom_cases,
  Poisson = pois_cases,
  NegBinomial = nb_cases
)

# 🖼️ Reshape for ggplot
library(tidyr)
long_data <- pivot_longer(data, cols = -Day, names_to = "Model", values_to = "Cases")

# 📊 Plot all models
ggplot(long_data, aes(x = Day, y = Cases, color = Model)) +
  geom_line(size = 1.2) +
  geom_point(size = 2) +
  theme_minimal() +
  labs(
    title = "Comparison of Disease Case Simulations",
    subtitle = "Binomial vs Poisson vs Negative Binomial",
    x = "Day",
    y = "Number of Infections"
  ) +
  scale_color_manual(values = c("Binomial" = "blue", "Poisson" = "red", "NegBinomial" = "darkgreen"))