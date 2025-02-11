library(dplyr)
library(ggplot2)

# Define file path
file_path <- "c:/Users/me/test-practice-others/DSC 10/Registered_motors.csv"

# Read the CSV file
data <- read.csv(file_path, stringsAsFactors = FALSE)

# Load India's population data (assuming user will provide or fetch separately)
# Example: Population data frame with 'Year' and 'Population' columns
population_data <- data.frame(
  Year = c(1951:2013),
  Population = c(361088000, 439235000, 498975000, 555189000, 609684000, 663033000, 
                 716507000, 780219000, 841387000, 904135000, 967765000, 
                 1028737436, 1082851733, 1140218560, 1199122898, 1256743972)
)

# Ensure both datasets have a common 'Year' column
data <- data %>% rename(Year = X)  # Assuming 'X' column represents Year
merged_data <- merge(data, population_data, by = "Year")

# Calculate correlation between total vehicles and population
correlation_value <- cor(merged_data$Total_Vehicles, merged_data$Population, use = "complete.obs")

# Plot the relationship
plot <- ggplot(merged_data, aes(x = Population, y = Total_Vehicles)) +
  geom_point() +
  geom_smooth(method = "lm", se = FALSE, color = "blue") +
  labs(title = "Correlation between Total Vehicles and Population in India",
       x = "Population",
       y = "Total Vehicles Registered") +
  theme_minimal()

# Display results
print(correlation_value)
print(plot)