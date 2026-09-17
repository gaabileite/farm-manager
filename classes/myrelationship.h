#include <iostream> 
#include <string> 
#include "myfarm.h" 
using namespace std; 

#ifndef MYRELATIONSHIP 
#define MYRELATIONSHIP 

class MyRelationship: public MyFarm { 
    private: 
    string villagerName; 
    int friendship; 

    public: 
    //Constructor 
    MyRelationship(string currentvillagerName, int currentfriendship); 
    
    //Destructor 
    virtual ~MyRelationship(); 
    
    //Getters 
    string getVillagerName() const; 
    int getFriendship() const; 
    
    //Setters 
    void setVillagerName(string newVillagerName); 
    void setFriendship(int newFriendship);
    void increaseFriendship(int addedFriendship); 
    void decreaseFriendship(int reducedFriendship); 
}; 

#endif