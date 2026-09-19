#include "ReservationManager.h"
#include <cctype>
#include <ostream>
#include <utility>

namespace {
bool blank(const std::string& text) {
    return text.find_first_not_of(" \t\n\r\f\v") == std::string::npos;
}

bool validId(const std::string& id) {
    if (id.empty()) return false;
    for (unsigned char ch : id) {
        if (std::isspace(ch)) return false;
    }
    return true;
}

bool validDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    for (std::size_t i = 0; i < date.size(); ++i) {
        if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9')) return false;
    }
    const int year = std::stoi(date.substr(0, 4));
    const int month = std::stoi(date.substr(5, 2));
    const int day = std::stoi(date.substr(8, 2));
    if (year == 0 || month < 1 || month > 12) return false;
    const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maximum = days[month - 1];
    const bool leap = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    if (month == 2 && leap) maximum = 29;
    return day >= 1 && day <= maximum;
}
} // namespace

ReservationManager::ReservationManager(ResourceValidator resourceExists)
    : head_(nullptr), count_(0), resourceExists_(std::move(resourceExists)) {}

ReservationManager::~ReservationManager() {
    // Save the link before deleting each node. O(n) cleanup.
    while (head_ != nullptr) {
        Node* old = head_;
        head_ = head_->next;
        delete old;
    }
}

const ReservationManager::Node*
ReservationManager::findNode(const std::string& id) const {
    for (const Node* current = head_; current != nullptr; current = current->next) {
        if (current->data.getID() == id) return current;
    }
    return nullptr;
}

bool ReservationManager::contains(const std::string& id) const {
    return findNode(id) != nullptr;
}

bool ReservationManager::findReservation(const std::string& id,
                                         Reservation& found) const {
    const Node* node = findNode(id);
    if (node == nullptr) return false;
    found = node->data; // Return a copy, so callers cannot change stored IDs.
    return true;
}

bool ReservationManager::createReservation(const Reservation& reservation,
                                           std::string& error) {
    error.clear();
    if (!validId(reservation.getID()) || !validId(reservation.getStudentID()) ||
        !validId(reservation.getResourceID())) {
        error = "IDs must be nonempty and contain no whitespace.";
        return false;
    }
    if (blank(reservation.getStudentName())) {
        error = "Student name is required.";
        return false;
    }
    if (!validDate(reservation.getDate())) {
        error = "Date must be a real calendar date in YYYY-MM-DD format.";
        return false;
    }
    if (contains(reservation.getID())) {
        error = "An active reservation already has that reservation ID.";
        return false;
    }
    if (!resourceExists_) {
        error = "Resource inventory lookup has not been connected.";
        return false;
    }
    if (!resourceExists_(reservation.getResourceID())) {
        error = "Resource ID does not exist in the inventory.";
        return false;
    }
    // Head insertion is O(1); duplicate checking makes creation O(n),
    // plus the inventory callback cost. Display order is newest first.
    head_ = new Node(reservation, head_);
    ++count_;
    return true;
}

bool ReservationManager::cancelReservation(const std::string& id,
                                           Reservation& removed,
                                           std::string& error) {
    error.clear();
    Node* previous = nullptr;
    Node* current = head_;
    while (current != nullptr && current->data.getID() != id) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) {
        error = "No active reservation has that ID.";
        return false;
    }
    // Copy before unlinking so history can retain the entire reservation.
    removed = current->data;
    if (previous == nullptr) head_ = current->next;
    else previous->next = current->next;
    delete current;
    --count_;
    // Search is O(n); unlinking the found node is O(1).
    return true;
}

void ReservationManager::displayReservations(std::ostream& out) const {
    if (head_ == nullptr) {
        out << "No active reservations.\n";
        return;
    }
    // O(n) traversal. Labels accommodate names of different lengths.
    for (const Node* current = head_; current != nullptr; current = current->next) {
        const Reservation& r = current->data;
        out << "Reservation ID: " << r.getID()
            << "\nStudent ID: " << r.getStudentID()
            << "\nStudent name: " << r.getStudentName()
            << "\nResource ID: " << r.getResourceID()
            << "\nReservation date: " << r.getDate() << "\n\n";
    }
}

std::size_t ReservationManager::size() const { return count_; }
