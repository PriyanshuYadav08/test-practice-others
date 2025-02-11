library(dplyr)
library(ggplot2)

file_path <- "c:/Users/me/test-practice-others/DSC 10/Registered_motors.csv"

data <- read.csv(file_path, stringsAsFactors = FALSE)

population_known <- data.frame(
  Year = c(1951,1952,1953,1954,1955,1956,1957,1958,1959,1960,1961,1962,1963,1964,1965,1966,1967,1968,1969,1970,1971,1972,1973,1974,1975,1976,1977,1978,1979,1980,1981,1982,1983,1984,1985,1986,1987,1988,1989,1990,1991,1992,1993,1994,1995,1996,1997,1998,1999,2000,2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011,2012,2013),
  Population = c(361088000,372997188,381227705,389731406,398577992,407656597,416935399,426295763,435900352,445954579,456351876,467024193,477933619,489059309,500114346,510992617,521987069,533431909,545314670,557501301,569999178,582837973,596107483,609721951,623524219,637451448,651685628,666267760,681248383,696828385,712869298,729169466,745826546,762895156,780242084,797878993,815716125,833729681,852012673,870452165,888941756,907574049,926351297,945261958,964279129,983281218,1002335230,1021434576,1040500054,1059633675,1078970907,1098313039,1117415123,1136264583,1154638713,1172373788,1189691809,1206734806,1223640160,1240613620,1257621191,1274487215,1291132063)
)

# Generate full population data using linear interpolation
full_years <- data.frame(Year = 1951:2013)
population_data <- merge(full_years, population_known, by = "Year", all.x = TRUE)
population_data$Population <- approx(population_data$Year, population_data$Population, xout = population_data$Year, rule = 2)$y

# Ensure both datasets have a common 'Year' column
data <- data %>% rename(Year = Year)
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