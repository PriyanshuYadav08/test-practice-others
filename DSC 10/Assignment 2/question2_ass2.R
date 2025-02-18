x <- seq(0,20,by = 1) 
 y<-dpois(x,1) 
png(file = "dpois.png") 
plot(x,y) 
dev.off()

ppois(16, lambda=12)

ppois(16, lambda=12, lower=FALSE)

qpois(0.75, lambda=12)

rpois(16, lambda=12)