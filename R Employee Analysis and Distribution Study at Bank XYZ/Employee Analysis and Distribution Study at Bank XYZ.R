# 1. Read the CSV file
data <- read.csv("data.csv")
print("Data loaded successfully.")

# 2. Calculate the 20% trimmed mean of monthly salary
trimmed_mean_salary <- mean(data$salary, trim = 0.2)
print(paste("20% Trimmed Mean of Monthly Salary:", trimmed_mean_salary))

# 3. Find the 75th percentile of years served at Bank XYZ
quantile_75_years <- quantile(data$year, c(0.75))
print(paste("75th Percentile of Years Served:", quantile_75_years))

# 4. Calculate the variance of monthly salary
variance_salary <- var(data$salary)
print(paste("Variance of Monthly Salary:", variance_salary))

# 5. Construct a stem and leaf plot for employee ages
stem(data$age)

# 6. Create a histogram for years of service
hist(data$year)

# 7. Identify the division with the largest proportion of managers
division_rank_table <- table(data$division, data$rank)
prop_table <- prop.table(division_rank_table, margin = 1) * 100
manager_proportions <- prop_table[, "M"]
largest_proportion <- names(manager_proportions)[manager_proportions == max(manager_proportions)]
print("Proportion of Managers by Division:")
print(prop_table)
print("Division with Largest Proportion of Managers:")
print(largest_proportion)

# 8. Calculate the annual salary adjustment based on performance
adjustment <- (data$salary * data$rating) / 100
coefficient_of_variation <- sd(adjustment) / mean(adjustment) * 100
print(paste("Coefficient of Variation for Salary Adjustment:", coefficient_of_variation))

# 9. Calculate and interpret the coefficient of variation for salary increase
edu_table <- table(data$sex, data$edu)
prop_table_edu <- prop.table(edu_table, margin = 1) * 100
proportion_master_male <- prop_table_edu["M", "master"]
print("Proportion of Male Employees with a Master's Degree:")
print(proportion_master_male)

# 10. Test the distribution of employees among five divisions
# Null Hypothesis: The number of employees is evenly distributed among divisions.
# Alternative Hypothesis: The number of employees is not evenly distributed among divisions.
observed_divisions <- table(data$division)
chi_square_test_result <- chisq.test(observed_divisions)
print(chi_square_test_result)

# Conclusion based on p-value
if (chi_square_test_result$p.value < 0.05) {
  cat("Since p-value < 0.05, we reject the null hypothesis. The data show evidence that the number of employees is not evenly distributed among divisions.")
} else {
  cat("Since p-value >= 0.05, we do not reject the null hypothesis.")
}