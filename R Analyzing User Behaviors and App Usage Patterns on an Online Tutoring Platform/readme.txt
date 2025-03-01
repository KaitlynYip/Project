The dataset is provided from HKCC.

The dataset consists of two separate files: "Tutoring.csv" and "France.csv".

Tutoring.csv:
This file contains statistics of a sample of users on an online tutoring platform.
Variables:
ID: Numeric ID of the user.
country: Character representing the user's country.
language: Character denoting the user's preferred language.
socialNbFollowers: Numeric, the number of users following this user.
socialClassesLiked: Numeric, number of classes this user liked.
classesListed: Numeric, number of classes without students listed under this user.
classesOffered: Numeric, number of classes this user has offered.
classesPassRate: Numeric, percentage of classes meeting the class description.
classesWished: Numeric, number of classes in the wishlist of this user.
classesEnrolled: Numeric, number of classes this user enrolled in.
gender: Character representing the user's gender ("M" for male, "F" for female).

France.csv:
This file contains information about the usage of the online tutoring platform's mobile app in France.

Variables:
ID: Numeric ID of the user.
hasAnyApp: Logical, indicating whether this user has ever used any of the platform's apps.
hasAndroidApp: Logical, indicating whether this user has ever used the official Android app.
hasIosApp: Logical, indicating whether this user has ever used the official iOS app.


These datasets provide valuable insights into user behaviors on the online tutoring platform and the usage patterns of the mobile app among users in France. Analysis of these datasets can help in understanding user preferences, engagement levels, and platform usage trends.



The process of the Rprogram.

Step1, 	All necessary packages will be loaded into the RStudio.

Step2. 	Read the data file Tutoring.csv and France.csv into two R data frames with names data_all and data_france respectively. 

Step3. 	The function of summarize() function to find out the average, standard deviation, minimum and maximum of the variable socialNbFollowers of all users and store the results in a R data frame basic_stat. 

Step 4. 	It found out the average and variance of the variable classesListed and the numbers of users in "France" and "Italie". The statistics will be stored in a R data frame country_stat. In this step, it uses the filter() function to separate the users living in France or Italie and further made them into a new dataset called " country_stat". After using the function of sunmmarize()  to show the mean, var, and no. of rows, it is based on the country's column to arrange into a descending order.

Step5.	It counts the total number of users who have the Android app and separates them into false and true classes. It calculated the average for those users who have offered. In this step, the code snippet filters app users in France, joins this information with the overall user statistics, calculates the average number of classes offered by users based on whether they have used the official Android app, and presents this information in a summary format with the group of Android app users listed first.

