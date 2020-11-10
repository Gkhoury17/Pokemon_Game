#include <iostream>
#include "Player.h"
#include "Trainer.h"
//#include "Encounter.h"

using namespace std;



// add g++ studd here:

class Game
{
    private:
    Pokemon allPokemon[151];
    string map[25][16];
    Trainer trainers[15];
    int wildPokeLoc[20][2];
    Pokemon wildPokemon[20]; // change this to a vector and remove pokemon once it has been battled or randomize its location if it flees
    
    // map
    // trainer array
    // pokemon array
    // playern object
    
    
    public:
    Game(); // Constructor
    // Debuggers
    void printFullMap();
    void printWildPokeLocs(Player aPlayer);

    void readPokeFile();
    void readMap();
    void readTrainerArr();
    void setWildPokeArr(Player aPlayer);
    void printMap(Player aPlayer);
    void beginningOfTurn(Player aPlayer);

    Pokemon getRandPoke();
    Pokemon getPokeAt(int index);
    Player getPlayer();
    // ONES I NEED TO WORK ON
    void travel(Player aPlayer);
    void encounter(Player aPlayer);
    void trainerBattle(Player aPlayer);
    //bool endOfTurn(Player aPlayer);
    //void rest(aPlayer);
    //void testYourLuck(aPlayer);
    
    
};
