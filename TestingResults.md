Project 1 – Testing Results
Testing Environment

The program was compiled and tested on a Windows computer using g++ and VS Code. The project was also compiled and tested after the search, sorting, and reporting features were integrated into the main program. The project was also tested successfully on the UNT CELL machine.

Test Results
Test	Expected Result	Actual Result	Status
Compile the project	All source files compile without errors	The project compiled successfully using g++ with no errors.	Pass
Start the program	The main menu appears	The menu appeared correctly with all available options.	Pass
Display resources	All resources and their availability are displayed	Four resources were displayed with their availability.	Pass
Create a valid reservation	The reservation is added to the active reservations	Reservation R100 was created successfully during the earlier tests.	Pass
Enter an invalid date	The program rejects the date and displays an error	The date 12012005 was rejected because it did not use YYYY-MM-DD format.	Pass
Enter an ID containing spaces	The program rejects the invalid ID	The program displayed an error about IDs containing whitespace.	Pass
Display active reservations	All active reservations are shown	R100 appeared in the active reservation list during the earlier tests.	Pass
Cancel a reservation	The reservation is removed from active reservations	R100 was cancelled successfully during the earlier tests.	Pass
View cancellation history	The cancelled reservation appears in the history stack	R100 appeared in the cancellation history during the earlier tests.	Pass
Undo a cancellation	The most recently cancelled reservation is restored	R100 was restored to active reservations during the earlier tests.	Pass
Add a waiting-list request	A request for an already-booked resource and date is queued	R101 was added to the waiting list when R100 already held that slot during the earlier tests.	Pass
Promote a waiting-list request	The next student is promoted after the active reservation is cancelled	R101 was promoted after R100 was cancelled during the earlier tests.	Pass
Search for a resource	The resource is found by its ID	Searching for R001 displayed Study Room 101, its type, and availability. Searching for nonexistent IDs displayed "Resource not found."	Pass
Sort resources	Resources are displayed in alphabetical order by name	Resources appeared alphabetically: Computer Lab 201, Conference Room 301, Study Room 101, Study Room 102.	Pass
Generate reports	The required system reports display the correct information	All three reports were tested with no data and with an active reservation and a waiting-list request. Resource utilization, waiting-list statistics, and most-requested resource counts updated correctly.	Pass
Compile and run on the UNT CELL machine	The project compiles and runs successfully on CELL	The project compiled and ran successfully on the UNT CELL machine.	Pass
Summary

The basic reservation, cancellation, cancellation history, undo, and waiting-list features were tested successfully on Windows during the earlier tests. Invalid dates and IDs containing spaces were also rejected correctly.

The search and sorting features were tested successfully after integration. All three reporting features were tested with and without reservation and waiting-list data, and the displayed results updated correctly.

The project compiled and ran successfully on both Windows using g++ and VS Code and the UNT CELL machine. All listed tests passed.