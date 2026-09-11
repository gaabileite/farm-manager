#include "database/filters.h"
#include <algorithm>
#include <cctype>

vector<Crop> filterCropsByName(const vector<Crop>& crops, string searchTerm) {
    vector<Crop> results;
    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

    for (const auto& c : crops) {
        string name = c.getName();
        transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (name.find(searchTerm) != string::npos) {
            results.push_back(c);
        }
    }
    return results;
}

vector<Crop> filterCropsBySeason(const vector<Crop>& crops, string season) {
    vector<Crop> results;
    for (const auto& c : crops) {
        if (c.getSeason() == season) {
            results.push_back(c);
        }
    }
    return results;
}

vector<Animal> filterAnimalsByName(const vector<Animal>& animals, string searchTerm) {
    vector<Animal> results;
    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

    for (const auto& a : animals) {
        string name = a.getName();
        transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (name.find(searchTerm) != string::npos) {
            results.push_back(a);
        }
    }
    return results;
}

vector<Building> filterBuildingsByName(const vector<Building>& buildings, string searchTerm) {
    vector<Building> results;
    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

    for (const auto& b : buildings) {
        string name = b.getName();
        transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (name.find(searchTerm) != string::npos) {
            results.push_back(b);
        }
    }
    return results;
}