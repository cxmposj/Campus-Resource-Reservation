# Milestone 1 – Complexity Analysis

## Reservation Insertion

Reservation insertion is **O(n)**.

The new reservation is added to the front of the linked list, which only takes O(1). However, before adding it, the program checks if the reservation ID is already being used and checks if the resource is already reserved for that date. These checks may have to go through the whole list, so the overall operation is O(n).

## Reservation Removal

Reservation removal is **O(n)**.

The program has to look through the linked list to find the reservation that needs to be cancelled. In the worst case, it may have to go through the whole list. After it finds the reservation, removing it is O(1), but finding it makes the overall operation O(n).

## Waiting-List Processing

Waiting-list processing is **O(n)**.

The queue can add and remove students from the front or back in O(1). However, when the next student is moved from the waiting list to an active reservation, the program has to check the active reservations first. That search can take O(n), so the overall process is O(n).

## Undo Cancellation

Undo cancellation is **O(1)**.

Cancelled reservations are stored in a stack. The most recently cancelled reservation is always on top, so the program can remove it directly without searching through the rest of the stack. This makes the undo operation O(1).
