#include "../../external/sqlite3.h"
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
        Database(const string& path);
        ~Database();

        sqlite3* getHandle() const;

        vector<Crop> getAllCrops();
        vector<Animal> getAllAnimals();
        vector<Building> getAllBuildings();
        vector<string> getAllVillagerNames();

        int createFarm(const string& farmName, const string& farmLayout);
        int getOrCreateFarm(const string& defaultName, const string& defaultLayout);
        void addAnimal(int farmId, const string& animalName, const string& animalType, int relationship);
        void updateAnimalRelationship(int animalId, int newRelationship);
        void removeAnimal(int animalId);

        void addBuilding(int farmId, const string& buildingName, const string& buildingType, int level);
        void upgradeBuilding(int buildingId);
        void removeBuilding(int buildingId);

        void addRelationship(int farmId, const string& villagerName, int friendship);
        void updateFriendship(int relationshipId, int newFriendship);
        vector<tuple<int,string,int>> getMyRelationships(int farmId);

        tuple<string,string> getFarmInfo(int farmId);
        void updateFarmName(int farmId, const string& newName);
        void updateFarmLayout(int farmId, const string& newLayout);

        vector<tuple<int,string,string,int>> getMyBuildings(int farmId);

        vector<tuple<int,string,string,int>> findMyAnimalsByName(int farmId, const string& name);
        vector<tuple<int,string,string,int>> findMyBuildingsByName(int farmId, const string& name);
};

#endif
