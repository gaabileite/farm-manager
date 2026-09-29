/*
*The class Building sets the attributes and methods shared between the building elements in the read-only library.
*Its parent class, DataType, defines the default attributes, name and type, and its getters and setters.
*/

#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include "datatype.h"
using namespace std;

#ifndef BUILDING 
#define BUILDING

class Building: public DataType {
    private:
        vector<tuple<string, int>> constructionMaterials;
        tuple<int, int> size;
        string whereToGet;
        bool housesAnimals;
        vector<string> animalTypes;
        int animalAmount;

    public:
        // Two overloaded constructors.
        // strings, vectors and tuples by const reference
        // Avoids copying full lists from constructionMaterials, size and animalTypes for each new Building object.

        // Constructor for buildings that do NOT house animals.
        Building(const string& currentname, 
                const string& currenttype,
                const vector<tuple<string,int>>& constructionMaterials,
                tuple<int,int> size, 
                const string& whereToGet);

        // Constructor for buildings that DO house animals.
        Building(const string& currentname, 
            const string& currenttype,
                const vector<tuple<string,int>>& constructionMaterials,
                tuple<int,int> size, 
                const string& whereToGet,
                const vector<string>& animalTypes, 
                int animalAmount);

        // Destructor
        virtual ~Building();

        // Getters
        vector<tuple<string, int>> getConstructionMaterials() const;
        tuple<int, int> getSize() const;
        string getWhereToGet() const;
        bool getHousesAnimals() const;
        vector<string> getAnimalTypes() const;
        int getAnimalAmount() const;

        // Setters
        void setConstructionMaterials(const vector<tuple<string,int>>& newconstructionMaterials);
        void setSize(tuple<int, int> newsize);
        void setWhereToGet(const string& newwhereToGet);
        void setHousesAnimals(bool newhousesAnimals);
        void setAnimalTypes(const vector<string>& newanimalTypes);
        void setAnimalAmount(int newanimalAmount);
};

#endif