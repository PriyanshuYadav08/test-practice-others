find_mode <- function(data) {
  freq_table <- table(data)
  max_freq <- max(freq_table)
  modes <- as.numeric(names(freq_table[freq_table == max_freq]))
  if (length(modes) == length(unique(data))) {
    return("No mode (all values appear with equal frequency)")
  } else {
    return(modes)
  }
}

set.seed(123)
data1 <- c(1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 5)
data2 <- c(1, 2, 3, 4, 5, 6, 7)
data3 <- c(2, 3, 3, 3, 4, 5, 6, 6, 6)

print(find_mode(data1))
print(find_mode(data2))
print(find_mode(data3))