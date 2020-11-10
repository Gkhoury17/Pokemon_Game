#include <iostream>
#include <cmath>
#include <string>
#include "Pokemon.h"

using namespace std;

Pokemon::Pokemon()
{
    HP = 0;
    attack = 0;
    defense = 0;
    speed = 0;
    max = 0;
    name = "";
    type1 = "";
    type2 = "";
    level = 0;
    liveHP = 0;
}
Pokemon::Pokemon(string newName, int newHP, int newAttack, int newDefense, int newSpeed, int newMax, string newType1, string newType2)
{
    name = newName;
    HP = newHP;
    attack = newAttack;
    defense = newDefense;
    speed = newSpeed;
    max = newMax;
    type1 = newType1;
    type2 = newType2;
    liveHP = HP;
    level = 1;
}
int Pokemon::getHP()
{
    return HP;
}
int Pokemon::getAttack()
{
    return attack;
}
int Pokemon::getDefense()
{
    return defense;
}
int Pokemon::getSpeed()
{
    return speed;
}
int Pokemon::getMax()
{
    return max;
}
string Pokemon::getName()
{
    return name;
}
string Pokemon::getType1()
{
    return type1;
}
string Pokemon::getType2()
{
    return type2;
}
int Pokemon::getLevel()
{
    return level;
}
int Pokemon::getliveHP()
{
    return liveHP;
}
bool Pokemon::isPokeAlive()
{
    if(liveHP <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void Pokemon::setName(string newName)
{
    name = newName;
}
void Pokemon::setHP(int HP)
{
    this->HP = HP;
}
void Pokemon::setAttack(int newA)
{
    attack = newA;
}
void Pokemon::setDef(int newD)
{
    defense = newD;
}
void Pokemon::setS(int newS)
{
    speed = newS;
}
void Pokemon::setM(int newM)
{
    max = newM;
}
void Pokemon::setType1(string newType1)
{
    type1 = newType1;
}
void Pokemon::setType2(string newType2)
{
    type2 = newType2;
}
void Pokemon::setLevel(int newLevel)
{
    level = newLevel;
}
void Pokemon::setliveHP(int newliveHP)
{
    liveHP = newliveHP;
}
void Pokemon::getHPBar() //somehow display HP bar for pokemon during battle #extracredits
{
    if(HP != 0)
    {
        double numHPBars;
        cout << "HP:";
        numHPBars = ((double)liveHP / (double)HP) * 10;
        for(int i = 0;i < 10;i++) // 10 times
        {
            
            //cout << numHPBars << endl
            if(i == 0)
            {
                cout << '[';
            }
            if(numHPBars > 0)
            {
                cout << 'I';
            }
            if(i == 9)
            {
                cout << ']';
            }
            else if(numHPBars <= 0)
            {
                cout << ' ';
            }
            numHPBars = numHPBars - 1;  
        }
    }
}
void Pokemon::getStats()
{
    cout << "Name: " << name << ", HP: " << to_string(liveHP) << "/" << to_string(HP) << ", A: " << to_string(attack) << ", D: " << to_string(defense) << ", S: " << to_string(speed) << ", M: " << to_string(max) << " Type 1: " << type1 << " Type 2: " << type2 << " Level: " << to_string(level) << endl;
}
void Pokemon::levelUp()
{
    cout << name << " leveled up!" << endl;
    level++;
    // first is HP
    HP = HP + (round(HP * .02));
    liveHP = liveHP + (round(HP * .02));
    //cout << "HP increased by " << to_string((round(HP * .02))) << endl;
    if(attack < max) // only level attack and defense up if theyre below max
    {
        attack = attack + (round(attack * .02));
    }
    if(defense < max)
    {
        defense = defense + (round(defense * .02));
    }
    speed = speed + (round(speed * .02));
    
    
}
void Pokemon::restoreHP()
{
    liveHP = HP;
}
