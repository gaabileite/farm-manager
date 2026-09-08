#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "../datatype.h"
using namespace std;

#ifndef ANIMAL
#define ANIMAL

/*
The Animal class is a derived class from DataType and inherits its key attributes.
 */

class Animal : public DataType

{
   private:
   string produces;
   int daysToAdult;
   int buyPrice;
   int sellValue;
   vector<pair<string, string, int>> artisanItem;

   public:

   // Constructor
   Animal(string currentname, string currenttype, string currentproduces, int currentdaysToAdult, int currentbuyPrice, int currentsellValue, vector<pair<string, string>> currentartisanItem);

   // Destructor
   virtual ~Animal(); 

   // Getters
   string getProduces() const;
   int getDaysToAdult() const;
   int getBuyPrice() const;
   int getSellValue() const;
   vector<pair<string, string>> getArtisanItem() const;


   // Setters
   void setProduces(string newproduces);
   void setDaysToAdult(int newdaysToAdult);
   void setBuyPrice(int newbuyPrice);
   void setSellValue(int newsellValue);
   void setArtisanItem(vector<pair<string, string>> newartisanItem);
};

#endif
