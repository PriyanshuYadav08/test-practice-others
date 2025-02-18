x <- seq(0,20,by = 1) 
 y<-dpois(x,1) 
png(file = "dpois.png") 
plot(x,y) 
dev.off()
print(x <- ppois(16, lambda=12))

print(x <- ppois(16, lambda=12, lower=FALSE))

print(x <- qpois(0.75, lambda=12))

print(x <- rpois(16, lambda=12))