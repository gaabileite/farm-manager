/*
 * myfarm.h
 * Estrutura e representação da fazenda do jogador, reunindo
 * as informações básicas e suas listas de elementos associados.
 */

#ifndef MYFARM
#define MYFARM

#include <iostream>
#include <string>
#include <vector>
#include "myanimal.h"
#include "mybuilding.h"
#include "myrelationship.h"

using namespace std;

/*
 * MyFarm: representa a fazenda do jogador.
 * Guarda os dados gerais da fazenda (nome e layout) e agrupa as
 * coleções de animais, construções e relacionamentos do jogador.
 */
class MyFarm {
    private:
        string farmName;
        string farmLayout;
        vector<MyAnimal> myAnimals;
        vector<MyBuilding> myBuildings;
        vector<MyRelationship> myRelationships;

    public:
        // Constructor
        // Passagem por referência constante evita copiar a string duas vezes.
        MyFarm(const string& currentfarmName, 
               const string& currentfarmLayout);

        // Destructor
        virtual ~MyFarm();

        // Getters
        string getFarmName() const;
        string getFarmLayout() const;

        // Setters
        // Mesmo motivo do construtor, evita cópia desnecessária de memória.
        void setFarmName(const string& newfarmName);
        void setFarmLayout(const string& newfarmLayout);
};

#endif