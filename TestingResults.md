# Project 1 – Testing Results

## Testing Environment

The program was compiled and tested on a Windows computer using g++ and VS Code. The project was also compiled after the search and sorting files were added.

## Test Results

| Test                                    | Expected Result                                                        | Actual Result                                                             | Status     |
| --------------------------------------- | ---------------------------------------------------------------------- | ------------------------------------------------------------------------- | ---------- |
| Compile the project                     | All source files compile without errors                                | The project compiled successfully using g++                               | Pass       |
| Start the program                       | The main menu appears                                                  | The menu appeared correctly                                               | Pass       |
| Display resources                       | All resources and their availability are displayed                     | Four resources were displayed with their availability                     | Pass       |
| Create a valid reservation              | The reservation is added to the active reservations                    | Reservation R100 was created successfully                                 | Pass       |
| Enter an invalid date                   | The program rejects the date and displays an error                     | The date `12012005` was rejected because it did not use YYYY-MM-DD format | Pass       |
| Enter an ID containing spaces           | The program rejects the invalid ID                                     | The program displayed an error about IDs containing whitespace            | Pass       |
| Display active reservations             | All active reservations are shown                                      | R100 appeared in the active reservation list                              | Pass       |
| Cancel a reservation                    | The reservation is removed from active reservations                    | R100 was cancelled successfully                                           | Pass       |
| View cancellation history               | The cancelled reservation appears in the history stack                 | R100 appeared in the cancellation history                                 | Pass       |
| Undo a cancellation                     | The most recently cancelled reservation is restored                    | R100 was restored to active reservations                                  | Pass       |
| Add a waiting-list request              | A request for an already-booked resource and date is queued            | R101 was added to the waiting list when R100 already held that slot       | Pass       |
| Promote a waiting-list request          | The next student is promoted after the active reservation is cancelled | R101 was promoted after R100 was cancelled                                | Pass       |
| Search for a resource                   | The resource is found by its ID                                        | Needs testing after the search feature is connected to the menu           | Not tested |
| Sort resources                          | Resources are displayed in alphabetical order by name                  | Needs testing after the sorting feature is connected and fixed            | Not tested |
| Generate reports                        | The required system reports display the correct information            | Needs testing after the reporting feature is integrated                   | Not tested |
| Compile and run on the UNT CELL machine | The project compiles and runs successfully on CELL                     | Final verification still needed                                           | Not tested |

## Summary

The basic reservation, cancellation, cancellation history, undo, and waiting-list features were tested successfully on Windows. Invalid dates and IDs containing spaces were also rejected correctly.

The search, sorting, and reporting features still need to be tested after they are connected to the program. The final version also needs to be compiled and tested on the UNT CELL machines before submission.
