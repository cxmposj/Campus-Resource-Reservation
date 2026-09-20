#include "WaitingList.h"
#include "ReservationManager.h"
#include <cctype>
#include <ostream>
#include <utility>

namespace {
bool validId(const std::string& id) {
    if (id.empty()) return false;
    for (unsigned char c : id) if (std::isspace(c)) return false;
    return true;
}
bool validDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    for (std::size_t i = 0; i < date.size(); ++i)
        if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9')) return false;
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    if (year == 0 || month < 1 || month > 12) return false;
    const int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int maximum = days[month - 1];
    if (month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
        maximum = 29;
    return day >= 1 && day <= maximum;
}
}

WaitingList::WaitingList(const std::string& resourceId, const std::string& date,
                         ResourceValidator resourceExists)
    : resourceId_(resourceId), date_(date),
      resourceExists_(std::move(resourceExists)), front_(nullptr),
      rear_(nullptr), count_(0) {}

WaitingList::~WaitingList() {
    while (front_) {
        Node* old = front_;
        front_ = front_->next;
        delete old;
    }
}

bool WaitingList::enqueue(const Reservation& request, std::string& error) {
    error.clear();
    if (!validId(request.getID()) || !validId(request.getStudentID()) ||
        !validId(request.getResourceID()) ||
        request.getStudentName().find_first_not_of(" \t\r\n\f\v") == std::string::npos) {
        error = "Nonblank name and nonempty IDs without whitespace are required.";
        return false;
    }
    if (!validDate(request.getDate())) {
        error = "Date must be a real calendar date in YYYY-MM-DD format.";
        return false;
    }
    if (request.getResourceID() != resourceId_ || request.getDate() != date_) {
        error = "Request does not match this queue's resource and date.";
        return false;
    }
    if (!resourceExists_ || !resourceExists_(resourceId_)) {
        error = "Resource lookup is missing or the resource ID does not exist.";
        return false;
    }
    // O(q) validation. Raw rear insertion below is O(1).
    for (const Node* n = front_; n; n = n->next) {
        if (n->data.getID() == request.getID() ||
            n->data.getStudentID() == request.getStudentID()) {
            error = "Reservation ID or student is already in this waiting queue.";
            return false;
        }
    }
    Node* node = new Node(request);
    if (rear_) rear_->next = node;
    else front_ = node;
    rear_ = node;
    ++count_;
    return true;
}

bool WaitingList::dequeue(Reservation& removed) {
    if (!front_) return false;
    removed = front_->data;
    Node* old = front_;
    front_ = front_->next;
    if (!front_) rear_ = nullptr; // Permit reuse after removing the last node.
    delete old;
    --count_;
    return true;
}

bool WaitingList::peek(Reservation& front) const {
    if (!front_) return false;
    front = front_->data; // Copy prevents external mutation of queued IDs.
    return true;
}

bool WaitingList::promoteNext(ReservationManager& manager,
                              Reservation& promoted, std::string& error) {
    error.clear();
    if (!front_) {
        error = "Waiting queue is empty.";
        return false;
    }
    // Prepare all potentially throwing copies before changing either list.
    Reservation candidate = front_->data;
    Reservation originalOutput = promoted;
    promoted = candidate;
    if (!manager.createReservation(candidate, error)) {
        promoted = originalOutput;
        return false;
    }
    // Creation checks active IDs, resource existence, and resource/date conflicts.
    // Do not call dequeue here: another string copy could fail after creation.
    Node* old = front_;
    front_ = front_->next;
    if (!front_) rear_ = nullptr;
    delete old;
    --count_;
    return true;
}

void WaitingList::display(std::ostream& out) const {
    out << "Waiting list for " << resourceId_ << " on " << date_ << '\n';
    if (!front_) out << "No waiting requests.\n";
    for (const Node* n = front_; n; n = n->next) {
        out << "Reservation ID: " << n->data.getID()
            << " | Student ID: " << n->data.getStudentID()
            << " | Student name: " << n->data.getStudentName()
            << " | Resource ID: " << n->data.getResourceID()
            << " | Date: " << n->data.getDate() << '\n';
    }
}
bool WaitingList::empty() const { return front_ == nullptr; }
std::size_t WaitingList::size() const { return count_; }
