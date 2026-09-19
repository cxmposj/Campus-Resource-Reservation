#include "CancellationStack.h"
#include <iostream>

using namespace std;

// Creates a new stack
CancellationStack::CancellationStack()
{
    top = nullptr;
}

// Creates a new node
CancellationStack::Node::Node(const Reservation& res, Node* nextNode)
{
    reservation = res;
    next = nextNode;
}

// Adds a cancelled reservation to the top of the stack
void CancellationStack::push(const Reservation& reservation)
{
    top = new Node(reservation, top);
}

// Removes the most recently cancelled reservation
bool CancellationStack::pop(Reservation& reservation)
{
    if (top == nullptr)
    {
        return false;
    }

    reservation = top->reservation;

    Node* temp = top;
    top = top->next;

    delete temp;

    return true;
}

// Displays all cancelled reservations
void CancellationStack::display() const
{
    if (top == nullptr)
    {
        cout << "Cancellation history is empty." << endl;
        return;
    }

    Node* current = top;

    while (current != nullptr)
    {
        current->reservation.display();
        cout << "------------------------" << endl;
        current = current->next;
    }
}

// Checks whether the stack is empty
bool CancellationStack::isEmpty() const
{
    return top == nullptr;
}

// Deletes all nodes when the stack is destroyed
CancellationStack::~CancellationStack()
{
    while (top != nullptr)
    {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}