#include "../external/sqlite3.h"
#include <string>
#include <vector>
#include <tuple>
#include "external/sqlite3.h"
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

        int createFarm(string farmName, string farmLayout);   // retorna o id criado
        void addAnimal(int farmId, string animalName, string animalType, int relationship);
        void updateAnimalRelationship(int animalId, int newRelationship);
        void removeAnimal(int animalId);

        void addBuilding(int farmId, string buildingName, string buildingType, int level);
        void upgradeBuilding(int buildingId);
        void removeBuilding(int buildingId);

        void addRelationship(int farmId, string villagerName, int friendship);
        void updateFriendship(int relationshipId, int newFriendship);
};

#endif
