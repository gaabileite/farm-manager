/*
 * database.cpp
 * Implementação das operações de leitura e alteração dos dados no SQLite.
 */

#include "classes/database.h"
#include <iostream>

// Trata campos NULL do SQLite antes de convertê-los para string.
static string columnText(sqlite3_stmt* stmt, int col) {
    const unsigned char* text = sqlite3_column_text(stmt, col);
    return text ? string(reinterpret_cast<const char*>(text)) : string();
}


// ---------- DATABASE ----------

// Abre a conexão com o banco usando o caminho informado.
Database::Database(const string& path) {
    int rc = sqlite3_open(path.c_str(), &db);
    if (rc) {
        cout << "Erro ao abrir banco: " << sqlite3_errmsg(db) << endl;
    }
}

// Fecha a conexão com o banco ao destruir o objeto.
Database::~Database() {
    sqlite3_close(db);
}


// ---------- CROP ----------

// Busca os valores de venda de uma plantação por qualidade.
vector<tuple<string,int>> Database::getCropSellValues(int cropId) {
    vector<tuple<string,int>> result;
    string sql = "SELECT quality, value FROM crop_sell_values WHERE crop_id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, cropId);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string quality = columnText(stmt, 0);
        int value = sqlite3_column_int(stmt, 1);
        result.push_back(make_tuple(quality, value));
    }
    sqlite3_finalize(stmt);
    return result;
}

// Busca as fontes de sementes da plantação e seus preços.
vector<tuple<string,int>> Database::getCropSeedSources(int cropId) {
    vector<tuple<string,int>> result;
    string sql = "SELECT shop_name, price FROM crop_seed_sources WHERE crop_id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, cropId);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string shop = columnText(stmt, 0);
        int price = sqlite3_column_int(stmt, 1);
        result.push_back(make_tuple(shop, price));
    }
    sqlite3_finalize(stmt);
    return result;
}

// Busca os itens artesanais derivados de uma plantação.
vector<tuple<string,string,int>> Database::getCropArtisanItems(int cropId) {
    vector<tuple<string,string,int>> result;
    string sql = "SELECT item_name, machine, value FROM crop_artisan_items WHERE crop_id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, cropId);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string item = columnText(stmt, 0);
        string machine = columnText(stmt, 1);
        int value = sqlite3_column_int(stmt, 2);
        result.push_back(make_tuple(item, machine, value));
    }
    sqlite3_finalize(stmt);
    return result;
}

// Busca todas as plantações do catálogo e seus dados relacionados.
vector<Crop> Database::getAllCrops() {
    vector<Crop> crops;
    string sql =
        "SELECT d.id, d.name, d.type, c.season, c.daysToHarvest, c.regrow, c.regrowDays "
        "FROM datatype d JOIN crop c ON c.id = d.id;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string name = columnText(stmt, 1);
        string type = columnText(stmt, 2);
        string season = columnText(stmt, 3);
        int daysToHarvest = sqlite3_column_int(stmt, 4);
        int regrow = sqlite3_column_int(stmt, 5);
        int regrowDays = sqlite3_column_int(stmt, 6);

        auto sellValues = getCropSellValues(id);
        auto seedSources = getCropSeedSources(id);
        auto artisanItems = getCropArtisanItems(id);

        crops.push_back(Crop(name, type, season, daysToHarvest, regrow, regrowDays,
                              sellValues, seedSources, artisanItems));
    }

    sqlite3_finalize(stmt);
    return crops;
}


// ---------- ANIMAL ----------

// Busca os itens artesanais produzidos por um animal.
vector<tuple<string,string,int>> Database::getAnimalArtisanItems(int animalId) {
    vector<tuple<string,string,int>> result;
    string sql = "SELECT item_name, machine, value FROM animal_artisan_items WHERE animal_id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, animalId);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string item = columnText(stmt, 0);
        string machine = columnText(stmt, 1);
        int value = sqlite3_column_int(stmt, 2);
        result.push_back(make_tuple(item, machine, value));
    }
    sqlite3_finalize(stmt);
    return result;
}

// Busca todos os animais do catálogo e seus itens artesanais.
vector<Animal> Database::getAllAnimals() {
    vector<Animal> animals;
    string sql =
        "SELECT d.id, d.name, d.type, a.produces, a.daysToAdult, a.buyPrice "
        "FROM datatype d JOIN animal a ON a.id = d.id;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string name = columnText(stmt, 1);
        string type = columnText(stmt, 2);
        string produces = columnText(stmt, 3);
        int daysToAdult = sqlite3_column_int(stmt, 4);
        int buyPrice = sqlite3_column_int(stmt, 5);

        auto artisanItems = getAnimalArtisanItems(id);

        animals.push_back(Animal(name, type, produces, daysToAdult, buyPrice, artisanItems));
    }

    sqlite3_finalize(stmt);
    return animals;
}


