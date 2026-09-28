/*
*The class Crop sets the attributes and methods shared between the crop elements in the read-only library.
*Its parent class, DataType, defines the default attributes, name and type, and its getters and setters.
*/

#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include "datatype.h"
using namespace std;

#ifndef CROP
#define CROP

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
    Crop(string currentname, string currenttype, string currentseason, int currentdaysToHarvest, int currentregrow, int daysToRegrowth, vector<tuple<string,int>> currentsellValue, vector<tuple<string, int>> currentseedPrice, vector<tuple<string, string, int>> currentartisanItems);

    // Destructor
    virtual ~Crop();

    // Getters
    string getSeason() const;
    int getDaysToHarvest() const;
    int getRegrow() const;
    int getDaysToRegrowth() const;
    vector<tuple<string,int>> getSellValue() const;
    vector<tuple<string,int>> getSeedPrice() const;
    vector<tuple<string, string, int>> getArtisanItems() const;

    // Setters
    void setSeason(string newseason);
    void setDaysToHarvest(int newdaysToHarvest);
    void setRegrow(int newregrow);
    void setDaysToRegrowth(int newdaysToRegrowth);
    void setSellValue(vector<tuple<string,int>> newsellValue);
    void setSeedPrice(vector<tuple<string,int>> newseedPrice);
    void setArtisanItems(vector<tuple<string, string, int>> newartisanItems);
};

#endif