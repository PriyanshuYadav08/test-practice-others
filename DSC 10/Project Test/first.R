set.seed(123)

setwd("c:/Users/me/test-practice-others/DSC 10/Project Test")

population <- 1000
prob_infection <- 0.02 
lambda <- 5

binom_cases <- rbinom(30, population, prob_infection)
pois_cases <- rpois(30, lambda)

png("Binomial_vs_Poisson.png")

# Set ylim to cover the range of both binom_cases and pois_cases
plot(binom_cases, 
     type="b", 
     col="blue", 
     ylab="Infections",
     xlab="Day", 
     main="Binomial vs Poisson",
     ylim=c(0, max(c(binom_cases, pois_cases))))  # Adjust y-axis limits

lines(pois_cases, 
      type="b", 
      col="red")

legend("topright", 
       legend=c("Binomial", "Poisson"), 
       col=c("blue", "red"), 
       lty=1)

dev.off()