/*
 * myrelationship.h
 * Estrutura e representação do relacionamento do jogador
 * com os moradores da vila, gerenciando o nível de amizade.
 */

#ifndef MYRELATIONSHIP
#define MYRELATIONSHIP

#include <iostream> 
#include <string> 
using namespace std; 
 
/*
 * MyRelationship: representa a relação entre o jogador e um morador.
 * Guarda o nome do morador e a quantidade acumulada de pontos de amizade.
 */
class MyRelationship { 
    private: 
        string villagerName; 
        int friendship; 

    public: 
        //Constructor 
        // Passagem por referência constante evita copiar a string duas vezes.
        MyRelationship(const string& currentvillagerName, int currentfriendship);
        
        //Destructor 
        virtual ~MyRelationship(); 
        
        //Getters 
        string getVillagerName() const; 
        int getFriendship() const; 
        
        //Setters 
        // Mesmo motivo do construtor, evita cópia desnecessária de memória.
        void setVillagerName(const string& newVillagerName);
        void setFriendship(int newFriendship);

        // Incrementa a pontuação de amizade com o morador.
        void increaseFriendship(int addedFriendship); 

        // Reduz a pontuação de amizade com o morador.
        void decreaseFriendship(int reducedFriendship); 
}; 

#endif