#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Reservation.h"
#include <cstddef>
#include <functional>
#include <iosfwd>
#include <string>

// Create ONE manager for the entire system, shared by menu, queue, and undo.
// Its list stores all active reservations across all resources.
class ReservationManager {
public:
    // The inventory owner supplies this lookup. It must return true only
    // when the resource ID exists. The lookup's lifetime must cover its use.
    using ResourceValidator = std::function<bool(const std::string&)>;

    explicit ReservationManager(ResourceValidator resourceExists);
    ~ReservationManager();

    // This object owns its nodes; copying would otherwise double-delete them.
    ReservationManager(const ReservationManager&) = delete;
    ReservationManager& operator=(const ReservationManager&) = delete;

    bool createReservation(const Reservation& reservation, std::string& error);
    bool cancelReservation(const std::string& id, Reservation& removed,
                           std::string& error);
    bool findReservation(const std::string& id, Reservation& found) const;
    bool contains(const std::string& id) const;
    // O(n) search of active reservations. This checks conflicts only;
    // false does not validate resource existence or date formatting.
    bool hasConflict(const std::string& resourceId, const std::string& date) const;
    void displayReservations(std::ostream& out) const;
    std::size_t size() const;
    // Count active reservations for one resource: O(n) time, O(1) extra space.
    std::size_t countForResource(const std::string& resourceId) const;

private:
    struct Node {
        Reservation data;
        Node* next;
        Node(const Reservation& reservation, Node* following)
            : data(reservation), next(following) {}
    };

    Node* head_;
    std::size_t count_;
    ResourceValidator resourceExists_;

    const Node* findNode(const std::string& id) const;
};

#endif
