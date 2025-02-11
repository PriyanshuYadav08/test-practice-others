library(dplyr)
file_path <- "c:/Users/me/test-practice-others/DSC 10/NV55_2009.csv"
data <- read.csv(file_path, stringsAsFactors = FALSE)
cleaned_data <- na.omit(data)
write.csv(cleaned_data, "c:/Users/me/test-practice-others/DSC 10/NV55_2009.csv", row.names = FALSE) # nolint: line_length_linter.
subset_data <- cleaned_data %>%
filter(`Students_Abroad_2019` > 50) # nolint: indentation_linter.
summary(subset_data)
countries <- unique(subset_data$Country)
get_top_universities <- function(country) {
  return(paste("Top university in", country))
}
top_universities <- sapply(countries, get_top_universities)
top_universities