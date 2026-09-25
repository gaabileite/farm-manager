#include "database/menu.h"
#include "database/filters.h"
#include "classes/database.h"
#include <iostream>
#include <algorithm>

void showCropMenu(const vector<Crop>& crops) {
    while (true) {
        cout << "\n--- Crops ---\n";
        cout << "1. Search by name\n2. Filter by season\n3. List all\n0. Back\n> ";
        int choice;
        cin >> choice;
        if (choice == 0) break;

        vector<Crop> results;
        if (choice == 1) {
            cin.ignore();
            string term;
            cout << "Name: ";
            getline(cin, term);
            results = filterCropsByName(crops, term);
        } else if (choice == 2) {
            string season;
            cout << "Season: ";
            cin >> season;
            results = filterCropsBySeason(crops, season);
        } else {
            results = crops;
        }

        if (results.empty()) cout << "No results found.\n";
        for (const auto& c : results) {
            cout << c.getName() << " - " << c.getSeason() << " - " << c.getDaysToHarvest() << " dias\n";
        }
    }
}

void showAnimalMenu(const vector<Animal>& animals) {
    while (true) {
        cout << "\n--- Animals ---\n";
        cout << "1. Search by name\n2. List all\n0. Back\n> ";
        int choice;
        cin >> choice;
        if (choice == 0) break;

        vector<Animal> results;
        if (choice == 1) {
            cin.ignore();
            string term;
            cout << "Name: ";
            getline(cin, term);
            results = filterAnimalsByName(animals, term);
        } else {
            results = animals;
        }

        if (results.empty()) cout << "No results found.\n";
        for (const auto& a : results) {
            cout << a.getName() << " - produces " << a.getProduces()
                 << " - " << a.getDaysToAdult() << " days to adult"
                 << " - " << a.getBuyPrice() << "g\n";
        }
    }
}

void showBuildingMenu(const vector<Building>& buildings) {
    while (true) {
        cout << "\n--- Buildings ---\n";
        cout << "1. Search by name\n2. List all\n0. Back\n> ";
        int choice;
        cin >> choice;
        if (choice == 0) break;

        vector<Building> results;
        if (choice == 1) {
            cin.ignore();
            string term;
            cout << "Name: ";
            getline(cin, term);
            results = filterBuildingsByName(buildings, term);
        } else {
            results = buildings;
        }

        if (results.empty()) cout << "No results found.\n";
        for (const auto& b : results) {
            cout << b.getName()
                 << " - " << get<0>(b.getSize()) << "x" << get<1>(b.getSize())
                 << " - " << b.getWhereToGet();
            if (b.getHousesAnimals()) {
                cout << " - houses " << b.getAnimalAmount() << " animals";
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

        cout << "\n--- Farm Info ---\n";
        cout << "Name: " << name << "\n";
        cout << "Layout: " << layout << "\n";
        cout << "1. Edit name\n2. Edit layout\n0. Back\n> ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) {
            cin.ignore();
            string newName;
            cout << "New name: ";
            getline(cin, newName);
            db.updateFarmName(farmId, newName);
        } else if (choice == 2) {
            cin.ignore();
            string newLayout;
            cout << "New layout: ";
            getline(cin, newLayout);
            db.updateFarmLayout(farmId, newLayout);
        }
    }
}

void showMyAnimalsMenu(Database& db, int farmId) {
    while (true) {
        cout << "\n--- My Animals ---\n";
        cout << "1. Add animal\n";
        cout << "2. Update an animal's friendship\n";
        cout << "3. Remove animal\n";
        cout << "4. List animals\n";
        cout << "0. Back\n> ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) {
            cin.ignore();
            string name, type;
            cout << "Animal name: ";
            getline(cin, name);
            cout << "Type (e.g. Cow, Chicken): ";
            getline(cin, type);
            db.addAnimal(farmId, name, type, 0);
            cout << "Animal added!\n";
        }
        else if (choice == 2) {
            int id, newRel;
            cout << "Animal ID: ";
            cin >> id;
            cout << "New friendship level: ";
            cin >> newRel;
            db.updateAnimalRelationship(id, newRel);
            cout << "Updated!\n";
        }
        else if (choice == 3) {
            int id = resolveAnimalId(db, farmId);
            if (id != -1) {
                db.removeAnimal(id);
                cout << "Removed!\n";
            }
        }
        else if (choice == 4) {
            string sql = "SELECT id, animal_name, animal_type, animal_relationship FROM my_animals WHERE farm_id = ?;";
            sqlite3_stmt* stmt;
            sqlite3_prepare_v2(db.getHandle(), sql.c_str(), -1, &stmt, nullptr);
            sqlite3_bind_int(stmt, 1, farmId);
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                cout << id << ". " << sqlite3_column_text(stmt, 1)
                    << " (" << sqlite3_column_text(stmt, 2) << ") - friendship "
                    << sqlite3_column_int(stmt, 3) << "\n";
            }
            sqlite3_finalize(stmt);
        }
    }
}

