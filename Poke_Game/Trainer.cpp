#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//#include "Player.h"
#include "Pokemon.h"
#include "Trainer.h"

using namespace std;

Trainer::Trainer()
{
    vector<Pokemon> suite;
    numPokemonInParty = 0;
    name = "";
}
void Trainer::setNumPokemonInParty()
{
    numPokemonInParty = (rand() % 6) + 1;
}
int Trainer::getNumPokemonInParty()
{
    return numPokemonInParty;
}
void Trainer::setName()
{
    ifstream inFile;
    inFile.open("names.txt");
    
    string tempName;
    int nameIdx = (rand() % 200) + 1;
    //cout << nameIdx;
    for(int i = 1;i <= nameIdx;i++)
    {
        getline(inFile,tempName);
        if(i == nameIdx)
        {
            getline(inFile,tempName);
        }
        
    }
    name = tempName;
    //cout << name << endl;
    inFile.close();
}

string Trainer::getName()
{
    return name;
}
void Trainer::addPokemon(Pokemon pokemon)
{
    suite.push_back(pokemon);
}
void Trainer::getPokemon() // debug function
{
    for(int i = 0;i < numPokemonInParty;i++)
    {
        suite[i].getStats();
    }
}
Pokemon Trainer::getTActivePokemon()
{
    //1cout << "Get active pokemon " << endl;
    return suite[0];
    
    // for(int i = 0;i < suite.size();i++)
    // {
    //     if(suite[i].getliveHP() > 0)
    //     {
    //         return suite[i];
    //     }
    // }
}
bool Trainer::allPokeFainted()
{
    for(int i = 0;i < suite.size();i++)
    {
        if(suite[i].getliveHP() > 0)
        {
            //cout << suite[i].getName() << "'s HP is at " << suite[i].getliveHP() << " (alive)" << endl;
            return false;
        }
        else
        {
            //cout << suite[i].getName() << "'s HP is at " << suite[i].getliveHP() << " (fainted)" << endl;
        }
        
    }
    
    return true;
}
Pokemon Trainer::getPokeAtIdx(int idx)
{
    return suite[idx];
}
void Trainer::updatePokemon(Pokemon pokemon, int idx)
{
    suite[idx] = pokemon;
}
void Trainer::printAllPoke()
{
    for(int i = 0;i < suite.size();i++)
    {
        cout << suite[i].getName() << endl;
    }
}