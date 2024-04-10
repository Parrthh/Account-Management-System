library(ggplot2)

df <- read.csv("stock_transaction_history.txt",sep = ' ')


colnames(df) <- c("EVENT","BALANCE","STOCK_NAME","STOCK_PRICE","TOTAL","TIMESTAMP")


ggplot(df, aes(x = "", y = "TOTAL VALUATION", fill = EVENT)) + geom_bar(stat="identity", width=1) +
  coord_polar("y", start=0)
