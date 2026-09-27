#include <iostream>
#include <string>
using namespace std;

#ifndef MYBUILDING
#define MYBUILDING

class MyBuilding {
    private:
        string buildingName;
        string buildingType;
        int buildingLevel;

    public:
        // Constructor
        MyBuilding(string currentbuildingName, string currentbuildingType, int currentbuildingLevel);
        
        // Destructor
        virtual ~MyBuilding();

        // Getters
        string getBuildingName() const;
        string getBuildingType() const;
        int getBuildingLevel() const;

        // Setters
        void setBuildingName(string newbuildingName);
        void setBuildingType(string newbuildingType);
        void setBuildingLevel(int newbuildingLevel);
        
        // Auxiliares
        void upgradeBuilding();
};

#endif