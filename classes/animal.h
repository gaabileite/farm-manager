#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "datatype.h"
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
   vector<tuple<string, string, int>> artisanItem;

   public:

   // Constructor
   Animal(string currentname, string currenttype, string currentproduces, int currentdaysToAdult, int currentbuyPrice, vector<tuple<string, string, int>> currentartisanItem);

   // Destructor
   virtual ~Animal(); 

   // Getters
   string getProduces() const;
   int getDaysToAdult() const;
   int getBuyPrice() const;
   vector<tuple<string, string, int>> getArtisanItem() const;


   // Setters
   void setProduces(string newproduces);
   void setDaysToAdult(int newdaysToAdult);
   void setBuyPrice(int newbuyPrice);
   void setArtisanItem(vector<tuple<string, string, int>> newartisanItem);
};

#endif
