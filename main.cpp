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
    Animal::Animal(string currentname, string currenttype, string currentproduces, int currentdaysToAdult, int currentbuyPrice, int currentsellValue, vector<pair<string, string>> currentartisanItem): DataType(currentname, currenttype) {
        produces = currentproduces;
        daysToAdult = currentdaysToAdult;
        buyPrice = currentbuyPrice;
        sellValue = currentsellValue;
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
    int Animal::getSellValue() const {
        return sellValue;
    }
    vector<pair<string, string>> Animal::getArtisanItem() const {
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
    void Animal::setSellValue(int newsellValue) {
        sellValue = newsellValue;
    }
    void Animal::setArtisanItem(vector<pair<string, string>> newartisanItem) {
        artisanItem = newartisanItem;
    }

// Declaration of Building's methods.
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

    // Destructor
    Building::~Building() {};

    // Getters
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

    // Setters
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

// Declaration of Crop's methods.
    // Constructor
    Crop::Crop(string currentname, string currenttype, string currentseason, int currentdaysToHarvest, bool currentregrow, vector<int> currentsellValue, vector<int> currentseedPrice, vector<int> currentprofit, vector<pair<string, string>> currentartisanItems, vector<string> currentseedShop): DataType(currentname, currenttype) {
        season = currentseason;
        daysToHarvest = currentdaysToHarvest;
        regrow = currentregrow;
        sellValue = currentsellValue;
        seedPrice = currentseedPrice;
        profit = currentprofit;
        artisanItems = currentartisanItems;
        seedShop = currentseedShop;
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
    bool Crop::getRegrow() const { 
        return regrow; 
    }
    vector<int> Crop::getSellValue() const { 
        return sellValue; 
    }
    vector<int> Crop::getSeedPrice() const { 
        return seedPrice; 
    }
    vector<int> Crop::getProfit() const { 
        return profit; 
    }
    vector<pair<string, string>> Crop::getArtisanItems() const { 
        return artisanItems; 
    }
    vector<string> Crop::getSeedShop() const { 
        return seedShop; 
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
    void Crop::setSellValue(vector<int> newsellValue) { 
        sellValue = newsellValue; 
    }
    void Crop::setSeedPrice(vector<int> newseedPrice) { 
        seedPrice = newseedPrice; 
    }
    void Crop::setProfit(vector<int> newprofit) { 
        profit = newprofit; 
    }
    void Crop::setArtisanItems(vector<pair<string, string>> newartisanItems) { 
        artisanItems = newartisanItems; 
    }
    void Crop::setSeedShop(vector<string> newseedShop) { 
        seedShop = newseedShop; 
    }

// Declaration of Villager's methods.
    // Constructor
    Villager::Villager(string currentname, string currenttype, bool currentsingle, vector<string> currentgiftsLike, vector<string> currentgiftsLove, vector<string> currentgiftsHate, vector<string> currentgiftsNeutral): DataType(currentname, currenttype) {
        single = currentsingle;
        routine = currentroutine;
        giftsLike = currentgiftsLike;
        giftsLove = currentgiftsLove;
        giftsHate = currentgiftsHate;
        giftsNeutral = currentgiftsNeutral;
    }

    // Destructor
    Villager::~Villager() {};

    // Getters
    bool Villager::getSingle() const { 
        return single; 
    }
    vector<string> Villager::getGiftsLike() const { 
        return giftsLike; 
    }
    vector<string> Villager::getGiftsLove() const { 
        return giftsLove; 
    }
    vector<string> Villager::getGiftsHate() const { 
        return giftsHate; 
    }
    vector<string> Villager::getGiftsNeutral() const { 
        return giftsNeutral; 
    }

    // Setters
    void Villager::setSingle(bool newsingle) { 
        single = newsingle; 
    }
    void Villager::setGiftsLike(vector<string> newgiftsLike) { 
        giftsLike = newgiftsLike; 
    }
    void Villager::setGiftsLove(vector<string> newgiftsLove) { 
        giftsLove = newgiftsLove; 
    }
    void Villager::setGiftsHate(vector<string> newgiftsHate) { 
        giftsHate = newgiftsHate; 
    }
    void Villager::setGiftsNeutral(vector<string> newgiftsNeutral) { 
        giftsNeutral = newgiftsNeutral; 
    }