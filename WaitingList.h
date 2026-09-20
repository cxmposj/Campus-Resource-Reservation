#ifndef WAITING_LIST_H
#define WAITING_LIST_H

#include "Reservation.h"
#include <cstddef>
#include <functional>
#include <iosfwd>
#include <string>

class ReservationManager;

// One FIFO queue for a resource/date pair. Keep one queue per pair in the
// coordinator; all queues share the ONE active ReservationManager.
class WaitingList {
public:
    using ResourceValidator = std::function<bool(const std::string&)>;
    WaitingList(const std::string& resourceId, const std::string& date,
                ResourceValidator resourceExists);
    ~WaitingList();
    WaitingList(const WaitingList&) = delete;
    WaitingList& operator=(const WaitingList&) = delete;

    bool enqueue(const Reservation& request, std::string& error);
    bool dequeue(Reservation& removed); // Remove front only: FIFO, O(1).
    bool peek(Reservation& front) const;
    void display(std::ostream& out) const;
    bool empty() const;
    std::size_t size() const;

    // Call after this resource/date becomes free. Removes the front ONLY
    // after active reservation creation succeeds; failed requests stay queued.
    bool promoteNext(ReservationManager& manager, Reservation& promoted,
                     std::string& error);

private:
    struct Node {
        Reservation data;
        Node* next;
        explicit Node(const Reservation& request) : data(request), next(nullptr) {}
    };
    std::string resourceId_;
    std::string date_;
    ResourceValidator resourceExists_;
    Node* front_;
    Node* rear_;
    std::size_t count_;
};
#endif
