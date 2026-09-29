/*
*The class Villager sets the attributes and methods shared between the villager elements in the read-only library.
*Its parent class, DataType, defines the default attributes, name and type, and its getters and setters.
*/

#include <string>
#include <vector>
#include <utility>
#include "datatype.h"
using namespace std;

#ifndef VILLAGER
#define VILLAGER

class Villager : public DataType {
   private:
    bool single;
    string giftLike;
    string giftLove;

   public:
   // Constructor
    Villager(const string& currentname, 
            const string& currenttype, 
            bool currentsingle,
            const string& currentgiftLike, 
            const string& currentgiftLove);

    // Destructor
    virtual ~Villager();

    // Getters
    bool getSingle() const;
    string getGiftLike() const;
    string getGiftLove() const;

    // Setters
    void setGiftLike(const string& newgiftLike);
    void setGiftLove(const string& newgiftLove);
};

#endif