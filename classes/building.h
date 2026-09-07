#include <string>
#include <vector>
#include <utility>

using namespace std;

#ifndef BUILDING 
#define BUILDING

#include "../datatype.h"

class Building: public DataType {
    private:
    vector<pair<string, string>> constructionMaterials;
    vector<int> size;
    string whereToGet;
    bool housesAnimals;
    vector<string> animalTypes;
    int animalAmount;

    public:
    // Two overloaded constructors: the compiler picks one automatically based on how many arguments are passed at object creation.

    // Constructor for buildings that do NOT house animals.
    // housesAnimals is set internally to false, animalTypes/animalAmount stay empty/0.
    Building(string currentname, string currenttype, vector<pair<string, string>> constructionMaterials, vector<int> size, string whereToGet);

    // Constructor for buildings that DO house animals.
    // housesAnimals is set internally to true.
    Building(string currentname, string currenttype, vector<pair<string, string>> constructionMaterials, vector<int> size, string whereToGet, vector<string> animalTypes, int animalAmount);

    // Destructor
    virtual ~Building();

    //Getters
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