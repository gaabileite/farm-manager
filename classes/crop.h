#include <string>
#include <vector>
#include <utility>
#include "datatype.h"
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
    int daysToRegrowth;
    vector<tuple<string, int>> sellValue;
    vector<tuple<string, int>> seedPrice;
    vector<tuple<string, string, int>> artisanItems;

   public:
    // Constructor
    Crop(string currentname, string currenttype, string currentseason, int currentdaysToHarvest, int currentregrow, int daysToRegrowth, vector<int> currentsellValue, vector<int> currentseedPrice, vector<tuple<string, string, int>> currentartisanItems);

    // Destructor
    virtual ~Crop();

    // Getters
    string getSeason() const;
    int getDaysToHarvest() const;
    int getRegrow() const;
    int getDaysToRegrowth() const;
    vector<int> getSellValue() const;
    vector<int> getSeedPrice() const;
    vector<tuple<string, string, int>> getArtisanItems() const;

    // Setters
    void setSeason(string newseason);
    void setDaysToHarvest(int newdaysToHarvest);
    void setRegrow(bool newregrow);
    void setDaysToRegrowth(int newdaysToRegrowth);
    void setSellValue(vector<int> newsellValue);
    void setSeedPrice(vector<int> newseedPrice);
    void setArtisanItems(vector<tuple<string, string, int>> newartisanItems);
};

#endif