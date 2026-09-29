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
        // strings, vectors and tuples by const reference
        // Avoids copying full lists from sellValue, seedPrice and artisanItems for each new Crop object.
        Crop(const string& currentname, 
            const string& currenttype, 
            const string& currentseason,
            int currentdaysToHarvest, 
            int currentregrow, 
            int daysToRegrowth,
            const vector<tuple<string,int>>& currentsellValue,
            const vector<tuple<string,int>>& currentseedPrice,
            const vector<tuple<string,string,int>>& currentartisanItems);

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
        void setSeason(const string& newseason);
        void setDaysToHarvest(int newdaysToHarvest);
        void setRegrow(int newregrow);
        void setDaysToRegrowth(int newdaysToRegrowth);
        void setSellValue(const vector<tuple<string,int>>& newsellValue);
        void setSeedPrice(const vector<tuple<string,int>>& newseedPrice);
        void setArtisanItems(const vector<tuple<string,string,int>>& newartisanItems);
};

#endif