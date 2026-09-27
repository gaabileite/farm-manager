#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include "menus/filters.h"
#include "menus/menu.h"

int main() {
    // Banco estático (somente leitura)
    Database gameDb("data/gameData.db");

    vector<Crop> crops = gameDb.getAllCrops();
    vector<Animal> animals = gameDb.getAllAnimals();
    vector<Building> buildings = gameDb.getAllBuildings();

    // Player's personal database (game progress)
    Database playerDb("data/myFarmData.db");
    int farmId = playerDb.getOrCreateFarm("My Farm", "Default");

    // Main menu
    while (true) {
        cout << "\n=== Farm Manager ===\n";
        cout << "1. Crops\n2. Animals\n3. Buildings\n4. My Farm\n0. Exit\n> ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) showCropMenu(crops);
        else if (choice == 2) showAnimalMenu(animals);
        else if (choice == 3) showBuildingMenu(buildings);
        else if (choice == 4) showMyFarmMenu(playerDb, farmId, buildings);
    }
    return 0;
}