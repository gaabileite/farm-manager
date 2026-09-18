#include "database/menu.h"
#include "database/filters.h"
#include "classes/database.h"
#include <iostream>
#include <algorithm>

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

// User Menu:

void showFarmInfoMenu(Database& db, int farmId) {
    while (true) {
        auto info = db.getFarmInfo(farmId);
        string name = get<0>(info);
        string layout = get<1>(info);

        cout << "\n--- Informacoes da Fazenda ---\n";
        cout << "Nome: " << name << "\n";
        cout << "Layout: " << layout << "\n";
        cout << "1. Editar nome\n2. Editar layout\n0. Voltar\n> ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) {
            cin.ignore();
            string newName;
            cout << "Novo nome: ";
            getline(cin, newName);
            db.updateFarmName(farmId, newName);
        } else if (choice == 2) {
            cin.ignore();
            string newLayout;
            cout << "Novo layout: ";
            getline(cin, newLayout);
            db.updateFarmLayout(farmId, newLayout);
        }
    }
}

void showMyAnimalsMenu(Database& db, int farmId) {
    while (true) {
        cout << "\n--- Meus Animais ---\n";
        cout << "1. Adicionar animal\n";
        cout << "2. Atualizar amizade de um animal\n";
        cout << "3. Remover animal\n";
        cout << "4. Listar animais\n";
        cout << "0. Voltar\n> ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) {
            cin.ignore();
            string name, type;
            cout << "Nome do animal: ";
            getline(cin, name);
            cout << "Tipo (ex: Cow, Chicken): ";
            getline(cin, type);
            db.addAnimal(farmId, name, type, 0);
            cout << "Animal adicionado!\n";
        }
        else if (choice == 2) {
            int id, newRel;
            cout << "ID do animal: ";
            cin >> id;
            cout << "Novo nivel de amizade: ";
            cin >> newRel;
            db.updateAnimalRelationship(id, newRel);
            cout << "Atualizado!\n";
        }
        else if (choice == 3) {
            int id;
            cout << "ID do animal a remover: ";
            cin >> id;
            db.removeAnimal(id);
            cout << "Removido!\n";
        }
        else if (choice == 4) {
            string sql = "SELECT id, animal_name, animal_type, animal_relationship FROM my_animals WHERE farm_id = ?;";
            sqlite3_stmt* stmt;
            sqlite3_prepare_v2(db.getHandle(), sql.c_str(), -1, &stmt, nullptr);
            sqlite3_bind_int(stmt, 1, farmId);
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                cout << id << ". " << sqlite3_column_text(stmt, 1)
                    << " (" << sqlite3_column_text(stmt, 2) << ") - amizade "
                    << sqlite3_column_int(stmt, 3) << "\n";
            }
            sqlite3_finalize(stmt);
        }
    }
}

void showMyRelationshipsMenu(Database& db, int farmId) {
    while (true) {
        auto relationships = db.getMyRelationships(farmId);

        cout << "\n--- Relacionamentos ---\n";
        if (relationships.empty()) cout << "Nenhum relacionamento cadastrado.\n";
        for (const auto& r : relationships) {
            cout << get<0>(r) << ". " << get<1>(r) << " - " << get<2>(r) << " coracoes\n";
        }
        cout << "Numero do villager (0 para voltar): ";

        int id;
        cin >> id;
        if (id == 0) break;

        auto it = find_if(relationships.begin(), relationships.end(),
            [id](const tuple<int,string,int>& r) { return get<0>(r) == id; });
        if (it == relationships.end()) {
            cout << "Villager nao encontrado.\n";
            continue;
        }

        while (true) {
            cout << "\n--- " << get<1>(*it) << " ---\n";
            cout << get<2>(*it) << " coracoes\n";
            cout << "1. Alterar relacionamento\n0. Voltar\n> ";

            int choice;
            cin >> choice;
            if (choice == 0) break;

            if (choice == 1) {
                int newFriendship;
                cout << "Novo nivel de amizade: ";
                cin >> newFriendship;
                db.updateFriendship(id, newFriendship);
                relationships = db.getMyRelationships(farmId);
                it = find_if(relationships.begin(), relationships.end(),
                    [id](const tuple<int,string,int>& r) { return get<0>(r) == id; });
            }
        }
    }
}

void showMyBuildingsMenu(Database& db, int farmId, const vector<Building>& possibleBuildings) {
    while (true) {
        auto myBuildings = db.getMyBuildings(farmId);

        cout << "\n--- Minhas Construcoes ---\n";
        if (myBuildings.empty()) cout << "Nenhuma construcao ainda.\n";
        for (const auto& b : myBuildings) {
            cout << get<0>(b) << ". " << get<1>(b) << " (" << get<2>(b) << ") - nivel " << get<3>(b) << "\n";
        }
        cout << "1. Construir\n0. Voltar\n> ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) {
            cout << "\n--- Construcoes possiveis ---\n";
            for (size_t i = 0; i < possibleBuildings.size(); i++) {
                cout << (i + 1) << ". " << possibleBuildings[i].getName() << "\n";
            }
            cout << "Qual construcao? (0 para cancelar) ";

            int pick;
            cin >> pick;
            if (pick <= 0 || (size_t)pick > possibleBuildings.size()) continue;

            const Building& chosen = possibleBuildings[pick - 1];
            db.addBuilding(farmId, chosen.getName(), chosen.getType(), 1);
            cout << "Construido!\n";
        }
    }
}

void showMyFarmMenu(Database& db, int farmId, const vector<Building>& buildings) {
    while (true) {
        cout << "\n--- Minha Fazenda ---\n";
        cout << "1. Editar informacoes\n";
        cout << "2. Ver animais\n";
        cout << "3. Ver relacionamentos\n";
        cout << "4. Ver construcoes\n";
        cout << "0. Voltar\n> ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) showFarmInfoMenu(db, farmId);
        else if (choice == 2) showMyAnimalsMenu(db, farmId);
        else if (choice == 3) showMyRelationshipsMenu(db, farmId);
        else if (choice == 4) showMyBuildingsMenu(db, farmId, buildings);
    }
}