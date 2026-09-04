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
