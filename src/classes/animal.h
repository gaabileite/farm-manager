/*
*The class Animal sets the attributes and methods shared between the animal elements in the read-only library.
*Its parent class, DataType, defines the default attributes, name and type, and its getters and setters.
*/

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include "datatype.h"
using namespace std;

#ifndef ANIMAL
#define ANIMAL

class Animal : public DataType {
   private:
      string produces;
      int daysToAdult;
      int buyPrice;
      vector<tuple<string, string, int>> artisanItem;

   public:
      // Constructor
      // strings, vectors and tuples by const reference
      // Avoids copying full lists from artisanItems for each new Animal object.
      Animal(const string& currentname, 
            const string& currenttype, 
            const string& currentproduces,
            int currentdaysToAdult, 
            int currentbuyPrice,
            const vector<tuple<string,string,int>>& currentartisanItem);

      // Destructor
      virtual ~Animal(); 

      // Getters
      string getProduces() const;
      int getDaysToAdult() const;
      int getBuyPrice() const;
      vector<tuple<string, string, int>> getArtisanItem() const;


      // Setters
      void setProduces(const string& newproduces);
      void setDaysToAdult(int newdaysToAdult);
      void setBuyPrice(int newbuyPrice);
      void setArtisanItem(const vector<tuple<string,string,int>>& newartisanItem);
};

#endif
