#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef DATATYPE
#define DATATYPE

/* 
The class DataType is the master class for all of the other types accessed by the user. 
Its attributes and methods are shared by all other classes in the program.
TODO: Decide if MyFarm fits into the DataType umbrella.
*/

class DataType {
    private:
        string name;
        string type;
    public:
        // Constructor
        DataType(string currentname, string currenttype) {
            name = currentname;
            type = currenttype;
        }
        // Destructor
        virtual ~DataType();

        // Getters
        string getName() const {
            return name;
        }
        string getType() const {
            return type;
        }

        // Setters
        void setName(string newname) {
            name = newname;
        }
        void setType(string newtype) {
            type = newtype;
        }
};

#endif
