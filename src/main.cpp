#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include "menus/filters.h"
#include "menus/menu.h"

/*
 * main.cpp
 * Inicializa os bancos de dados e controla o menu principal do jogo.
 */

// Busca plantações, animais e construções pelo nome usando a interface comum de DataType.
void searchEverything(const vector<DataType*>& allEntities, const string& term) {
    for (DataType* entity : allEntities) {
        if (entity->getName().find(term) != string::npos) {
            cout << entity->getName() << " (" << entity->getType() << ")\n";
        }
    }
}

int main() {
    // Banco estático: contém apenas os dados do catálogo do jogo.
    Database gameDb("data/gameData.db");

    vector<Crop> crops = gameDb.getAllCrops();
    vector<Animal> animals = gameDb.getAllAnimals();
    vector<Building> buildings = gameDb.getAllBuildings();
    vector<string> villagerNames = gameDb.getAllVillagerNames();

    // Guarda ponteiros para os elementos já carregados no catálogo.
    // Eles permanecem válidos enquanto os vetores não forem realocados.
    vector<DataType*> allEntities;
    for (auto& c : crops) allEntities.push_back(&c);
    for (auto& a : animals) allEntities.push_back(&a);
    for (auto& b : buildings) allEntities.push_back(&b);

    // Banco da fazenda: guarda o progresso e os dados personalizados do jogador.
    Database playerDb("data/myFarmData.db");
    int farmId = playerDb.getOrCreateFarm("My Farm", "Default");

    // ---------- MENU PRINCIPAL ----------

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
            // Limpa o '\n' deixado pelo cin antes de usar getline.
            cin.ignore();
            string term;
            cout << "Search: ";
            getline(cin, term);
            searchEverything(allEntities, term);
        }
    }
    return 0;
}