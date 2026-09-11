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

// ... mesmo padrão para showAnimalMenu, showBuildingMenu