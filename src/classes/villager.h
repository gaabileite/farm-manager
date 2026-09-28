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
    Villager(string currentname, string currenttype, bool currentsingle, string currentgiftLike, string currentgiftLove);

    // Destructor
    virtual ~Villager();

    // Getters
    bool getSingle() const;
    string getGiftLike() const;
    string getGiftLove() const;

    // Setters
    void setSingle(bool newsingle);
    void setGiftLike(string newgiftLike);
    void setGiftLove(string newgiftLove);
};

#endif