/*
 * myanimal.h
 * Estrutura e representação de um animal pertencente à fazenda
 * do jogador, incluindo seus dados cadastrais e afeição.
 */

#ifndef MYANIMAL
#define MYANIMAL

#include <iostream>
#include <string>
using namespace std;

/*
 * MyAnimal: representa um animal criado na fazenda do jogador.
 * Guarda o nome do animal, o tipo/espécie e o nível atual
 * de afeição (amizade) com o jogador.
 */
class MyAnimal {
    private:
        string animalName;
        string animalType;
        int animalRelationship;

    public:
        // Constructor
        // Passagem por referência constante evita copiar a string duas vezes.
        MyAnimal(const string& currentanimalName, 
                const string& currentanimalType, 
                int currentanimalRelationship);

        // Destructor
        virtual ~MyAnimal();

        // Getters
        string getAnimalName() const;
        string getAnimalType() const;
        int getAnimalRelaionship() const;

        // Setters
        // Mesmo motivo do construtor, evita cópia desnecessária de memória.
        void setAnimalName(const string& newanimalName);
        void setAnimalType(const string& newanimalType);
        void setAnimalRelationship(int newanimalRelationship);
        // Incrementa os pontos de afeição do animal com o jogador.
        void addHeart(int addedRelationship);
};

#endif