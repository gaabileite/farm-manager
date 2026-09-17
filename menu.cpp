#include "database/menu.h"
#include "database/filters.h"
#include <iostream>

void showCropMenu(const vector<Crop>& crops) {
    while (true) {
        cout << "\n--- Crops ---\n";
        cout << "1. Buscar por nome\n2. Filtrar por estacao\n3. Listar todos\n0. Voltar\n> ";
        int choice;
        cin >> choice;
        if (choice == 0) break;

        vector<Crop> results;
        if (choice == 1) {
            cin.ignore();
            string term;
            cout << "Nome: ";
            getline(cin, term);
            results = filterCropsByName(crops, term);
        } else if (choice == 2) {
            string season;
            cout << "Estacao: ";
            cin >> season;
            results = filterCropsBySeason(crops, season);
        } else {
            results = crops;
        }

        if (results.empty()) cout << "Nenhum resultado encontrado.\n";
        for (const auto& c : results) {
            cout << c.getName() << " - " << c.getSeason() << " - " << c.getDaysToHarvest() << " dias\n";
        }
    }
}

void showAnimalMenu(const vector<Animal>& animals) {
    while (true) {
        cout << "\n--- Animals ---\n";
        cout << "1. Buscar por nome\n2. Listar todos\n0. Voltar\n> ";
        int choice;
        cin >> choice;
        if (choice == 0) break;

        vector<Animal> results;
        if (choice == 1) {
            cin.ignore();
            string term;
            cout << "Nome: ";
            getline(cin, term);
            results = filterAnimalsByName(animals, term);
        } else {
            results = animals;
        }

        if (results.empty()) cout << "Nenhum resultado encontrado.\n";
        for (const auto& a : results) {
            cout << a.getName() << " - produz " << a.getProduces()
                 << " - " << a.getDaysToAdult() << " dias ate adulto"
                 << " - " << a.getBuyPrice() << "g\n";
        }
    }
}

void showBuildingMenu(const vector<Building>& buildings) {
    while (true) {
        cout << "\n--- Buildings ---\n";
        cout << "1. Buscar por nome\n2. Listar todos\n0. Voltar\n> ";
        int choice;
        cin >> choice;
        if (choice == 0) break;

        vector<Building> results;
        if (choice == 1) {
            cin.ignore();
            string term;
            cout << "Nome: ";
            getline(cin, term);
            results = filterBuildingsByName(buildings, term);
        } else {
            results = buildings;
        }

        if (results.empty()) cout << "Nenhum resultado encontrado.\n";
        for (const auto& b : results) {
            cout << b.getName()
                 << " - " << get<0>(b.getSize()) << "x" << get<1>(b.getSize())
                 << " - " << b.getWhereToGet();
            if (b.getHousesAnimals()) {
                cout << " - abriga " << b.getAnimalAmount() << " animais";
            }
            cout << "\n";
        }
    }
}