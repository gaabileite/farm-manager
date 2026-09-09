#include <string>
#include <vector>
#include <utility>
#include "../datatype.h"
using namespace std;

#ifndef CROP
#define CROP

/*
The Crop class adds crops from the game, with many attributes that specify information about each crop.
*/

class Crop : public DataType {
   private:
    string season;
    int daysToHarvest;
    int regrow;
    int daysToRegrowth
    vector<pair<string, int>> sellValue;
    vector<pair<string, int>> seedPrice;
    vector<pair<string, string, int>> artisanItems;

   public:
    // Constructor
    Crop(string currentname, string currenttype, string currentseason, int currentdaysToHarvest, int currentregrow, int daysToRegrowth, vector<int> currentsellValue, vector<int> currentseedPrice, vector<pair<string, string>> currentartisanItems, vector<string> currentseedShop);

    // Destructor
    virtual ~Crop();

    // Getters
    string getSeason() const;
    int getDaysToHarvest() const;
    int getRegrow() const;
    int getDaysToRegrowth() const;
    vector<int> getSellValue() const;
    vector<int> getSeedPrice() const;
    vector<pair<string, string>> getArtisanItems() const;
    vector<string> getSeedShop() const;

    // Setters
    void setSeason(string newseason);
    void setDaysToHarvest(int newdaysToHarvest);
    void setRegrow(bool newregrow);
    void setDaysToRegrowth(int newdaysToRegrowth);
    void setSellValue(vector<int> newsellValue);
    void setSeedPrice(vector<int> newseedPrice);
    void setArtisanItems(vector<pair<string, string>> newartisanItems);
    void setSeedShop(vector<string> newseedShop);
};

#endif