// ---------- BUILDING ----------

// Busca os materiais necessários para construir uma construção.
vector<tuple<string,int>> Database::getBuildingConstructionMaterials(int buildingId) {
    vector<tuple<string,int>> result;
    string sql = "SELECT material_name, material_amount FROM building_construction_materials WHERE building_id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, buildingId);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string material = columnText(stmt, 0);
        int amount = sqlite3_column_int(stmt, 1);
        result.push_back(make_tuple(material, amount));
    }
    sqlite3_finalize(stmt);
    return result;
}

// Busca os tipos de animais que podem ser mantidos em uma construção.
vector<string> Database::getBuildingAnimalTypes(int buildingId) {
    vector<string> result;
    string sql = "SELECT animal_type FROM building_animal_types WHERE building_id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, buildingId);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        result.push_back(columnText(stmt, 0));
    }
    sqlite3_finalize(stmt);
    return result;
}

// Busca todas as construções do catálogo e seus dados relacionados.
vector<Building> Database::getAllBuildings() {
    vector<Building> buildings;
    string sql =
        "SELECT d.id, d.name, d.type, b.size_width, b.size_height, b.whereToGet, "
        "b.housesAnimals, b.animalAmount "
        "FROM datatype d JOIN building b ON b.id = d.id;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string name = columnText(stmt, 1);
        string type = columnText(stmt, 2);
        int width = sqlite3_column_int(stmt, 3);
        int height = sqlite3_column_int(stmt, 4);
        string whereToGet = columnText(stmt, 5);
        bool housesAnimals = sqlite3_column_int(stmt, 6) != 0;
        int animalAmount = sqlite3_column_int(stmt, 7);

        auto materials = getBuildingConstructionMaterials(id);
        tuple<int,int> size = make_tuple(width, height);

        if (housesAnimals) {
            auto animalTypes = getBuildingAnimalTypes(id);
            buildings.push_back(Building(name, type, materials, size, whereToGet, animalTypes, animalAmount));
        } else {
            buildings.push_back(Building(name, type, materials, size, whereToGet));
        }
    }

    sqlite3_finalize(stmt);
    return buildings;
}

// Busca apenas os nomes dos aldeões para validar o nome informado no menu de relacionamentos.
vector<string> Database::getAllVillagerNames() {
    vector<string> names;
    string sql = "SELECT d.name FROM datatype d JOIN villager v ON v.id = d.id ORDER BY d.id;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        names.push_back(columnText(stmt, 0));
    }
    sqlite3_finalize(stmt);
    return names;
}


// ---------- MYFARM ----------

// Cria uma nova fazenda e retorna seu id para identificar os dados relacionados.
int Database::createFarm(const string& farmName, const string& farmLayout) {
    string sql = "INSERT INTO my_farms (farm_name, farm_layout) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, farmName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, farmLayout.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return sqlite3_last_insert_rowid(db);   // devolve o id criado, pra usar em seguida
}

// Busca a fazenda já salva; se nenhuma existir, cria uma com os dados padrão.
// Usa a primeira fazenda cadastrada para manter a mesma fazenda entre as partes do projeto.
int Database::getOrCreateFarm(const string& defaultName, const string& defaultLayout) {
    string sql = "SELECT id FROM my_farms ORDER BY id LIMIT 1;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    int id = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    if (id == -1) {
        id = createFarm(defaultName, defaultLayout);
    }

    return id;
}

