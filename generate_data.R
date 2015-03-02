library(ggplot2)
library(rhdf5)

h5file <- "data/data.h5"

N <- 1000

Gamma <- matrix( rep(.5,4), nrow=2)
mu <- c(-1, 1)
sigma <- c(1,1)



N.s <- dim(Gamma)[1]

eig <- eigen(Gamma)
delta.unnorm <- eig$vectors[,min(which(eig$values==1))]
delta <- delta.unnorm/sum(delta.unnorm)

s <- integer(N)

for (i in 1:N) {
    p <- if (i==1) delta else Gamma[s[i-1],]
    s[i] <- sample.int(N.s, 1, prob=p)
}

y <- rnorm(N, mean=mu[s], sd=sigma[s])



data <- data.frame(time=1:N, state=s, observation=y)

ggplot(data, aes(time, observation)) + geom_path()


##write.csv(data, file="data.csv", row.names=FALSE)


H5close()
h5createFile(h5file)
h5createGroup(h5file, "basic")
h5write(data, h5file,"basic/data")
