#include <string>
#include <vector>
#include <utility>
#include "../datatype.h"
using namespace std;

#ifndef VILLAGER
#define VILLAGER

/*
The Villager class adds villagers from the game, specifying attributes for only the important information about each character.
*/

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