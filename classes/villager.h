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
    vector<string> giftsLike;
    vector<string> giftsLove;
    vector<string> giftsHate;
    vector<string> giftsNeutral;
   public:
    // Constructor
    Villager(string currentname, string currenttype, bool currentsingle, vector<string> currentgiftsLike, vector<string> currentgiftsLove, vector<string> currentgiftsHate, vector<string> currentgiftsNeutral);

    // Destructor
    virtual ~Villager();

    // Getters
    bool getSingle() const;
    vector<string> getGiftsLike() const;
    vector<string> getGiftsLove() const;
    vector<string> getGiftsHate() const;
    vector<string> getGiftsNeutral() const;

    // Setters
    void setSingle(bool newsingle);
    void setGiftsLike(vector<string> newgiftsLike);
    void setGiftsLove(vector<string> newgiftsLove);
    void setGiftsHate(vector<string> newgiftsHate);
    void setGiftsNeutral(vector<string> newgiftsNeutral);
};

#endif