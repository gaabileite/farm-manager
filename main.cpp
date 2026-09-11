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

// Declaration of Animal's methods.
   // Constructor
   // DataType's constructor initializes the inherited part of the Animal object.
    Animal::Animal(string currentname, string currenttype, string currentproduces, int currentdaysToAdult, int currentbuyPrice, vector<tuple<string, string, int>> currentartisanItem) : DataType(currentname, currenttype) {
        produces = currentproduces;
        daysToAdult = currentdaysToAdult;
        buyPrice = currentbuyPrice;
        artisanItem = currentartisanItem;
    }

    // Destructor
    Animal::~Animal() {};

    // Getters
    string Animal::getProduces() const {
        return produces;
    }
    int Animal::getDaysToAdult() const {
        return daysToAdult;
    }
    int Animal::getBuyPrice() const {
        return buyPrice;
    }
    vector<tuple<string, string, int>> Animal::getArtisanItem() const {
        return artisanItem;
    }

    // Setters
    void Animal::setProduces(string newproduces) {
        produces = newproduces;
    }
    void Animal::setDaysToAdult(int newdaysToAdult) {
        daysToAdult = newdaysToAdult;
    }
    void Animal::setBuyPrice(int newbuyPrice) {
        buyPrice = newbuyPrice;
    }
    void Animal::setArtisanItem(vector<tuple<string, string, int>> newartisanItem) {
        artisanItem = newartisanItem;
    }

// Declaration of Building's methods.
    // Constructor: no animals housed
    // housesAnimals defaults to false.
    Building::Building(string currentname, string currenttype, vector<tuple<string, int>> currentconstructionMaterials, tuple<int, int> currentsize, string currentwhereToGet): DataType(currentname, currenttype) {
        constructionMaterials = currentconstructionMaterials;
        size = currentsize;
        whereToGet = currentwhereToGet;
        housesAnimals = false;
        // animalTypes stays as an empty vector
        animalAmount = 0;
    }

    // Constructor: houses animals
    Building::Building(string currentname, string currenttype, vector<tuple<string, int>> currentconstructionMaterials, tuple<int, int> currentsize, string currentwhereToGet, vector<string> currentanimalTypes, int currentanimalAmount): DataType(currentname, currenttype) {
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
    vector<tuple<string, int>> Building::getConstructionMaterials() const {
        return constructionMaterials;
    }
    tuple<int, int> Building::getSize() const {
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

    // Setters
    void Building::setConstructionMaterials(vector<tuple<string, int>> newconstructionMaterials) {
        constructionMaterials = newconstructionMaterials;
    }
    void Building::setSize(tuple<int, int> newsize) {
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

// Declaration of Crop's methods.
    // Constructor
    Crop::Crop(string currentname, string currenttype, string currentseason, int currentdaysToHarvest, int currentregrow, int currentdaysToRegrowth, vector<tuple<string,int>> currentsellValue, vector<tuple<string,int>> currentseedPrice, vector<tuple<string, string, int>> currentartisanItems): DataType(currentname, currenttype) {
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
    string Crop::getSeason() const { 
      return season; 
    }
    int Crop::getDaysToHarvest() const { 
      return daysToHarvest; 
    }
    int Crop::getRegrow() const { 
      return regrow; 
    }
    int Crop::getDaysToRegrowth() const { 
      return daysToRegrowth; 
    }
    vector<tuple<string,int>> Crop::getSellValue() const { 
      return sellValue; 
    }
    vector<tuple<string,int>> Crop::getSeedPrice() const { 
      return seedPrice; 
    }
    vector<tuple<string, string, int>> Crop::getArtisanItems() const { 
      return artisanItems; 
    }

    // Setters
    void Crop::setSeason(string newseason) { 
      season = newseason; 
    }
    void Crop::setDaysToHarvest(int newdaysToHarvest) { 
      daysToHarvest = newdaysToHarvest; 
    }
    void Crop::setRegrow(bool newregrow) { 
      regrow = newregrow; 
    }
    void Crop::setDaysToRegrowth(int newdaysToRegrowth) { 
      daysToRegrowth = newdaysToRegrowth; 
    }
    void Crop::setSellValue(vector<tuple<string,int>> newsellValue) { 
      sellValue = newsellValue; 
    }
    void Crop::setSeedPrice(vector<tuple<string,int>> newseedPrice) { 
      seedPrice = newseedPrice; 
    }
    void Crop::setArtisanItems(vector<tuple<string, string, int>> newartisanItems) { 
      artisanItems = newartisanItems; 
    }

// Declaration of Villager's methods.
    // Constructor
    Villager::Villager(string currentname, string currenttype, bool currentsingle, string currentgiftLike, string currentgiftLove): DataType(currentname, currenttype) {
        single = currentsingle;
        giftLike = currentgiftLike;
        giftLove = currentgiftLove;
    }

    // Destructor
    Villager::~Villager() {};

    // Getters
    bool Villager::getSingle() const { 
        return single; 
    }
    string Villager::getGiftLike() const { 
        return giftLike; 
    }
    string Villager::getGiftLove() const { 
        return giftLove; 
    }

    // Setters
    void Villager::setSingle(bool newsingle) { 
        single = newsingle; 
    }
    void Villager::setGiftLike(string newgiftLike) { 
        giftLike = newgiftLike; 
    }
    void Villager::setGiftLove(string newgiftLove) { 
        giftLove = newgiftLove; 
    }

// Declaration of MyFarm's methods.
    // Constructor
    MyFarm::MyFarm(string currentfarmName, string currentfarmLayout) {
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
    void MyFarm::setFarmName(string newfarmName) {
        farmName = newfarmName;
    }
    void MyFarm::setFarmLayout(string newfarmLayout) {
        farmLayout = newfarmLayout;
    }   

int main() {
    Database db("database/gameData.db");

    vector<Crop> crops = db.getAllCrops();
    vector<Animal> animals = db.getAllAnimals();
    vector<Building> buildings = db.getAllBuildings();

    for (const auto& c : crops) {
        cout << c.getName() << " - " << c.getSeason() << endl;
    }

    return 0;
}