// Adiciona um animal à fazenda com o relacionamento informado.
void Database::addAnimal(int farmId, const string& animalName, const string& animalType, int relationship) {
    string sql = "INSERT INTO my_animals (farm_id, animal_name, animal_type, animal_relationship) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, farmId);
    sqlite3_bind_text(stmt, 2, animalName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, animalType.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, relationship);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Atualiza o nível de relacionamento de um animal existente.
void Database::updateAnimalRelationship(int animalId, int newRelationship) {
    string sql = "UPDATE my_animals SET animal_relationship = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, newRelationship);
    sqlite3_bind_int(stmt, 2, animalId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Remove um animal da fazenda pelo id.
void Database::removeAnimal(int animalId) {
    string sql = "DELETE FROM my_animals WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, animalId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Retorna a conexão SQLite utilizada pelo banco.
sqlite3* Database::getHandle() const {
    return db;
}


// ---------- MY BUILDINGS ----------

// Adiciona uma construção à fazenda com o nível informado.
void Database::addBuilding(int farmId, const string& buildingName, const string& buildingType, int level) {
    string sql = "INSERT INTO my_buildings (farm_id, building_name, building_type, building_level) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, farmId);
    sqlite3_bind_text(stmt, 2, buildingName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, buildingType.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, level);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Aumenta em um o nível da construção indicada.
void Database::upgradeBuilding(int buildingId) {
    string sql = "UPDATE my_buildings SET building_level = building_level + 1 WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, buildingId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Remove uma construção da fazenda pelo id.
void Database::removeBuilding(int buildingId) {
    string sql = "DELETE FROM my_buildings WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, buildingId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Busca as construções cadastradas para a fazenda.
vector<tuple<int,string,string,int>> Database::getMyBuildings(int farmId) {
    vector<tuple<int,string,string,int>> result;
    string sql = "SELECT id, building_name, building_type, building_level FROM my_buildings WHERE farm_id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, farmId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int level = sqlite3_column_int(stmt, 3);
        result.push_back(make_tuple(id, name, type, level));
    }

    sqlite3_finalize(stmt);
    return result;
}


// ---------- MY RELATIONSHIPS ----------

// Adiciona um relacionamento com um aldeão à fazenda.
void Database::addRelationship(int farmId, const string& villagerName, int friendship) {
    string sql = "INSERT INTO my_relationships (farm_id, villager_name, friendship) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, farmId);
    sqlite3_bind_text(stmt, 2, villagerName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, friendship);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Atualiza o nível de amizade de um relacionamento existente.
void Database::updateFriendship(int relationshipId, int newFriendship) {
    string sql = "UPDATE my_relationships SET friendship = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, newFriendship);
    sqlite3_bind_int(stmt, 2, relationshipId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Busca os relacionamentos cadastrados para a fazenda.
vector<tuple<int,string,int>> Database::getMyRelationships(int farmId) {
    vector<tuple<int,string,int>> result;
    string sql = "SELECT id, villager_name, friendship FROM my_relationships WHERE farm_id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, farmId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int friendship = sqlite3_column_int(stmt, 2);
        result.push_back(make_tuple(id, name, friendship));
    }

    sqlite3_finalize(stmt);
    return result;
}


// ---------- MYFARM INFO ----------

// Busca o nome e o layout associados à fazenda.
tuple<string,string> Database::getFarmInfo(int farmId) {
    string sql = "SELECT farm_name, farm_layout FROM my_farms WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, farmId);

    string name, layout;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const unsigned char* layoutText = sqlite3_column_text(stmt, 1);
        layout = layoutText ? reinterpret_cast<const char*>(layoutText) : "";
    }

    sqlite3_finalize(stmt);
    return make_tuple(name, layout);
}

// Atualiza o nome da fazenda.
void Database::updateFarmName(int farmId, const string& newName) {
    string sql = "UPDATE my_farms SET farm_name = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, newName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, farmId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Atualiza o layout da fazenda.
void Database::updateFarmLayout(int farmId, const string& newLayout) {
    string sql = "UPDATE my_farms SET farm_layout = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, newLayout.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, farmId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Busca animais da fazenda pelo nome, ignorando diferenças entre maiúsculas e minúsculas.
vector<tuple<int,string,string,int>> Database::findMyAnimalsByName(int farmId, const string& name) {
    vector<tuple<int,string,string,int>> result;
    string sql = "SELECT id, animal_name, animal_type, animal_relationship "
                 "FROM my_animals WHERE farm_id = ? AND LOWER(animal_name) = LOWER(?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, farmId);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string n = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int rel = sqlite3_column_int(stmt, 3);
        result.push_back(make_tuple(id, n, type, rel));
    }

    sqlite3_finalize(stmt);
    return result;
}

// Busca construções da fazenda pelo nome, ignorando diferenças entre maiúsculas e minúsculas.
vector<tuple<int,string,string,int>> Database::findMyBuildingsByName(int farmId, const string& name) {
    vector<tuple<int,string,string,int>> result;
    string sql = "SELECT id, building_name, building_type, building_level "
                 "FROM my_buildings WHERE farm_id = ? AND LOWER(building_name) = LOWER(?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, farmId);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string n = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int level = sqlite3_column_int(stmt, 3);
        result.push_back(make_tuple(id, n, type, level));
    }

    sqlite3_finalize(stmt);
    return result;
}