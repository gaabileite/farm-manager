/*
*The following .cpp file houses the definitions of all the classes that were declared in the header of the classes/ folder.
*The definitions are for each of the methods that are in the headers.
*This file is compiled along with the other .cpp.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include "classes/datatype.h"
#include "classes/animal.h"
#include "classes/building.h"
#include "classes/crop.h"
#include "classes/villager.h"
#include "classes/database.h"
#include "classes/myfarm.h"
#include "menus/filters.h"
#include "menus/menu.h"
#include "classes/myanimal.h"
#include "classes/myrelationship.h"
#include "classes/mybuilding.h"

/*
----------------------------------------------- STATIC DATA - READ-ONLY ----------------------------------------------
*/

// ---------- DATATYPE CLASS ----------
// Constructor
DataType::DataType(const string& currentname, const string& currenttype) {
    name = currentname;
    type = currenttype;
}

// Destructor
DataType::~DataType() {};

// Getters
string DataType::getName() const { return name; }
string DataType::getType() const { return type; }

// Setters
void DataType::setName(const string& newname) { name = newname; }
void DataType::setType(const string& newtype) { type = newtype; }

// ---------- ANIMAL CLASS ----------
// Constructor
// DataType's constructor initializes the inherited part of the Animal object.
Animal::Animal(const string& currentname, const string& currenttype, const string& currentproduces, int currentdaysToAdult, int currentbuyPrice, const vector<tuple<string, string, int>>& currentartisanItem) : DataType(currentname, currenttype) {
    produces = currentproduces;
    daysToAdult = currentdaysToAdult;
    buyPrice = currentbuyPrice;
    artisanItem = currentartisanItem;
}

// Destructor
Animal::~Animal() {};

// Getters
string Animal::getProduces() const { return produces; }
int Animal::getDaysToAdult() const { return daysToAdult; }
int Animal::getBuyPrice() const { return buyPrice; }
vector<tuple<string, string, int>> Animal::getArtisanItem() const { return artisanItem; }

// Setters
void Animal::setProduces(const string& newproduces) { produces = newproduces; }
void Animal::setDaysToAdult(int newdaysToAdult) { daysToAdult = newdaysToAdult; }
void Animal::setBuyPrice(int newbuyPrice) { buyPrice = newbuyPrice; }
void Animal::setArtisanItem(const vector<tuple<string, string, int>>& newartisanItem) { artisanItem = newartisanItem; }

// ---------- BUILDING CLASS ----------
// Constructor: no animals housed
// housesAnimals defaults to false.
Building::Building(const string& currentname, const string& currenttype, const vector<tuple<string, int>>& currentconstructionMaterials, tuple<int, int> currentsize, const string& currentwhereToGet): DataType(currentname, currenttype) {
    constructionMaterials = currentconstructionMaterials;
    size = currentsize;
    whereToGet = currentwhereToGet;
    housesAnimals = false;
    // animalTypes stays as an empty vector
    animalAmount = 0;
}

// Constructor: houses animals
// housesAnimals defaults to true.
Building::Building(const string& currentname, const string& currenttype, const vector<tuple<string, int>>& currentconstructionMaterials, tuple<int, int> currentsize, const string& currentwhereToGet, const vector<string>& currentanimalTypes, int currentanimalAmount): DataType(currentname, currenttype) {
    constructionMaterials = currentconstructionMaterials;
    size = currentsize;
    whereToGet = currentwhereToGet;
    housesAnimals = true;
    animalTypes = currentanimalTypes;
    animalAmount = currentanimalAmount;
}

// Destructor
Building::~Building() {};

// Getters
vector<tuple<string, int>> Building::getConstructionMaterials() const { return constructionMaterials; }
tuple<int, int> Building::getSize() const { return size; }
string Building::getWhereToGet() const { return whereToGet; }
bool Building::getHousesAnimals() const { return housesAnimals; }
vector<string> Building::getAnimalTypes() const { return animalTypes; }
int Building::getAnimalAmount() const { return animalAmount; }

// Setters
void Building::setConstructionMaterials(const vector<tuple<string, int>>& newconstructionMaterials) { constructionMaterials = newconstructionMaterials; }
void Building::setSize(tuple<int, int> newsize) { size = newsize; }
void Building::setWhereToGet(const string& newwhereToGet) { whereToGet = newwhereToGet; }
void Building::setHousesAnimals(bool newhousesAnimals) { housesAnimals = newhousesAnimals; }
void Building::setAnimalTypes(const vector<string>& newanimalTypes) { animalTypes = newanimalTypes; }
void Building::setAnimalAmount(int newanimalAmount) { animalAmount = newanimalAmount; }

// ---------- CROP CLASS ----------
// Constructor
Crop::Crop(const string& currentname, const string& currenttype, const string& currentseason, int currentdaysToHarvest, int currentregrow, int currentdaysToRegrowth, const vector<tuple<string,int>>& currentsellValue, const vector<tuple<string,int>>& currentseedPrice, const vector<tuple<string, string, int>>& currentartisanItems): DataType(currentname, currenttype) {
    season = currentseason;
    daysToHarvest = currentdaysToHarvest;
    regrow = currentregrow;
    daysToRegrowth = currentdaysToRegrowth;
    sellValue = currentsellValue;
    seedPrice = currentseedPrice;
    artisanItems = currentartisanItems;
}

// Destructor
Crop::~Crop() {};

// Getters
string Crop::getSeason() const { return season; }
int Crop::getDaysToHarvest() const { return daysToHarvest; }
int Crop::getRegrow() const { return regrow; }
int Crop::getDaysToRegrowth() const { return daysToRegrowth; }
vector<tuple<string,int>> Crop::getSellValue() const { return sellValue; }
vector<tuple<string,int>> Crop::getSeedPrice() const { return seedPrice; }
vector<tuple<string, string, int>> Crop::getArtisanItems() const { return artisanItems; }

