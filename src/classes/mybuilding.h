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
        MyBuilding(const string& currentbuildingName, 
                   const string& currentbuildingType, 
                   int currentbuildingLevel);
        
        // Destructor
        virtual ~MyBuilding();

        // Getters
        string getBuildingName() const;
        string getBuildingType() const;
        int getBuildingLevel() const;

        // Setters
        void setBuildingName(const string& newbuildingName);
        void setBuildingType(const string& newbuildingType);
        void setBuildingLevel(int newbuildingLevel);
        
        // Auxiliares
        void upgradeBuilding();
};

#endif