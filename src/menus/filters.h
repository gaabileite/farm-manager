/*
*Declaração das funções que realizam busca e filtro da biblioteca estática do programa.
*Essas funções são definidas em filters.cpp e usadas em menu.cpp.
*/

#include <string>
#include <vector>
#include "../classes/crop.h"
#include "../classes/animal.h"
#include "../classes/building.h"
using namespace std;

#ifndef FILTERS
#define FILTERS

vector<Crop> filterCropsByName(const vector<Crop>& crops, string searchTerm);
vector<Crop> filterCropsBySeason(const vector<Crop>& crops, string season);
vector<Animal> filterAnimalsByName(const vector<Animal>& animals, string searchTerm);
vector<Building> filterBuildingsByName(const vector<Building>& buildings, string searchTerm);

#endif