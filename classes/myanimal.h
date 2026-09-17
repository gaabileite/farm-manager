#include <iostream>
#include <string>
#include "myfarm.h"

#ifndef MYANIMAL
#define MYANIMAL

class MyAnimal : public MyFarm {
    private:
        string animalName;
        string animalType;
        int animalRelationship;

    public:
        MyAnimal(string currentanimalName, string currentanimalType, int currentanimalRelationship);
        virtual ~MyAnimal();

        string getAnimalName() const;
        string getAnimalType() const;
        int getAnimalRelaionship() const;

        void setAnimalName(string newanimalName);
        void setAnimalType(string newanimalType);
        void setAnimalRelationship(int newanimalRelationship);
        void addHeart(int addedRelationship);
};

#endif