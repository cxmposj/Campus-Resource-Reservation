#ifndef CANCELLATIONSTACK_H
#define CANCELLATIONSTACK_H

#include "Reservation.h"

class CancellationStack
{
private:
    struct Node
    {
        Reservation reservation;
        Node* next;

        Node(const Reservation& res, Node* nextNode = nullptr);
    };

    Node* top;

public:
    CancellationStack();
    ~CancellationStack();

    void push(const Reservation& reservation);
    bool pop(Reservation& reservation);
    void display() const;
    bool isEmpty() const;
};

#endif