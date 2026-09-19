#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>
using namespace std;

class Reservation {

     private;
        string resvID;
        string resvStudentID;
        string resvStudentName;
        string rescResourceID;
        string resvDate;

     public;
        Reservation():     //It would create a blank reservation with default information
        Reservation(string id, string studentID, string studentName, string resourceID, string date);    //Creates a reservation using the information provided by the user

        string getID() const;
        string getStudentID() const;
        string getStudentName() const;    //These are used to return after making the reservation
        string getResourceID() const;
        string getDate() const;

        void display() const;       //It displays all information stored for reservation
};

#endif
