# Reporting
This report was generated using the data maintained by our system 

## Menu options

- **2 — Active reservations:** displays all active records and the total count.
- **12 — Resource utilization:** displays the active reservation count for each resource, including resources with zero reservations, across all dates.
- **13 — Waiting-list statistics:** displays distinct students waiting per resource across date-specific queues, plus waiting-request counts. A student waiting for two dates on the same resource counts as one student and two requests.
- **14 — Most requested resources:** displays all resources tied for the greatest current demand, defined as active reservations plus waiting requests across all dates. Displays no winner when all counts are zero.
- **11 — Exit:** unchanged from the latest main branch. Search remains option 9 and sort remains option 10.

All reports read the existing data without removing requests, changing FIFO order, or sorting the resource inventory. Resource IDs are assumed to be unique in the inventory.

## Meaning of most requested

The program currently has no lifetime request ledger. Option 14 therefore measures **current demand**, not all-time popularity. Cancelled and historical requests do not contribute. Moving a request from a waiting queue into active reservations does not by itself change the total demand. The assignment's intended time scope should be confirmed before treating this definition as final rubric compliance; historical totals would require additional tracking.

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

Local C++17 checks passed for resource utilization, waiting statistics, and most-requested reports with AddressSanitizer and UndefinedBehaviorSanitizer enabled. Cases included empty inventory, zero counts, multiple resources and dates, tied maximums, duplicate students across date queues, cancellation, successful promotion, unsuccessful restoration due to a conflict, and preservation of queue order and reservation counts while reporting. The current application also passed a menu smoke test for the original reporting menu options; the integrated menu now uses 2, 12, 13, 14, and 11 for exit.

For a manual check, create two active reservations for resource A on different dates and one for resource B. Option 14 should show A with two. Add a waiting request for B: A and B should tie at two. Add a second waiting request for B on another date: B should lead with three. Option 13 should distinguish request count from distinct student count if that student is the same on both dates.

The October 11 merge includes the latest search/sort implementation and preserves search (9), sort (10), and exit (11). The full application compiled locally with C++17, and the three report test suites passed with search/sort linked. Further end-to-end testing was skipped at the project contributor's request. Existing compiler warnings about unqualified `move` calls and a signed/unsigned loop comparison remain. Testing on UNT CELL is still outstanding.
