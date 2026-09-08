#include <string>
#include <vector>
#include <utility>
#include "../datatype.h"
using namespace std;

#ifndef BUILDING 
#define BUILDING

/*
The class Building inherits key attributes from the DataType class.
It houses buildings that support animals AND buildings that don't.
*/

class Building: public DataType {
    private:
    vector<pair<string, string>> constructionMaterials;
    pair<int, int> size;
    string whereToGet;
    bool housesAnimals;
    vector<string> animalTypes;
    int animalAmount;

    public:
    // Two overloaded constructors.

    // Constructor for buildings that do NOT house animals.
    // housesAnimals is set internally to false, animalTypes and animalAmount stay empty.
    Building(string currentname, string currenttype, vector<pair<string, string>> constructionMaterials, vector<int> size, string whereToGet);

    // Constructor for buildings that DO house animals.
    // housesAnimals is set internally to true, animalTypes and animalAmount are filled.
    Building(string currentname, string currenttype, vector<pair<string, string>> constructionMaterials, vector<int> size, string whereToGet, vector<string> animalTypes, int animalAmount);

    // Destructor
    virtual ~Building();

    // Getters
    vector<pair<string, string>> getConstructionMaterials() const;
    vector<int> getSize() const;
    string getWhereToGet() const;
    bool getHousesAnimals() const;
    vector<string> getAnimalTypes() const;
    int getAnimalAmount() const;

    // Setters
    void setConstructionMaterials(vector<pair<string, string>> newconstructionMaterials);
    void setSize(vector<int> newsize);
    void setWhereToGet(string newwhereToGet);
    void setHousesAnimals(bool newhousesAnimals);
    void setAnimalTypes(vector<string> newanimalTypes);
    void setAnimalAmount(int newanimalAmount);
};

#endif