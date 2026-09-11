#include <vector>
#include "crop.h"
#include "animal.h"
#include "building.h"
using namespace std;

#ifndef MENU
#define MENU

void showCropMenu(const vector<Crop>& crops);
void showAnimalMenu(const vector<Animal>& animals);
void showBuildingMenu(const vector<Building>& buildings);

#endif