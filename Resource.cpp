#include "Resource.h"
#include <iostream>
using namespace std;

Resource::Resource(){      //This creates an empty resource and sets it as available by default

        resID = " ";
        resName = " ";
        resType = " ";
        resAvailable = true;
   }

Resource::Resource(string id, string name, string type, bool available){

        resID = id;
        resName = name;                 //Constructor with all of the resource information
        resType = type;
        resAvailable = available;
   }

string Resource::getID() const {
    return resID;
}

string Resource::getName() const {
    return resName;
}

string Resource::getType() const{       //Returns ID, name, type, and availability
    return resType;
}

bool Resource::isAvailable() const {    //Returns true when the resource is available
    return resAvailable;
}

void Resource::setAvailable(bool available) {    //This is used to change the availability status
    resAvailable = available;
}

void Resource::display() const {

      cout << resID << " | " <<  resName << " | " << resType << " | ";     //It would display all resource information

   if (resAvailable)
     cout << "Available";
  else
     cout << "Not Available";

cout << endl;
}
