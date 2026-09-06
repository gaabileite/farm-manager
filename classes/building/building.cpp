#include <string>
#include <vector> 
#include <utility>

using namespace std;

#include "building.h"

// Constructor: no animals housed
// housesAnimals defaults to false.
Building::Building(string currentname, string currenttype, vector<pair<string, string>> currentconstructionMaterials, vector<int> currentsize, string currentwhereToGet): DataType(currentname, currenttype) {
    constructionMaterials = currentconstructionMaterials;
    size = currentsize;
    whereToGet = currentwhereToGet;
    housesAnimals = false;
    // animalTypes stays as an empty vector
    animalAmount = 0;
}

// Constructor: houses animals
Building::Building(string currentname, string currenttype, vector<pair<string, string>> currentconstructionMaterials, vector<int> currentsize, string currentwhereToGet, vector<string> currentanimalTypes, int currentanimalAmount): DataType(currentname, currenttype) {
    constructionMaterials = currentconstructionMaterials;
    size = currentsize;
    whereToGet = currentwhereToGet;
    housesAnimals = true;
    animalTypes = currentanimalTypes;
    animalAmount = currentanimalAmount;
}

//Destructor
Building::~Building() {};

//Getters
vector<pair<string, string>> Building::getConstructionMaterials() const {
    return constructionMaterials;
}
vector<int> Building::getSize() const {
    return size;
}
string Building::getWhereToGet() const {
    return whereToGet;
}
bool Building::getHousesAnimals() const {
    return housesAnimals;
}
vector<string> Building::getAnimalTypes() const {
    return animalTypes;
}
int Building::getAnimalAmount() const {
    return animalAmount;
}

//Setters
void Building::setConstructionMaterials(vector<pair<string, string>> newconstructionMaterials) {
    constructionMaterials = newconstructionMaterials;
}
void Building::setSize(vector<int> newsize) {
    size = newsize;
}
void Building::setWhereToGet(string newwhereToGet) {
    whereToGet = newwhereToGet;
}
void Building::setHousesAnimals(bool newhousesAnimals) {
    housesAnimals = newhousesAnimals;
}
void Building::setAnimalTypes(vector<string> newanimalTypes) {
    animalTypes = newanimalTypes;
}
void Building::setAnimalAmount(int newanimalAmount) {
    animalAmount = newanimalAmount;
}
