#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include "menus/filters.h"
#include "menus/menu.h"

// Searches crops, animals, and buildings by name at once, through a pointer
// to the base class (DataType) — one vector, different types, all reached
// through the shared interface (getName/getType).
void searchEverything(const vector<DataType*>& allEntities, const string& term) {
    for (DataType* entity : allEntities) {
        if (entity->getName().find(term) != string::npos) {
            cout << entity->getName() << " (" << entity->getType() << ")\n";
        }
    }
}

int main() {
    // Static database (read-only)
    Database gameDb("data/gameData.db");

    vector<Crop> crops = gameDb.getAllCrops();
    vector<Animal> animals = gameDb.getAllAnimals();
    vector<Building> buildings = gameDb.getAllBuildings();
    vector<string> villagerNames = gameDb.getAllVillagerNames();

    // Pointers to the already-loaded elements — valid as long as crops/animals/buildings
    // aren't reallocated, which doesn't happen after the initial load.
    vector<DataType*> allEntities;
    for (auto& c : crops) allEntities.push_back(&c);
    for (auto& a : animals) allEntities.push_back(&a);
    for (auto& b : buildings) allEntities.push_back(&b);

    // Player's personal database (game progress)
    Database playerDb("data/myFarmData.db");
    int farmId = playerDb.getOrCreateFarm("My Farm", "Default");

    // Main menu
    while (true) {
        cout << "\n=== Farm Manager ===\n";
        cout << "1. Crops\n2. Animals\n3. Buildings\n4. My Farm\n5. Search everything\n0. Exit\n> ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) showCropMenu(crops);
        else if (choice == 2) showAnimalMenu(animals);
        else if (choice == 3) showBuildingMenu(buildings);
        else if (choice == 4) showMyFarmMenu(playerDb, farmId, buildings, villagerNames);
        else if (choice == 5) {
            cin.ignore();
            string term;
            cout << "Search: ";
            getline(cin, term);
            searchEverything(allEntities, term);
        }
    }
    return 0;
}