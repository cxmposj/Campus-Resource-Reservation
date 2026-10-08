# Campus-Resource-Reservation
Project 1 - Final Submission

# Project Description
This project is a Campus Resource Reservation System that helps students reserve different campus resources,
such as study rooms, laptops, calculators, and other resources. It helps keep track of the resources, reservations, waiting lists, and cancellation history. 

# Team Members Contributions
1. Jose Campos - Worked on the Resource and Reservation classes. Set up the Reservation class for student and reservation information,
with functions to access and display. Also implemented Linear Search to find resources by resource ID and Merge sort to sort resources by resource name. Made changes to the README, and made certain everything was added and correct in the GitHub. 
2. Rj Amuebie - Handled the cancellation history stack and complexity analysis. Adding functions to add, remove, and displayed
cancelled reservations. Also handled the final testing of the system to make sure the different features work correctly together. 
3. Adeoluwa Olukotun - Responsible for Reservation Management and the linked list. Handling the creation, cancellation, checking, and display of reservations, including inserting and removing reservation records. Worked on the waiting list features and will handl on the final reporting for the project. 

# Main Features
- Manage campus resource information
- Check resource availability
- Search for resources by Resource ID
- Sort resources by Resoucee Name 
- Create reservations
- Cancel reservations
- Display active reservations
- Manage waiting lists
- Keep track of cancellation history

# Data Structures Used
The system uses different data structures to organize and manage the information, including a linked list for active reservations, a queue for waiting lists, a stack for cancellation history, and a vector for storing the resources and supporting the searching and sorting functions. 

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
