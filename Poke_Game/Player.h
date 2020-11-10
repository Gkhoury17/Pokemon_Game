#include <iostream>
#include <vector>
#include <string>
//#include "Player.h"
#include "Pokemon.h"

using namespace std;


class Player : public Pokemon
{
    private:
        int numBadges;
        int numPoints;
        int numPokeballs;
        int numWildEncounters;
        int numPokemon;
        string name;
        int rowIndex;
        int columnIndex;
        int numTrainersFaught;
        //ADD NUMTYPES WHICH IS HOW MANY UNIQUE TYPES THE TRAINER HAS.
        vector<Pokemon> totalPokemon;
        vector<Pokemon> suite;
        vector<string> types; // if this size >= 8, player wins
        vector<int> idxOfTrainersFaught;
        vector<int> idxOfWildPokeFaught;
        // maybe make a 2d array that holds locations of gyms the player has already been to.
    
    public:
        Player(); //set everything to 0;
        
        int getTrainersFaught();
        int getNumPokemon();
        int getNumPokeballs();
        int getNumPoints();
        int getNumBadges();
        int getNumWildEncounters();
        int getRowIdx();
        int getColIdx();
        Pokemon getPokeFromSuite(int index);
        int getSuiteSize();
        string getName();
        Pokemon getActivePokemon();
        bool didPlayerWin();
        string getNamePokeIdx(int index);
        
        bool checkIfPokeIsNew(int index);
        bool allPokeFainted();
        
        void updatePoke(Pokemon pokemon, int idx);

        void nearestPokeCenter(int pokeCenterLocs[][2]);
        void addTrainerFaught();
        void addWildPokeFaught(int index);
        void removePokemon(int index);
        void printPokemonNamesInParty();
        void addPokeballs(int numBalls);
        void switchActivePokemon();
        void setLocation(int newRowIndex,int newColumnIndex);
        void setName(string newName);
        void printPokemonInParty();
        void addPokemon(Pokemon pokemon);
        void defeatTrainer();
        void caughtWildPokemon();
        void addWildEncounter();
        void rest();
        void tryLuck();
        void printTypesVector();
        
        void pokeCenter();
        void makePokeActive();
};
