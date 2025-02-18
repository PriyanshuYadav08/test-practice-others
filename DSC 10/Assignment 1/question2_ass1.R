library(dplyr)

# Define file path
file_path <- "c:/Users/me/test-practice-others/DSC 10/NV55_2009.csv"

# Read the CSV file
data <- read.csv(file_path, stringsAsFactors = FALSE)

# Remove rows with missing data
cleaned_data <- na.omit(data)

# Save cleaned data to a new file
write.csv(cleaned_data, "c:/Users/me/test-practice-others/DSC 10/cleaned_data.csv", row.names = FALSE)

# Check column names and correct if necessary
colnames(cleaned_data) <- trimws(colnames(cleaned_data))

# Ensure column exists before filtering
if("Students_Abroad_2019" %in% colnames(cleaned_data)) {
  subset_data <- cleaned_data %>%
    filter(Students_Abroad_2019 > 50)
  
  # Analyze the subset data
  summary(subset_data)
  
  # Extract unique countries from subset data
  countries <- unique(subset_data$Country)
  
  # Function to retrieve top-ranked universities
  get_top_universities <- function(country) {
    return(paste("Top university in", country))
  }
  
  # Get top universities for each country in the subset
  top_universities <- sapply(countries, get_top_universities)
  
  # Print results
  print(top_universities)
} else {
  print("Column 'Students_Abroad_2019' not found in the dataset.")
}