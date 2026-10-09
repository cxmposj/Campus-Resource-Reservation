# Campus-Resource-Reservation
Project 1 - Final Submission

# Project Description
This project is a Campus Resource Reservation System that helps students reserve different campus resources,
such as study rooms, laptops, calculators, and other resources. It helps keep track of the resources, reservations, waiting lists, and cancellation history. The system also includes searching and sorting features and provides reports on active reservations, resource utilization, and waiting-list information. 

# Team Members Contributions
1. Jose Campos - implemented Linear Search to find resources by resource ID and Merge sort to sort resources by resource name. Tested the searching and sorting functions to check that they worked correctly with the resource data. Made changes to the README, worked on the User Documentation, and made certain everything was added and correct in the GitHub. 
2. Rj Amuebie - Handled the final testing of the system to make sure the different features work correctly together. Worked on the main and integration of the project components. Reviewed the system's functionality, and helped identify and fix issues during testing and debugging. 
3. Adeoluwa Olukotun - Worked on the reporting part of the final project, including reports for active reservations, resource usage, and waiting lists. This includes organizing the reservation and waiting-list details and showing how resources are being used and how many students are waiting for each resource. 

# Main Features
- Manage and display campus resources
- Search for resources using their resource ID
- Sort resources alphabetically by resource name
- Create, display, and cancel reservations
- Manage waiting lists for unavailable resources
- Keep a history of canceled reservations
- Provide reports about reservations, resource usage, and waiting lists 

# Data Structures Used
The system uses different data structures to organize and manage the information, including a linked list for active reservations, a queue for waiting lists, a stack for cancellation history, and a vector for storing the resources and supporting the searching and sorting functions. 

- Linked List: Stores active reservations
- Queue: Manages waiting lists
- Stack: Stores cancellation history

# Searching and Sorting 
The project uses Linear Search to search for resources by their Resource ID. The search goes through the resources one at at time until it finds a resource with the matching ID or determines that the resource is not in the list, The project also uses Merge Sort to sort the resources by Resource Name, organizing the resources in order so they can be displayed in a organized way. 

# Reporting
The project includes reports that provide information about the resources and reservations in the system. These reports help show resource usage, the most requested resources, active reservations, and waiting list information. 

# How to Compile and Run 

g++-std=c++17 main.cpp Reservation.cpp
Resource. cp ReservationManager.cpp Waitinglist.cpp CancellationStationStack.cpp ResourceSearchSort.cpp -o CampusReservation

Ran: 

./CampusReservation

# Testing
We tested the resource and reservation functions to make sure the information was being stored and displayed correctly. 
We also tested the reservation features and input handling. 

# GitHub Repository
https://github.com/cxmposj/Campus-Resource-Reservation
