#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
using namespace std;

class Resource {

     private:
        string resID;
        string resName;           //Stores the resource for ID, name, type
        string resType;
        bool resAvailable;        //Stores whether if the resource is available

     public:
        Resource();           // The creates an empty resource and makes it available
        Resource(string id, string name, string type, bool available);    //It creates a resource using the information 

        string getID() const;
        string getName() const;     //Returns for ID, name, type
        string getType() const;
        bool isAvailable() const;          //Checks if the resource is available
        void setAvailable(bool available);

        void display() const;     //It displays the resource information
};

#endif
