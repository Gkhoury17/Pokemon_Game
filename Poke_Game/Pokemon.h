#include <iostream>
#include <vector>
#include <string>
//#include "Pokemon.h"

using namespace std;

class Pokemon
{
    private:
        string name;
        int HP; // i might need to add base hp and battle hp, or handel that in encounters?
        int attack;
        int defense;
        int speed;
        int max;
        string type1;
        string type2;
        int level;
        int liveHP;
        
    public:
        Pokemon(); // sets all stats to 0
        Pokemon(string newName, int newHP, int newAttack, int newDefense, int newSpeed, int newMax, string newType1, string newType2);
        // Constructors ^
        string getName();
        int getHP(); 
        void getHPBar(); // diplay   HP: ||||||||||||||||||||
        int getAttack();
        int getDefense();
        int getSpeed();
        int getMax();
        string getType1();
        string getType2();
        int getLevel();
        int getliveHP();

        void setName(string newName);
        void setHP(int HP);
        void setAttack(int newA);
        void setDef(int newD);
        void setS(int newS);
        void setM(int newM);
        void setType1(string newType1);
        void setType2(string newType2);
        void setLevel(int newLevel);
        void setliveHP(int newliveHP);

    
        void getStats();
        bool isPokeAlive();
        // Getters ^
        void levelUp();
        void setStats(string newName, int newHP, int newAttack, int newDefense, int newSpeed, int newMax, string newType1, string newType2);
        void restoreHP();
        // Setters ^
};