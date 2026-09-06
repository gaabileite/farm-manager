#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "animal.h"

//Constructor
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


