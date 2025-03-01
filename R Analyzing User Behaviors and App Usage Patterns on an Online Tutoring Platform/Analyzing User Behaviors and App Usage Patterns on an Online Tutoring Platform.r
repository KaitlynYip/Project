# (a) Load all necessary packages
library(dplyr)



# (b) Read the data files
data_all = read.csv("Tutoring.csv")
data_france = read.csv("France.csv")




# (c) Basic summary statistics
basic_stat = summarize(data_all,
                       AvgFollowers=mean(socialNbFollowers),
                       SdFollowers=sd(socialNbFollowers),
                       MinFollowers=min(socialNbFollowers),
                       MaxFollowers=max(socialNbFollowers))




# (d) Summary statistics of France and Italie users
data_subset = filter(data_all,country=="France"|country=="Italie")
country_stat = summarize(group_by(data_subset,country),
                         AvgClassesListed=mean(classesListed),
                         VarClassesListed=var(classesListed),
                         NumberOfUser=n()
)
country_stat = arrange(country_stat,desc(country))




# (e) Summary of app users in France
appusers = filter(data_france,hasAnyApp)
data_appusers = right_join(data_all,appusers,by="ID")
france_stat = summarize(group_by(data_appusers,hasAndroidApp),
                        AvgclassesOffered=mean(classesOffered),
                        NumberOfUsers=n())
france_stat = arrange(france_stat,desc(hasAndroidApp))