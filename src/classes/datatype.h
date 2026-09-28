/*
*The class DataType sets a set of default attributes and methods that are shared throughout the code.
*This specific class, as it is a parent class, houses the read-only classes, seen in animal.h, building.h, crop.h, viollager.h.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef DATATYPE
#define DATATYPE

class DataType {
    private:
        string name;
        string type;
    public:
        // Constructor
        DataType(string currentname, string currenttype);

        // Destructor
        virtual ~DataType();

        // Getters
        string getName() const;
        string getType() const;

        // Setters
        void setName(string newname);
        void setType(string newtype);
};

#endif