// Setters
void Crop::setSeason(const string& newseason) { season = newseason; }
void Crop::setDaysToHarvest(int newdaysToHarvest) { daysToHarvest = newdaysToHarvest; }
void Crop::setRegrow(int newregrow) { regrow = newregrow; }
void Crop::setDaysToRegrowth(int newdaysToRegrowth) { daysToRegrowth = newdaysToRegrowth; }
void Crop::setSellValue(const vector<tuple<string,int>>& newsellValue) { sellValue = newsellValue; }
void Crop::setSeedPrice(const vector<tuple<string,int>>& newseedPrice) { seedPrice = newseedPrice; }
void Crop::setArtisanItems(const vector<tuple<string, string, int>>& newartisanItems) { artisanItems = newartisanItems; }

// ---------- VILLAGER CLASS ----------
// Constructor
Villager::Villager(const string& currentname, const string& currenttype, bool currentsingle, const string& currentgiftLike, const string& currentgiftLove): DataType(currentname, currenttype) {
    single = currentsingle;
    giftLike = currentgiftLike;
    giftLove = currentgiftLove;
}

// Destructor
Villager::~Villager() {};

// Getters
bool Villager::getSingle() const { return single; }
string Villager::getGiftLike() const { return giftLike; }
string Villager::getGiftLove() const { return giftLove; }

// Setters
void Villager::setGiftLike(const string& newgiftLike) { giftLike = newgiftLike; }
void Villager::setGiftLove(const string& newgiftLove) { giftLove = newgiftLove; }

/*
----------------------------------------------- CRUD MENU - MYFARM ------------------------------------------------
*/

// ---------- MY FARM ----------
// Declaration of MyFarm's methods.

// Constructor
MyFarm::MyFarm(const string& currentfarmName, const string& currentfarmLayout) {
    farmName = currentfarmName;
    farmLayout = currentfarmLayout;
}

// Destructor
MyFarm::~MyFarm() {};

// Getters
string MyFarm::getFarmName() const {
    return farmName;
}
string MyFarm::getFarmLayout() const {
    return farmLayout;
}

// Setters
void MyFarm::setFarmName(const string& newfarmName) {
    farmName = newfarmName;
}
void MyFarm::setFarmLayout(const string& newfarmLayout) {
    farmLayout = newfarmLayout;
}

// ---------- MY ANIMAL ----------
// Declaring MyAnimal's methods

// Constructor
MyAnimal::MyAnimal(const string& currentanimalName, const string& currentanimalType, int currentanimalRelationship) {
    animalName = currentanimalName;
    animalType = currentanimalType;
    animalRelationship = currentanimalRelationship;
}

// Destructor
MyAnimal::~MyAnimal() {}

// Getters
string MyAnimal::getAnimalName() const {
    return animalName;
}
string MyAnimal::getAnimalType() const {
    return animalType;
}
int MyAnimal::getAnimalRelaionship() const {
    return animalRelationship;
}

// Setters
void MyAnimal::setAnimalName(const string& newanimalName) {
    animalName = newanimalName;
}
void MyAnimal::setAnimalType(const string& newanimalType) {
    animalType = newanimalType;
}
void MyAnimal::setAnimalRelationship(int newanimalRelationship) {
    animalRelationship = newanimalRelationship;
}

// Incrementa a pontuação de afeição do animal com o jogador.
void MyAnimal::addHeart(int addedRelationship) {
    animalRelationship += addedRelationship;
}

// ---------- MY RELATIONSHIP ----------
// Declaring MyRelationship's methods

// Constructor
MyRelationship::MyRelationship(const string& currentvillagerName, int currentfriendship) {
    villagerName = currentvillagerName;
    friendship = currentfriendship;
}

// Destructor
MyRelationship::~MyRelationship() {}

//Getters
string MyRelationship::getVillagerName() const {
    return villagerName;
}
int MyRelationship::getFriendship() const {
    return friendship;
}

//Setters
void MyRelationship::setVillagerName(const string& newVillagerName) {
    villagerName = newVillagerName;
}
void MyRelationship::setFriendship(int newFriendship) {
    friendship = newFriendship;
}

// Incrementa a pontuação de amizade com o morador.
void MyRelationship::increaseFriendship(int addedFriendship) {
    friendship += addedFriendship;
}

// Reduz a pontuação de amizade com o morador.
void MyRelationship::decreaseFriendship(int reducedFriendship) {
    friendship -= reducedFriendship;
}

// ---------- MY BUILDING ----------
// Declaration of MyBuilding's methods.

// Constructor
MyBuilding::MyBuilding(const string& currentbuildingName, const string& currentbuildingType, int currentbuildingLevel) {
    buildingName = currentbuildingName;
    buildingType = currentbuildingType;
    buildingLevel = currentbuildingLevel;
}

// Destructor
MyBuilding::~MyBuilding() {};

// Getters
string MyBuilding::getBuildingName() const {
    return buildingName;
}
string MyBuilding::getBuildingType() const {
    return buildingType;
}
int MyBuilding::getBuildingLevel() const {
    return buildingLevel;
}

// Setters
void MyBuilding::setBuildingName(const string& newbuildingName) {
    buildingName = newbuildingName;
}
void MyBuilding::setBuildingType(const string& newbuildingType) {
    buildingType = newbuildingType;
}
void MyBuilding::setBuildingLevel(int newbuildingLevel) {
    buildingLevel = newbuildingLevel;
}

// Eleva o nível de melhoria da construção em uma unidade.
void MyBuilding::upgradeBuilding() {
    buildingLevel++;
}
