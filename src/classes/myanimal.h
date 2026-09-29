#include <iostream>
#include <string>
using namespace std;

#ifndef MYANIMAL
#define MYANIMAL

class MyAnimal {
    private:
        string animalName;
        string animalType;
        int animalRelationship;

    public:
        // Constructor
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
        void setAnimalName(const string& newanimalName);
        void setAnimalType(const string& newanimalType);
        void setAnimalRelationship(int newanimalRelationship);
        void addHeart(int addedRelationship);
};

#endif