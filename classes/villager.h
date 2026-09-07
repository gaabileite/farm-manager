#include <string>
#include <vector>
#include <utility>

using namespace std;

#ifndef VILLAGER
#define VILLAGER

#include "../datatype.h"

class Villager : public DataType {
   private:
    bool single;
    vector<pair<string, string>> routine;
    vector<string> giftsLike;
    vector<string> giftsLove;
    vector<string> giftsHate;
    vector<string> giftsNeutral;
   public:
    // Constructor
    Villager(string currentname, string currenttype, bool currentsingle, vector<pair<string, string>> currentroutine, vector<string> currentgiftsLike, vector<string> currentgiftsLove, vector<string> currentgiftsHate, vector<string> currentgiftsNeutral);

    // Destructor
    virtual ~Villager();

    // Getters
    bool getSingle() const;
    vector<pair<string, string>> getRoutine() const;
    vector<string> getGiftsLike() const;
    vector<string> getGiftsLove() const;
    vector<string> getGiftsHate() const;
    vector<string> getGiftsNeutral() const;

    // Setters
    void setSingle(bool newsingle);
    void setRoutine(vector<pair<string, string>> newroutine);
    void setGiftsLike(vector<string> newgiftsLike);
    void setGiftsLove(vector<string> newgiftsLove);
    void setGiftsHate(vector<string> newgiftsHate);
    void setGiftsNeutral(vector<string> newgiftsNeutral);
};

#endif