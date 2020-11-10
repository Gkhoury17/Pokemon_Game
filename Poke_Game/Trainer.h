#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

//#include "Trainer.h"
//#include "Pokemon.h"

using namespace std;

class Trainer // other "AI" trainers other than the player
{
    private:
        vector<Pokemon> suite;
        int numPokemonInParty; // randomize this and loop to this number and in each loop push a rando pokemon into the 
        string name;
    
    public:
        Trainer(); // randomizes pokemon
        void setNumPokemonInParty();
        void setName();
        void addPokemon(Pokemon pokemon);
        int getNumPokemonInParty();
        string getName();
        void getPokemon();
        bool allPokeFainted();
        Pokemon getPokeAtIdx(int idx);
        Pokemon getTActivePokemon();
        void updatePokemon(Pokemon pokemon, int idx);
        void printAllPoke();
}; 

