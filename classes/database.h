#include <external/sqlite3.h>
#include <string>
#include <vector>
#include <tuple>
#include "datatype.h"
#include "crop.h"
#include "animal.h"
#include "building.h"
using namespace std;

#ifndef DATABASE
#define DATABASE

class Database {
    private:
        sqlite3* db;

        // Auxiliares — buscam as tabelas filhas de cada entidade
        vector<tuple<string,int>> getCropSellValues(int cropId);
        vector<tuple<string,int>> getCropSeedSources(int cropId);
        vector<tuple<string,string,int>> getCropArtisanItems(int cropId);
        vector<tuple<string,string,int>> getAnimalArtisanItems(int animalId);
        vector<tuple<string,int>> getBuildingConstructionMaterials(int buildingId);
        vector<string> getBuildingAnimalTypes(int buildingId);

    public:
        Database(string path);
        ~Database();

        vector<Crop> getAllCrops();
        vector<Animal> getAllAnimals();
        vector<Building> getAllBuildings();
};

#endif