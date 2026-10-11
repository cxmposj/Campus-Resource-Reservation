# Campus Resource Reservation System – User Guide

## 1. About the Program

The Campus Resource Reservation System lets users view campus resources, create and cancel reservations, manage waiting lists, undo cancellations, search and sort resources, and generate reports about resource usage and demand.

## 2. How to Compile the Program

Make sure g++ is installed and all required project files are in the same folder.

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

### 1. Display Resources

Shows the campus resources, including their IDs, names, types, and availability.

### 2. Display Active Reservations

Shows the reservations that are currently active.

### 3. Create Reservation

Enter the reservation ID, student ID, student name, resource ID, and date. Dates must use the `YYYY-MM-DD` format, such as `2026-09-20`.

### 4. Cancel Reservation

Enter the ID of the reservation you want to cancel. If the reservation exists, it will be removed from the active reservations. A waiting-list request may be promoted when the matching resource and date become available.

### 5. Display Cancellation History

Shows reservations that have been cancelled and saved in the cancellation history stack.

### 6. Undo Cancellation

Attempts to restore the most recently cancelled reservation. Restoration may fail if the resource is no longer available for that date.

### 7. Join Waiting List

Enter the reservation ID, student ID, student name, resource ID, and date to join the waiting list for that resource and date.

### 8. Display Waiting Lists

Shows the requests currently waiting for resources.

### 9. Search Resource

Searches for a resource using its resource ID. If the resource exists, its information is displayed. If the ID does not match a resource, the program displays a not-found message.

### 10. Sort Resources by Name

Displays resources in alphabetical order by resource name.

### 11. Exit

Closes the program.

### 12. Resource Utilization Report

Displays the resources and the number of active reservations associated with each resource.

### 13. Waiting-List Statistics

Displays waiting-list request counts for each resource and the total number of waiting requests.

### 14. Most Requested Resources (Current Demand)

Displays the resource with the highest current request count. The count combines active reservations and waiting-list requests.

## 5. Important Tips

* Enter resource IDs exactly as they appear in the resource list, such as `R001`.
* Use the date format `YYYY-MM-DD`.
* Use unique reservation IDs.
* Check active reservations before booking a resource for a date.
* A waiting-list request may be promoted when the matching resource and date become available.
* Keep `resources.txt` in the appropriate location expected by the program so resources can be loaded.
* Use the menu options to search, sort, and review resource reports.

## 6. Testing and Limitations

The program compiled and ran successfully on Windows using g++ and VS Code, and it was also tested successfully on the UNT CELL machine.

Search, sorting, and all three reporting features were tested successfully in the integrated version. The reports were tested with no data and with reservation and waiting-list data.

The program should continue to be tested if future changes are made.
