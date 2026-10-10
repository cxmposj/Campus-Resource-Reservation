#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "WaitingList.h"
#include "CancellationStack.h"
#include "ResourceSearchSort.h"

using namespace std;

bool loadResources(string filename, vector<Resource>& resources)
{
    ifstream file(filename);

    if (!file)
    {
        cout << "Could not open resources.txt" << endl;
        return false;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        string id, name, type, available;
        stringstream ss(line);

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, available);

        bool isAvailable = (available == "1");

        resources.push_back(Resource(id, name, type, isAvailable));
    }

    file.close();
    return true;
}

bool resourceExists(const vector<Resource>& resources, string id)
{
    for (const Resource& r : resources)
    {
        if (r.getID() == id)
            return true;
    }

    return false;
}

struct WaitingQueue
{
    string resourceID;
    string date;
    unique_ptr<WaitingList> queue;
};

int main()
{
    vector<Resource> resources;

    if (!loadResources("resources.txt", resources))
        return 1;

    auto checkResource = [&resources](const string& id)
    {
        return resourceExists(resources, id);
    };

    ReservationManager reservationManager(checkResource);
    CancellationStack cancellationHistory;

    vector<WaitingQueue> waitingLists;

    int choice;

    do
    {
        cout << endl;
        cout << "===== Campus Resource Reservation System =====" << endl;
        cout << "1. Display Resources" << endl;
        cout << "2. Display Active Reservations" << endl;
        cout << "3. Create Reservation" << endl;
        cout << "4. Cancel Reservation" << endl;
        cout << "5. Display Cancellation History" << endl;
        cout << "6. Undo Cancellation" << endl;
        cout << "7. Join Waiting List" << endl;
        cout << "8. Display Waiting Lists" << endl;
        cout << "9. Search Resource" << endl; 
        cout << "10. Sort Resources by Name" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            cout << endl;
            cout << "===== Resources =====" << endl;

            for (const Resource& r : resources)
            {
                r.display();
            }
        }

        else if (choice == 2)
        {
            cout << endl;
            cout << "===== Active Reservations =====" << endl;

            reservationManager.displayReservations(cout);
        }

        else if (choice == 3)
        {
            string resvID;
            string studentID;
            string studentName;
            string resourceID;
            string date;
            string error;

            cout << "Reservation ID: ";
            getline(cin, resvID);

            cout << "Student ID: ";
            getline(cin, studentID);

            cout << "Student Name: ";
            getline(cin, studentName);

            cout << "Resource ID: ";
            getline(cin, resourceID);

            cout << "Date (YYYY-MM-DD): ";
            getline(cin, date);

            Reservation newReservation(
                resvID,
                studentID,
                studentName,
                resourceID,
                date
            );

            if (reservationManager.createReservation(
                    newReservation, error))
            {
                cout << "Reservation created." << endl;
            }
            else
            {
                if (reservationManager.hasConflict(resourceID, date))
                {
                    bool foundQueue = false;

                    for (WaitingQueue& w : waitingLists)
                    {
                        if (w.resourceID == resourceID &&
                            w.date == date)
                        {
                            if (w.queue->enqueue(newReservation, error))
                            {
                                cout << "Resource is already reserved." << endl;
                                cout << "Added to waiting list." << endl;
                            }
                            else
                            {
                                cout << error << endl;
                            }

                            foundQueue = true;
                            break;
                        }
                    }

                    if (!foundQueue)
                    {
                        WaitingQueue newQueue;

                        newQueue.resourceID = resourceID;
                        newQueue.date = date;

                        newQueue.queue =
                            make_unique<WaitingList>(
                                resourceID,
                                date,
                                checkResource
                            );

                        if (newQueue.queue->enqueue(
                                newReservation, error))
                        {
                            cout << "Resource is already reserved." << endl;
                            cout << "Added to waiting list." << endl;

                            waitingLists.push_back(move(newQueue));
                        }
                        else
                        {
                            cout << error << endl;
                        }
                    }
                }
                else
                {
                    cout << "Reservation could not be created." << endl;
                    cout << error << endl;
                }
            }
        }

        else if (choice == 4)
        {
            string id;

            cout << "Enter reservation ID to cancel: ";
            getline(cin, id);

            Reservation cancelled;
            string error;

            if (reservationManager.cancelReservation(
                    id, cancelled, error))
            {
                cancellationHistory.push(cancelled);

                cout << "Reservation cancelled." << endl;

                for (WaitingQueue& w : waitingLists)
                {
                    if (w.resourceID == cancelled.getResourceID() &&
                        w.date == cancelled.getDate())
                    {
                        if (!w.queue->empty())
                        {
                            Reservation promoted;
                            string promoteError;

                            if (w.queue->promoteNext(
                                    reservationManager,
                                    promoted,
                                    promoteError))
                            {
                                cout << "The next person on the "
                                     << "waiting list got the reservation."
                                     << endl;
                            }
                        }

                        break;
                    }
                }
            }
            else
            {
                cout << error << endl;
            }
        }

        else if (choice == 5)
        {
            cout << endl;
            cout << "===== Cancellation History =====" << endl;

            cancellationHistory.display();
        }

        else if (choice == 6)
        {
            Reservation restored;

            if (cancellationHistory.pop(restored))
            {
                string error;

                if (reservationManager.createReservation(
                        restored, error))
                {
                    cout << "Reservation restored." << endl;
                }
                else
                {
                    cancellationHistory.push(restored);
                    cout << "Could not restore reservation." << endl;
                    cout << error << endl;
                }
            }
            else
            {
                cout << "No cancelled reservations to restore." << endl;
            }
        }

        else if (choice == 7)
        {
            string resvID;
            string studentID;
            string studentName;
            string resourceID;
            string date;
            string error;

            cout << "Reservation ID: ";
            getline(cin, resvID);

            cout << "Student ID: ";
            getline(cin, studentID);

            cout << "Student Name: ";
            getline(cin, studentName);

            cout << "Resource ID: ";
            getline(cin, resourceID);

            cout << "Date (YYYY-MM-DD): ";
            getline(cin, date);

            Reservation waitingReservation(
                resvID,
                studentID,
                studentName,
                resourceID,
                date
            );

            bool foundQueue = false;

            for (WaitingQueue& w : waitingLists)
            {
                if (w.resourceID == resourceID &&
                    w.date == date)
                {
                    if (w.queue->enqueue(
                            waitingReservation, error))
                    {
                        cout << "Added to waiting list." << endl;
                    }
                    else
                    {
                        cout << error << endl;
                    }

                    foundQueue = true;
                    break;
                }
            }

            if (!foundQueue)
            {
                WaitingQueue newQueue;

                newQueue.resourceID = resourceID;
                newQueue.date = date;

                newQueue.queue =
                    make_unique<WaitingList>(
                        resourceID,
                        date,
                        checkResource
                    );

                if (newQueue.queue->enqueue(
                        waitingReservation, error))
                {
                    cout << "Added to waiting list." << endl;
                    waitingLists.push_back(move(newQueue));
                }
                else
                {
                    cout << error << endl;
                }
            }
        }

        else if (choice == 8)
        {
            cout << endl;
            cout << "===== Waiting Lists =====" << endl;

            if (waitingLists.empty())
            {
                cout << "No waiting lists." << endl;
            }
            else
            {
                for (WaitingQueue& w : waitingLists)
                {
                    cout << endl;
                    w.queue->display(cout);
                }
            }
        }
        else if (choice == 9)
        {
            string id;
            cout << "Enter Resource ID to search: ";
            getline(cin, id);

            int index = search

        else if (choice == 11)
        {
            cout << "Goodbye!" << endl;
        }

        else
        {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 11);

    return 0;
}
