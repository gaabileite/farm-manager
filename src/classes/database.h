/*
 * database.h
 * Acesso ao SQLite e operações de leitura e alteração dos dados da fazenda.
 */

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

/*
 * Database: gerencia a conexão com o banco e as operações sobre os dados
 * do catálogo do jogo e da fazenda do jogador.
 */
class Database {
    private:
        sqlite3* db;

        // ---------- AUXILIARES ----------

        // Busca os valores de venda de uma plantação.
        vector<tuple<string,int>> getCropSellValues(int cropId);

        // Busca as fontes de sementes da plantação e seus preços.
        vector<tuple<string,int>> getCropSeedSources(int cropId);

        // Busca os itens artesanais derivados de uma plantação.
        vector<tuple<string,string,int>> getCropArtisanItems(int cropId);

        // Busca os itens artesanais produzidos por um animal.
        vector<tuple<string,string,int>> getAnimalArtisanItems(int animalId);

        // Busca os materiais necessários para uma construção.
        vector<tuple<string,int>> getBuildingConstructionMaterials(int buildingId);

        // Busca os tipos de animais que podem ser mantidos em uma construção.
        vector<string> getBuildingAnimalTypes(int buildingId);

    public:
        Database(const string& path);
        ~Database();

        // ---------- DATABASE ----------

        // Retorna a conexão SQLite utilizada pelo banco.
        sqlite3* getHandle() const;

        // ---------- CATÁLOGO ----------

        // Busca todas as plantações cadastradas no catálogo.
        vector<Crop> getAllCrops();

        // Busca todos os animais cadastrados no catálogo.
        vector<Animal> getAllAnimals();

        // Busca todas as construções cadastradas no catálogo.
        vector<Building> getAllBuildings();

        // Busca os nomes dos aldeões cadastrados no catálogo.
        vector<string> getAllVillagerNames();

        // ---------- MY FARM ----------

        // Cria uma nova fazenda com o nome e o layout informados.
        int createFarm(const string& farmName, const string& farmLayout);

        // Busca a fazenda pelo nome padrão; se não existir, cria uma nova.
        // Retorna o id da fazenda encontrada ou criada.
        int getOrCreateFarm(const string& defaultName, const string& defaultLayout);

        // Adiciona um animal à fazenda com o relacionamento informado.
        void addAnimal(int farmId, const string& animalName, const string& animalType, int relationship);

        // Atualiza o relacionamento de um animal existente.
        void updateAnimalRelationship(int animalId, int newRelationship);

        // Remove um animal da fazenda pelo id.
        void removeAnimal(int animalId);

        // Adiciona uma construção à fazenda com o nível informado.
        void addBuilding(int farmId, const string& buildingName, const string& buildingType, int level);

        // Atualiza o nível de uma construção.
        void upgradeBuilding(int buildingId);

        // Remove uma construção da fazenda pelo id.
        void removeBuilding(int buildingId);

        // ---------- MY RELATIONSHIPS ----------

        // Adiciona um relacionamento com um aldeão à fazenda.
        void addRelationship(int farmId, const string& villagerName, int friendship);

        // Atualiza o nível de amizade de um relacionamento existente.
        void updateFriendship(int relationshipId, int newFriendship);

        // Busca os relacionamentos cadastrados para a fazenda.
        vector<tuple<int,string,int>> getMyRelationships(int farmId);

        // ---------- FARM INFO ----------

        // Busca o nome e o layout associados à fazenda.
        tuple<string,string> getFarmInfo(int farmId);

        // Atualiza o nome da fazenda.
        void updateFarmName(int farmId, const string& newName);

        // Atualiza o layout da fazenda.
        void updateFarmLayout(int farmId, const string& newLayout);

        // Busca as construções cadastradas para a fazenda.
        vector<tuple<int,string,string,int>> getMyBuildings(int farmId);

        // Busca animais da fazenda pelo nome informado.
        vector<tuple<int,string,string,int>> findMyAnimalsByName(int farmId, const string& name);

        // Busca construções da fazenda pelo nome informado.
        vector<tuple<int,string,string,int>> findMyBuildingsByName(int farmId, const string& name);
};

#endif