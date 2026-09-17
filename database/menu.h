#include <vector>
#include "../classes/crop.h"
#include "../classes/animal.h"
#include "../classes/building.h"
using namespace std;

#ifndef MENU
#define MENU

void showCropMenu(const vector<Crop>& crops);
void showAnimalMenu(const vector<Animal>& animals);
void showBuildingMenu(const vector<Building>& buildings);
void showMyFarmMenu(Database& db, int farmId);

#endif