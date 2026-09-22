#include <vector>
#include "../classes/crop.h"
#include "../classes/animal.h"
#include "../classes/building.h"
#include "../classes/database.h"
using namespace std;

#ifndef MENU
#define MENU

void showCropMenu(const vector<Crop>& crops);
void showAnimalMenu(const vector<Animal>& animals);
void showBuildingMenu(const vector<Building>& buildings);

void showMyFarmMenu(Database& db, int farmId, const vector<Building>& buildings);
void showFarmInfoMenu(Database& db, int farmId);
void showMyAnimalsMenu(Database& db, int farmId);
void showMyRelationshipsMenu(Database& db, int farmId);
void showMyBuildingsMenu(Database& db, int farmId, const vector<Building>& possibleBuildings);

int resolveAnimalId(Database& db, int farmId);
int resolveBuildingId(Database& db, int farmId);

#endif