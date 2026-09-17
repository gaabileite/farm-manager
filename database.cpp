#include "classes/database.h"
#include <iostream>

// sqlite3_column_text returns NULL for NULL cells; building a std::string from NULL crashes.
static string columnText(sqlite3_stmt* stmt, int col) {
    const unsigned char* text = sqlite3_column_text(stmt, col);
    return text ? string(reinterpret_cast<const char*>(text)) : string();
}

Database::Database(string path) {
    int rc = sqlite3_open(path.c_str(), &db);
    if (rc) {
        cout << "Erro ao abrir banco: " << sqlite3_errmsg(db) << endl;
    }
}

Database::~Database() {
    sqlite3_close(db);
}

// ---------- CROP ----------

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

// ---------- MYFARM ----------
// Create:
int Database::createFarm(string farmName, string farmLayout) {
    string sql = "INSERT INTO my_farms (farm_name, farm_layout) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, farmName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, farmLayout.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return sqlite3_last_insert_rowid(db);   // devolve o id criado, pra usar em seguida
}

int Database::getOrCreateFarm(string farmName, string farmLayout) {
    string sql = "SELECT id FROM my_farms WHERE farm_name = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, farmName.c_str(), -1, SQLITE_TRANSIENT);

    int id = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (id == -1) {
        id = createFarm(farmName, farmLayout);
    }
    return id;
}

void Database::addAnimal(int farmId, string animalName, string animalType, int relationship) {
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

// Update:
void Database::updateAnimalRelationship(int animalId, int newRelationship) {
    string sql = "UPDATE my_animals SET animal_relationship = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, newRelationship);
    sqlite3_bind_int(stmt, 2, animalId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Delete:
void Database::removeAnimal(int animalId) {
    string sql = "DELETE FROM my_animals WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, animalId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

sqlite3* Database::getHandle() const {
    return db;
}