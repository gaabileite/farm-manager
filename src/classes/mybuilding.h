/*
 * mybuilding.h
 * Estrutura e representação de uma construção da fazenda
 * do jogador, contendo seu tipo e nível de evolução.
 */

#ifndef MYBUILDING
#define MYBUILDING

#include <iostream>
#include <string>
using namespace std;

/*
 * MyBuilding: representa uma construção na fazenda do jogador.
 * Guarda o nome da construção, o tipo de estrutura e seu nível
 * atual de melhoria (upgrade).
 */
class MyBuilding {
    private:
        string buildingName;
        string buildingType;
        int buildingLevel;

    public:
        // Constructor
        // Passagem por referência constante evita copiar a string duas vezes.
        MyBuilding(const string& currentbuildingName, 
                   const string& currentbuildingType, 
                   int currentbuildingLevel);
        
        // Destructor
        virtual ~MyBuilding();

        // Getters
        string getBuildingName() const;
        string getBuildingType() const;
        int getBuildingLevel() const;

        // Setters
        // Mesmo motivo do construtor, evita cópia desnecessária de memória.
        void setBuildingName(const string& newbuildingName);
        void setBuildingType(const string& newbuildingType);
        void setBuildingLevel(int newbuildingLevel);
        
        // Eleva o nível de melhoria da construção em uma unidade.
        void upgradeBuilding();
};

#endif