#include "classes/database.h"
#include <iostream>

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
        string quality = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
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
        string shop = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
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
        string item = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string machine = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
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
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string season = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
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
        string item = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string machine = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
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
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string produces = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
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
        string material = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
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
        result.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
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
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int width = sqlite3_column_int(stmt, 3);
        int height = sqlite3_column_int(stmt, 4);
        string whereToGet = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
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