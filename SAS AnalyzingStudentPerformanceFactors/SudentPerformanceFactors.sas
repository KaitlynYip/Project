
/* using csv file to input */
data std_Performance;
    infile 'StudentPerformanceFactors.csv' dsd firstobs=2;
    input Hours_Studied  Attendance  Parental_Involvement $ 
          Access_to_Resources $ Extracurricular_Activities $ Sleep_Hours  
          Previous_Scores  Motivation_Level $ Internet_Access $ Tutoring_Sessions  
          Family_Income $ Teacher_Quality $ School_Type $ Peer_Influence $ Physical_Activity  
          Learning_Disabilities $ Parental_Education_Level $ 
          Distance_from_Home $ Gender $ Exam_Score date:DDMMYY10.;
    
    label Hours_Studied = 'Hours of Studied' Exam_Score = 'Exam Performance';
run;

* print the dataset;
proc print data=std_Performance;
    label Hours_Studied = 'Hours of Study' Exam_Score = 'Exam Performance';
run;


/* Step 1: Sort the data */
proc sort data=std_Performance out=sorted_data;
    by Exam_Score;
run;

/* Step 2: Extract the top 4 largest values */
data BottomSmallest;
    set sorted_data(obs=4);
run;

/* Step 3: Extract the bottom 4 smallest values */
data TopLargest;
    set sorted_data nobs=n;
    if _N_ > (n - 4) then output;
run;

/* Step 4: Combine results */
data CombinedResults;
    length Type $10;
    set TopLargest;
    Type = "Largest";
    output;

    set BottomSmallest;
    Type = "Smallest";
    output;
run;

proc sort data=combinedresults;
	by Type;
run;

/* Step 5: Print the results */
proc print data=CombinedResults;
    title "Top 4 Largest and Smallest Exam Scores";
    var Type Exam_Score Hours_Studied Internet_Access;
run;





/* Demonstrate a proper usage of Conditional Statement or Loops */
/* Step1, create dataset */
/* Create a Pass/Fail status based on Exam Score */
data std_Performance;
    set std_Performance;
    if Exam_Score < 60 then Status = 'Fail';
    else Status = 'Pass';
run;

/* Sort the data in descending order of Exam Score */
proc sort data=std_Performance;
    by descending Exam_Score;
run;

/* Print the top 10 failed exams */
proc print data=std_Performance(where=(Status='Fail') obs=10) label;
    title "Top 10 Failed Exams ";
    var Exam_Score Hours_Studied Status;
run;

/* Print the top 10 passed exams */
proc print data=std_Performance(where=(Status='Pass') obs=10) label;
    title "Top 10 Passed Exams ";
    var Exam_Score Hours_Studied Status;
run;



/*DATA VISUALIZATION */

* Bar charts for student gender;
PROC SGPLOT DATA =  std_Performance;
	VBAR Gender ;
	TITLE 'Numbers of male and female';
RUN;

* Create histogram that student performence in exam;
PROC SGPLOT DATA =  std_Performance;  
	HISTOGRAM Exam_Score; 
	DENSITY Exam_Score; 
	TITLE 'Student Performence In Exam';
RUN;
* Create box plot;
PROC SGPLOT DATA =  std_Performance;
	VBOX Attendance / CATEGORY = Teacher_Quality;  
	TITLE 'Teacher quality and the attendence';
RUN;
* Plot PreviousScores by  Exam Score;
PROC SGPLOT DATA = std_Performance;  
	SCATTER X = Previous_Scores Y = Exam_Score;  
	XAXIS LABEL  =  'Previous_Scores' VALUES  =  (40 TO 100 BY  10);
	YAXIS LABEL  =  'Exam_Score';
	TITLE  'Exam_Score and Previous_Scores';
RUN;





/* DATA ANALYTICS */


proc univariate data=std_Performance;
   var Hours_Studied Exam_Score;
   qqplot Hours_Studied Exam_Score;
   title 'summary';
run;

*Data analytics of Exam_Score and Hours_Studied;
proc corr data=std_Performance ;
	var Exam_score Hours_Studied;
	title'Correlations for Exam_ Score and Hours_Studied';
run;

*data analysis of Exam_Score and Hours_studied;
proc reg data=std_Performance alpha=0.05 plots(maxpoints=none);;
	model Exam_Score = Hours_Studied;
	title'Results of Regression Analysis';
run;

