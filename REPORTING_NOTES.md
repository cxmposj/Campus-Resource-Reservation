# Reporting

The reporting changes were developed with AI assistance. This document records the behavior and local checks; it does not establish compliance with course rules on AI use.

## Menu options

- **2 — Active reservations:** displays all active records and the total count.
- **10 — Resource utilization:** displays the active reservation count for each resource, including resources with zero reservations, across all dates.
- **11 — Waiting-list statistics:** displays distinct students waiting per resource across date-specific queues, plus waiting-request counts. A student waiting for two dates on the same resource counts as one student and two requests.
- **12 — Most requested resources:** displays all resources tied for the greatest current demand, defined as active reservations plus waiting requests across all dates. Displays no winner when all counts are zero.
- **9 — Exit:** unchanged.

All reports read the existing data without removing requests, changing FIFO order, or sorting the resource inventory. Resource IDs are assumed to be unique in the inventory.

## Meaning of most requested

The program currently has no lifetime request ledger. Option 12 therefore measures **current demand**, not all-time popularity. Cancelled and historical requests do not contribute. Moving a request from a waiting queue into active reservations does not by itself change the total demand. The assignment's intended time scope should be confirmed before treating this definition as final rubric compliance; historical totals would require additional tracking.

## Complexity

Let r be the number of resources, n the number of active reservations, k the number of date-specific queues, and w the total number of waiting requests. These bounds assume fixed-size IDs and constant-time queue size access.

| Report | Time | Extra space |
| --- | --- | --- |
| Active records and total | O(n + 1) | O(1) |
| Resource utilization | O(r * (n + 1)) | O(1) |
| Waiting statistics | O(r * k + w^2 + r) worst case | O(w) |
| Most requested | O(r * (n + k + 1)) | O(r) |

Waiting statistics uses a simple list of IDs to count each student once per resource. Comparing against prior IDs accounts for the quadratic worst-case term.

## Local verification

Local C++11 checks passed for resource utilization, waiting statistics, and most-requested reports with AddressSanitizer and UndefinedBehaviorSanitizer enabled. Cases included empty inventory, zero counts, multiple resources and dates, tied maximums, duplicate students across date queues, cancellation, successful promotion, unsuccessful restoration due to a conflict, and preservation of queue order and reservation counts while reporting. The current application also passed a menu smoke test for options 2, 10, 11, 12, and 9.

For a manual check, create two active reservations for resource A on different dates and one for resource B. Option 12 should show A with two. Add a waiting request for B: A and B should tie at two. Add a second waiting request for B on another date: B should lead with three. Option 11 should distinguish request count from distinct student count if that student is the same on both dates.

These checks used the current core application sources. The separate teammate search/sort module was not linked into the reporting test application and its integration is not verified here. Two existing warnings about unqualified `move` calls in the shared driver remain. Full team integration and testing on UNT CELL remain outstanding.