void showMyRelationshipsMenu(Database& db, int farmId) {
    while (true) {
        auto relationships = db.getMyRelationships(farmId);

        cout << "\n--- Relationships ---\n";
        if (relationships.empty()) cout << "No relationships registered.\n";
        for (const auto& r : relationships) {
            cout << get<0>(r) << ". " << get<1>(r) << " - " << get<2>(r) << " hearts\n";
        }
        cout << "Villager number (0 to go back): ";

        int id;
        cin >> id;
        if (id == 0) break;

        auto it = find_if(relationships.begin(), relationships.end(),
            [id](const tuple<int,string,int>& r) { return get<0>(r) == id; });
        if (it == relationships.end()) {
            cout << "Villager not found.\n";
            continue;
        }

        while (true) {
            cout << "\n--- " << get<1>(*it) << " ---\n";
            cout << get<2>(*it) << " hearts\n";
            cout << "1. Change relationship\n0. Back\n> ";

            int choice;
            cin >> choice;
            if (choice == 0) break;

            if (choice == 1) {
                int newFriendship;
                cout << "New friendship level: ";
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

        cout << "\n--- My Buildings ---\n";
        if (myBuildings.empty()) cout << "No buildings yet.\n";
        for (const auto& b : myBuildings) {
            cout << get<1>(b) << " (" << get<2>(b) << ") - level " << get<3>(b) << "\n";
        }
        cout << "1. Build\n2. Remove\n0. Back\n> ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) {
            // ... (unchanged)
        }
        else if (choice == 2) {
            int id = resolveBuildingId(db, farmId);
            if (id != -1) {
                db.removeBuilding(id);
                cout << "Removed!\n";
            }
        }
    }
}

void showMyFarmMenu(Database& db, int farmId, const vector<Building>& buildings) {
    while (true) {
        cout << "\n--- My Farm ---\n";
        cout << "1. Edit info\n";
        cout << "2. View animals\n";
        cout << "3. View relationships\n";
        cout << "4. View buildings\n";
        cout << "0. Back\n> ";

        int choice;
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) showFarmInfoMenu(db, farmId);
        else if (choice == 2) showMyAnimalsMenu(db, farmId);
        else if (choice == 3) showMyRelationshipsMenu(db, farmId);
        else if (choice == 4) showMyBuildingsMenu(db, farmId, buildings);
    }
}

// Asks for the name, resolves it to the internal id; if ambiguous, disambiguates by type,
// and if still ambiguous, lets the user pick by numbered position (never by the raw id)
int resolveAnimalId(Database& db, int farmId) {
    cin.ignore();
    string name;
    cout << "Animal name: ";
    getline(cin, name);

    auto matches = db.findMyAnimalsByName(farmId, name);
    if (matches.empty()) {
        cout << "Animal not found.\n";
        return -1;
    }
    if (matches.size() == 1) {
        return get<0>(matches[0]);
    }

    cout << "There is more than one animal named \"" << name << "\":\n";
    for (const auto& m : matches) {
        cout << " - Type: " << get<2>(m) << "\n";
    }
    cout << "Which type? ";
    string type;
    getline(cin, type);

    vector<tuple<int,string,string,int>> filtered;
    for (const auto& m : matches) {
        if (get<2>(m) == type) filtered.push_back(m);
    }

    if (filtered.size() == 1) {
        return get<0>(filtered[0]);
    }
    if (filtered.empty()) {
        cout << "No animal with that name and type.\n";
        return -1;
    }

    cout << "There is still more than one. Choose by current friendship level:\n";
    for (size_t i = 0; i < filtered.size(); i++) {
        cout << (i + 1) << ". friendship: " << get<3>(filtered[i]) << "\n";
    }
    cout << "Number: ";
    int pick;
    cin >> pick;
    if (pick < 1 || (size_t)pick > filtered.size()) return -1;
    return get<0>(filtered[pick - 1]);
}

int resolveBuildingId(Database& db, int farmId) {
    cin.ignore();
    string name;
    cout << "Building name: ";
    getline(cin, name);

    auto matches = db.findMyBuildingsByName(farmId, name);
    if (matches.empty()) {
        cout << "Building not found.\n";
        return -1;
    }
    if (matches.size() == 1) {
        return get<0>(matches[0]);
    }

    cout << "There is more than one building named \"" << name << "\":\n";
    for (const auto& m : matches) {
        cout << " - Type: " << get<2>(m) << "\n";
    }
    cout << "Which type? ";
    string type;
    getline(cin, type);

    vector<tuple<int,string,string,int>> filtered;
    for (const auto& m : matches) {
        if (get<2>(m) == type) filtered.push_back(m);
    }

    if (filtered.size() == 1) {
        return get<0>(filtered[0]);
    }
    if (filtered.empty()) {
        cout << "No building with that name and type.\n";
        return -1;
    }

    cout << "There is still more than one. Choose by current level:\n";
    for (size_t i = 0; i < filtered.size(); i++) {
        cout << (i + 1) << ". level: " << get<3>(filtered[i]) << "\n";
    }
    cout << "Number: ";
    int pick;
    cin >> pick;
    if (pick < 1 || (size_t)pick > filtered.size()) return -1;
    return get<0>(filtered[pick - 1]);
}