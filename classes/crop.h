#include <string>
#include <vector>
#include <utility>

using namespace std;

#ifndef CROP
#define CROP

#include "../datatype.h"

class Crop : public DataType {
   private:
    string season;
    int daysToHarvest;
    bool regrow;
    vector<int> sellValue;
    vector<int> seedPrice;
    vector<int> profit;
    vector<pair<string, string>> artisanItems;
    vector<string> seedShop;
   public:
    // Constructor
    Crop(string currentname, string currenttype, string currentseason, int currentdaysToHarvest, bool currentregrow, vector<int> currentsellValue, vector<int> currentseedPrice, vector<int> currentprofit, vector<pair<string, string>> currentartisanItems, vector<string> currentseedShop);

    // Destructor
    virtual ~Crop();

    // Getters
    string getSeason() const;
    int getDaysToHarvest() const;
    bool getRegrow() const;
    vector<int> getSellValue() const;
    vector<int> getSeedPrice() const;
    vector<int> getProfit() const;
    vector<pair<string, string>> getArtisanItems() const;
    vector<string> getSeedShop() const;

    // Setters
    void setSeason(string newseason);
    void setDaysToHarvest(int newdaysToHarvest);
    void setRegrow(bool newregrow);
    void setSellValue(vector<int> newsellValue);
    void setSeedPrice(vector<int> newseedPrice);
    void setProfit(vector<int> newprofit);
    void setArtisanItems(vector<pair<string, string>> newartisanItems);
    void setSeedShop(vector<string> newseedShop);
};

#endif