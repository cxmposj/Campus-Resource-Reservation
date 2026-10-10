# Campus Resource Reservation System – User Guide

## 1. About the Program

The Campus Resource Reservation System lets users view campus resources, create and cancel reservations, manage waiting lists, and undo cancellations.

## 2. How to Compile the Program

Make sure you have g++ installed and that all the project files are in the same folder.

On Windows, open the VS Code terminal and run:

```powershell
g++ -std=c++17 main.cpp Reservation.cpp Resource.cpp ReservationManager.cpp WaitingList.cpp CancellationStack.cpp ResourceSearchSort.cpp -o CampusReservation.exe
```

On the UNT CELL Linux machines, run:

```bash
g++ -std=c++17 main.cpp Reservation.cpp Resource.cpp ReservationManager.cpp WaitingList.cpp CancellationStack.cpp ResourceSearchSort.cpp -o CampusReservation
```

## 3. How to Run the Program

On Windows:

```powershell
.\CampusReservation.exe
```

On the CELL machines:

```bash
./CampusReservation
```

The program will display a menu. Enter the number for the action you want to perform.

## 4. Menu Options

**1. Display Resources**

Shows the campus resources loaded from `resources.txt`, including each resource's ID, name, type, and availability.

**2. Display Active Reservations**

Shows the reservations that are currently active.

**3. Create Reservation**

Enter the reservation ID, student ID, student name, resource ID, and date. Dates must use the `YYYY-MM-DD` format, such as `2026-09-20`.

If the resource is already reserved for that date, the request can be added to the waiting list.

**4. Cancel Reservation**

Enter the ID of the reservation you want to cancel. If the reservation exists, it will be removed from the active reservations. If someone is waiting for that resource and date, the next request may be promoted.

**5. Display Cancellation History**

Shows the reservations that have been cancelled and saved in the history stack.

**6. Undo Cancellation**

Attempts to restore the most recently cancelled reservation. Restoration may fail if the resource is no longer available for that date.

**7. Join Waiting List**

Enter the reservation ID, student ID, student name, resource ID, and date to join the waiting list for that resource and date.

**8. Display Waiting Lists**

Shows the requests currently waiting for resources.

**9. Exit**

Closes the program.

## 5. Important Tips

* Enter resource IDs exactly as they appear in the resource list, such as `R001`.
* Use the date format `YYYY-MM-DD`.
* Use unique reservation IDs.
* Check the active reservations before booking a resource for a date.
* A waiting-list request is promoted when the matching resource and date become available and the promotion succeeds.
* Keep `resources.txt` in the same folder as the program so the resources can be loaded.

## 6. Known Limitations

Searching, sorting, and reporting must be tested in the final integrated version before they are documented as working features.

The program should also be compiled and tested on the UNT CELL machines before the final submission.
