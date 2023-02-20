### Question
You oversee a team of 3 engineers which work with Python and C.
Each of the engineers has two skills, rated from 1 to 10: 
•	John: C – 10, Python - 2
•	Gary: C – 3, Python - 4
•	Anne: C – 5, Python - 8

A rating of 10 implies that the engineer is highly skilled while a rating of 1 implies that the engineer is a beginner.

Each month (20 working days) you receive a set of tasks, which are assessed based on how much C or Python coding time is needed and a time estimation for how much would an intermediate engineer take (rated as 5 for c and 5 for Python) for the given tasks.
Using the following example: 
•	“Write an ADC driver” - {c: 100%, Python 0:%, estimated time: 10 days}
•	“Create tests for Clock driver” {c: 40%, Python 60%, estimated time: 5 days}
•	“Update test infrastructure for multiple devices” {c: 0%, Python 100%, estimated time: 10 days }
•	“Create new demo application” {c: 80%, Python: 20%, estimated time: 10 days}
•	“Fix bug found by customer { c: 10%, Python: 90%, estimated time: 2 days }
•	“Analyze feature request” {c: 50%, Python: 50%, estimated time: 7 days}
•	“Implement new partitioning schema” {c: 90%, Python 10%, estimated time: 10 days}

Write a C program, which decides how the aforementioned tasks shall be split between engineers so that:
1.	You decide whether the tasks can be executed in 20 days (equivalent to the sprint duration). Print how the tasks were assigned to each developer.
2.	If Anne decides to take a week off (5 working days), in the beginning of the sprint, print the new sprint allocation for each developer.

Notes: 
•	You’re allowed to use any IDE or compiler you want.
•	Your solution should compile correctly.
•	The code should be readable – think you would present it to your work colleagues.