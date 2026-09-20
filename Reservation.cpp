#include "Reservation.h"
#include <iostream>
using namespace std;

Reservation::Reservation(){
    resvID = " ";
    resvStudentID = " ";
    resvStudentName = " ";     //This creates a default constructor for the Reservation class
    rescResourceID = " ";
    resvDate = " ";
}

Reservation::Reservation(string id, string studentID, string studentName, string resourceID, string date){
    resvID = id;
    resvStudentID = studentID;
    resvStudentName = studentName;     //It stores all information for the new reservation
    rescResourceID = resourceID;
    resvDate = date;
}

string Reservation::getID() const {
    return resvID;
}

string Reservation::getStudentID() const{
    return resvStudentID;
}

string Reservation::getStudentName() const{     //It returns all ID, name, resource ID, and date
    return resvStudentName;
}

string Reservation::getResourceID() const{
    return rescResourceID;
}

string Reservation::getDate() const{
    return resvDate;
}

void Reservation::display() const{
    cout << "Reservation ID: " << resvID << endl;
    cout << "Student ID: " << resvStudentID << endl;
    cout << "Student Name: " << resvStudentName << endl;     //This displays all information stored from the reservation
    cout << "Resource ID: " << rescResourceID << endl;
    cout << "Reservation Date: " << resvDate << endl;
}
