#include <iostream>
#include <string>
using namespace std;

#ifndef MYFARM
#define MYFARM

/*
The class MyFarm is the start to the CRUD system of the program.
It serves as a model to the other classes that'll hold the information to the player's farm.
*/

class MyFarm {
    private:
        string farmName;
        string farmLayout;

    public:
        // Constructor
        MyFarm(string currentfarmName, string currentfarmLayout);

        // Destructor
        virtual ~MyFarm();

        // Getters
        string getFarmName() const;
        string getFarmLayout() const;

        // Setters
        void setFarmName(string newfarmName);
        void setFarmLayout(string newfarmLayout);

};

#endif