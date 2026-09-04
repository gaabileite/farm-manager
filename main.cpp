#include <iostream>
#include <string>
#include <algorithm>
#include "classes/datatype.h"

// Declaration of DataType's methods.
    // Constructor
    DataType::DataType(string currentname, string currenttype) {
        name = currentname;
        type = currenttype;
    }
    // Destructor
    DataType::~DataType() {};

    // Getters
    string DataType::getName() const {
        return name;
    }
    string DataType::getType() const {
        return type;
    }

    // Setters
    void DataType::setName(string newname) {
        name = newname;
    }
    void DataType::setType(string newtype) {
        type = newtype;
    }