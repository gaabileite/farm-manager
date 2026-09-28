/*
*Implementação de funções de filtro e busca, definidas em menus/filters.h.
*/

#include "menus/filters.h"
#include <algorithm>
#include <cctype>

// Busca plantações cujo nome contenha searchTerm (case-insensitive, por substring).
// Retorna nova lista; não altera crops.
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

// Filtra plantações pela estação, ignorando maiúsculas/minúsculas.
// season: "spring", "Spring" ou "SPRING" dão o mesmo resultado.
vector<Crop> filterCropsBySeason(const vector<Crop>& crops, string season) {
    vector<Crop> results;
    transform(season.begin(), season.end(), season.begin(), ::tolower);

    for (const auto& c : crops) {
        string cropSeason = c.getSeason();
        transform(cropSeason.begin(), cropSeason.end(), cropSeason.begin(), ::tolower);

        if (cropSeason == season) {
            results.push_back(c);
        }
    }
    return results;
}

// Busca animais cujo nome contenha searchTerm (case-insensitive, por substring).
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

// Busca construções cujo nome contenha searchTerm (case-insensitive, por substring).
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