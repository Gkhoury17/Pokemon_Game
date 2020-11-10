/*
Notes for Project
Add a vector of pokemon/trainers battled to the player class so you can know which pokemon AND trainers they battled

- ANY battle won by a pokemon will cause it to level up.

- At the end of every turn:
    - Check if the player has won the game
        - If they have collected 6 badges or 8 different types of pokemon
        - If so, write stats to different file.
    else
    - Move location of wild pokemon randomly in one direction
    - 3 possible outcomes:
        - 30% chance another pokemon just spawned. catch it or release it
        - 25% chance player finds a hidden treasure
            - 50% chance its a pokeball, 50% chance its a rare candy and you choose a pokemon to level it up
        - 20% chance a random pokemon in the players party randomly faints. Remove it from the players party

errors
 when a pokemon dies of old age, all of its stats are still under player. which is why it is saying the player won from 8 types even though it currently has less. because it still has typed from dead pokemon
 for removing pokemon, remove them from the total pokemon vector as well
     then i can loop through the total pokemomn vector and see if there are 8 different types. then, player wins.
 results file not writing.try appending to file
 finish trainer battles.
 randomize wild poke loc after they flee


 Pokemon pokemon = Pokemon(tempArr[1],stoi(tempArr[2]),stoi(tempArr[3]),stoi(tempArr[4]),stoi(tempArr[5]),stoi(tempArr[6]),tempArr[7],tempArr[8]);
*/



#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "Game.h"
// copy and paste g++ command below
// g++ -std=c++11 Pokemon.cpp Trainer.cpp Player.cpp pokeDriverReal.cpp
//

using namespace std;

int split(string splitString, char delimiter, string stringArray [], int arrayLength)
{
  if (splitString == "") {
    return 0;
  }

  int count = 0;
  int del = 0;
  for (int i = 0; i < splitString.length(); i++) {
    if (splitString[i] == delimiter) {
      if (i == del) {
        // Do nothing.
      } else {
        string subStringUntilDel = splitString.substr(del, i - del);
        //cout << "Adding: " << subStringUntilDel << " at index: " << count << endl;
        stringArray [count] = subStringUntilDel;
        del = i + 1;
      }
      count++;
    }
  }
    //cout << "heelo" << endl;
  if (del < splitString.length()) {
    string subStringUntilDel = splitString.substr(del, splitString.length() - del);
    //cout << "Adding: to" << subStringUntilDel << " at index: " << count << endl;
    stringArray [count] = subStringUntilDel;
    count++;
  }

  for (int i = 0; i < count; i++) {
    //cout << stringArray[i] << endl;
  }

  if (count > arrayLength) {
    return -1;
  }

  if(count == 0) {
    stringArray [count] = splitString;
    return 1;
  }

  return count;
}
// void beginningFunc()
// {
//     cout << "The sun is shining " + player.getName() + "! It's a beautiful day, we have " << player.getNumPokeballs() << " Pokeball(s) left and your Pokemon are stronk." << endl;
//     cout << endl;
//     cout << "Here are the stats of the current Pokemon in your party:" << endl;
//     cout << endl;
//     player.printPokemonInParty();
//     cout << endl;
//     cout << "Please choose from the following options: " << endl;
//     cout << endl;
//     cout << "1. Travel" << endl;
//     cout << "2. Rest" << endl;
//     cout << "3. Try your luck" << endl;
//     cout << "4. Quit the game" << endl;
// }

int main()
{
    Pokemon allPokemon[151];
    // Read pokemon function
    srand(time(0));
    ifstream infile;
    infile.open("pokemon.txt");
    string line;
    int count2 = 0;
    while(getline(infile,line))
    {
        string tempArr[9];
        split(line,',',tempArr,9);
        
        if(tempArr[8] == "")
        {
            Pokemon pokemon = Pokemon();
            pokemon.setName(tempArr[1]);
            pokemon.setHP(stoi(tempArr[2]));
            pokemon.setAttack(stoi(tempArr[3]));
            pokemon.setDef(stoi(tempArr[4]));
            pokemon.setS(stoi(tempArr[5]));
            pokemon.setM(stoi(tempArr[6]));
            pokemon.setType1(tempArr[7]);
            pokemon.setType2("");
            pokemon.setLevel(1);
            pokemon.setliveHP(stoi(tempArr[2]));

            allPokemon[count2] = pokemon;
            //cout << "Success1" << endl;
        }
        else
        {
            Pokemon pokemon = Pokemon();
            pokemon.setName(tempArr[1]);
            pokemon.setHP(stoi(tempArr[2]));
            pokemon.setAttack(stoi(tempArr[3]));
            pokemon.setDef(stoi(tempArr[4]));
            pokemon.setS(stoi(tempArr[5]));
            pokemon.setM(stoi(tempArr[6]));
            pokemon.setType1(tempArr[7]);
            pokemon.setType2(tempArr[8]);
            pokemon.setLevel(1);
            pokemon.setliveHP(stoi(tempArr[2]));

            allPokemon[count2] = pokemon;
            //cout << "Success2" << endl;
        }
        //cout << count << endl;
        //allPokemon[count] = pokemon;
        count2++;
        //cout << count << endl;
    }
    
    // Player starts game.
    Player player = Player(); // creates object named 'player' of class "Player"
    
    
    string playerName;
    cout << "Welcome to Pokemon!" << endl;
    cout << endl;
    cout << "Please state your name: ";
    getline(cin,playerName);
    player.setName(playerName);
    cout << "Welcome, " << playerName << "! Before you can begin your Pokemon adventure, you must choose a starting pokemon, courtesy of the Professor." << endl;
    cout << "Please choose from the following Pokemon: " << endl;
    cout << endl;
    cout << "1. Bulbasaur" << endl;
    cout << "2. Charmander" << endl;
    cout << "3. Squirtle" << endl;
    cout << "4. Pikachu" << endl;
    cin.clear();
    //cin.ignore(10000,'\n');
    int pokeChoice;
    cin >> pokeChoice;
    
    while(pokeChoice != 1 && pokeChoice != 2 && pokeChoice != 3 && pokeChoice != 4 && pokeChoice != 420) // loop while input is invalid
    {
        //cin.clear();
        // invalid input, re ask prompt
        cout << "Invalid input, please enter 1, 2, 3, or 4:" << endl;
        cin >> pokeChoice;
        cin.clear();
    }
    if(pokeChoice == 1)
    {
        //bulbasuar case row 13 column 7
        player.setLocation(12,6);
        player.addPokemon(allPokemon[0]);
        //cin.clear();
    }
    else if(pokeChoice == 2)
    {
        //charmander case row 13 column 8
        player.setLocation(12,7);
        player.addPokemon(allPokemon[3]);
        
    }
    else if(pokeChoice == 3)
    {
        //squirtle case row 13 column 9
        player.setLocation(12,8);
        player.addPokemon(allPokemon[6]);
        //allPokemon[6].getHPBar();
        //cout << pokemon.getliveHP() << endl;
    }
    else if(pokeChoice == 4)
    {
        //pikachu case row 13 column 10
        player.setLocation(12,9); // should be (12,9)
        player.addPokemon(allPokemon[24]);
        
        //allPokemon[24].getHPBar();
        //cout << "hi" << endl;

    }
    // cout << "h22i" << endl;
    //  cout << "yep" << endl;
    // else if(pokeChoice == 420)
    // {
    //     //snoop dogg case row 13 column 10
    //     player.setLocation(13,10);
    //     Pokemon snoopdogg = Pokemon("Snoop Dogg", 420,420,420,420,420,"Flying","Dog");
    //     player.addPokemon(snoopdogg);
    //     cout << "SMOKE WEED EVERYDAY" << endl;
    // }
    // cin.ignore(10000,'\n');
    //cin.clear();
    // READ MAP AND POKEMON FILES
    
    // read map function
    ifstream inFile;
    inFile.open("mapPoke.txt");
    
    string map[25][16]; // map is the 2d map array
    string tempArr[16];
    
    string line1;
    int count = 0;
    while(getline(inFile,line1))
    { 
     
        split(line1,',',tempArr,16);
        for(int i = 0;i < 16;i++)
        {
            map[count][i] = tempArr[i];
        }
        count++;
    }
    int pokeCenterLoc[15][2];
    int centerCount = 0;
    for(int i = 0;i < 25;i++)
    {
        for(int j = 0;j < 16;j++)
        {
            if(map[i][j] == "C")
            {
                //cout << i << ' ' << j << endl;
                pokeCenterLoc[centerCount][0] = i;
                pokeCenterLoc[centerCount][1] = j;
                centerCount++;
            }
        }
    }
    inFile.close();
    
    // for(int i = 0;i < 25;i++) // 25 rows, 16 columns, prints out board.
    // {
    //     for(int j = 0;j < 16;j++) // 16 columns
    //     {
    //         cout << map[i][j];
    //     }
    //     cout << endl;
        
    // }

    // Create Random Trainers and Wild Pokemon
    
    //cout << map[23][16] << endl;
    
    Trainer trainers[15];
    for(int i = 0;i < 15;i++) // iterating through each trainer and assigning them pokemon
    {
        Trainer trainer = Trainer();
        trainers[i] = trainer;
        trainers[i].setNumPokemonInParty();
        //cout << trainer.getNumPokemonInParty() << endl; // test
        trainers[i].setName();
        //cout << trainer.getName() << endl;
        int randPokeIdx;
        vector<int> pokeIdx;
        for(int j = 0;j < trainers[i].getNumPokemonInParty();j++) // iterating through pokemon for each trainer
        {
            randPokeIdx = rand() % 151; // grabs random pokemon
            if(pokeIdx.size() >= 1)
            {
                for(int k = 0;k < pokeIdx.size();k++)
                {
                    if(randPokeIdx == pokeIdx[k])
                    {
                        randPokeIdx = rand() % 151;
                    }
                }
            }
            pokeIdx.push_back(randPokeIdx);

            // I somehow need to make sure that randPokeIdx is different for each loop
            
            Pokemon pokemon = Pokemon(allPokemon[randPokeIdx].getName(), allPokemon[randPokeIdx].getHP(),allPokemon[randPokeIdx].getAttack(),allPokemon[randPokeIdx].getDefense(),allPokemon[randPokeIdx].getSpeed(),allPokemon[randPokeIdx].getMax(),allPokemon[randPokeIdx].getType1(),allPokemon[randPokeIdx].getType2());
            trainers[i].addPokemon(pokemon); // add this to trainer class
            //pokemon.getStats();
            // get random pokemon and push it into the trainers suite
        }
        //trainer.getPokemon(); // add this debug function to trainer.h
    }
    
    // Now scatter wild pokemon.
    //cout << "Trainer 1's name is: " << trainers[0].getName() << endl;

    int wildPokeLoc[20][2];
    Pokemon wildPokemon[20];
    vector <int> wildPokeIdxAlreadyFaught; // havent done NYTHING with this yet
    int randRowIdx;
    int randColIdx;
    int randPokeIdx;
    for(int i = 0;i < 20;i++) // iterating through pokemon
    {
        randPokeIdx = rand() % 151;
        Pokemon pokemon = Pokemon(allPokemon[randPokeIdx].getName(), allPokemon[randPokeIdx].getHP(),allPokemon[randPokeIdx].getAttack(),allPokemon[randPokeIdx].getDefense(),allPokemon[randPokeIdx].getSpeed(),allPokemon[randPokeIdx].getMax(),allPokemon[randPokeIdx].getType1(),allPokemon[randPokeIdx].getType2());
        wildPokemon[i] = pokemon;
        //cout << i << endl;
        
        bool pokePlaced = false;
        while(pokePlaced == false)
        {
            bool pokeConflict = false;
            randRowIdx = (rand() % 25);
            randColIdx = (rand() % 16);
            // cout << "Random row: " << randRowIdx << endl;
            // cout << "Random column: " << randColIdx << endl;
            //cout << "yep? map[randRowIdx][randColIdx] = " << map[randRowIdx][randColIdx] << endl;
            if(map[randRowIdx][randColIdx] == "p") // this accounts for everything except for other wild pokemon and the players location
            {
                //cout << "Land tile" << endl;
                if(i != 0)
                {
                    //cout << i << endl;
                    //cout << "Row: " << randRowIdx << " Column: " << randColIdx << endl;

                    for(int j = 0;j < i;j++) // Checking if location is same as other pokemon. INFINITE LOOP when i == 7
                    {
                        //cout << i << endl;
                        //cout << j << endl;
                        if(randRowIdx == wildPokeLoc[j][0] && randColIdx == wildPokeLoc[j][1]) // random lcation matches other pokmenon
                        {
                            //cout << "Other pokemon location detected at " << randRowIdx << ' ' << randColIdx << endl;
                            //cout << "Row: " << randRowIdx << " Column: " << randColIdx << endl;
                            pokeConflict = true;
                            break;
                        }
                    }
                }
                if (pokeConflict != true) 
                {
                    
                    if(randRowIdx == player.getRowIdx() && randColIdx == player.getColIdx()) // add these punctions to player.h, if location is the same as the players
                    {
                        //cout << "Pokemon location is the same as the players" << endl;
                        pokePlaced = false;
                    }
                    else
                    {
                        pokePlaced = true;
                        //cout << i << " Pokemon at Row: " << randRowIdx << " Column: " << randColIdx << endl;
                        wildPokeLoc[i][0] = randRowIdx;
                        wildPokeLoc[i][1] = randColIdx;
                    }

                }
            }
            else{
                
            }
        }
        //cout << i << endl;
        //cout << "end of loop" << endl;
    }
    // for(int i = 0;i < 20;i++)
    // {
    //     cout << map[wildPokeLoc[i][0]][wildPokeLoc[i][1]] << endl;
    // }



    cout << endl;
    // Process players choice each turn
    
    // First, print 7x7 map around player
    for(int i = -3;i <= 3;i++) // rows
    {
        for(int j = -3;j <= 3;j++) // columns
        {
            // iterating through player row plus i.
            if(player.getRowIdx() + i  < 0 || player.getRowIdx() + i > 24 || player.getColIdx() + j < 0 || player.getColIdx() + j > 15) // if the row Index is out of bounds
            {
                cout << " X";
                // if(player.getColIdx() + j < 0 || player.getColIdx() + j > 15) // if the column idx is out of bounds
                // {
                // cout << " x";
                // }
            }
            else
            {
                if(i == 0 && j == 0)
                {
                    cout << " @";
                }
                else
                {
                    //cout << player.getRowIdx() + i << endl; // -1
                    if(map[player.getRowIdx() + i][player.getColIdx() + j] == "w")
                    {
                        cout << " ~";
                    }
                    else if(map[player.getRowIdx() + i][player.getColIdx() + j] == "p")
                    {
                        cout << " *";
                    }
                    else
                    {
                        cout << ' ' << map[player.getRowIdx() + i][player.getColIdx() + j];
                    }
                }
            }
            // player.getRowIdx()
            // player.getColIdx()
        }
        cout << endl;
    }
    //cout << map[1][7] << endl;
    
    cout << endl;
    
    cout << "The sun is shining " + player.getName() + "! It's a beautiful day, we have " << player.getNumPokeballs() << " Pokeball(s) left and your Pokemon are stronk." << endl;
    cout << endl;
    cout << "Here are the stats of the current Pokemon in your party:" << endl;
    player.printPokemonInParty();
    cout << "Please choose from the following options: " << endl;
    cout << endl;
    cout << "1. Travel" << endl;
    cout << "2. Rest" << endl;
    cout << "3. Try your luck" << endl;
    cout << "4. Quit the game" << endl;
    int turnChoice;
    cin.clear();
    cin >> turnChoice;
    cin.clear();
    while(turnChoice != 4) // Turn sequence
    {
        if(turnChoice == 1) // Travel
        {
            int travelDirection;
            cout << "Would you like to move North, South, East, or West?" << endl;
            cout << "1. North" << endl;
            cout << "2. South" << endl;
            cout << "3. East" << endl;
            cout << "4. West" << endl;
            cin >> travelDirection;
            bool location = false;
            while(location == false)
            {
                if(travelDirection == 1) // North
                {
                    if(player.getRowIdx() - 1 < 0)
                    {
                        cout << "This location is out of bounds. Please choose a different direction to travel." << endl;
                        cin.clear();
                        cin >> travelDirection;
                    }
                    else if(map[player.getRowIdx() - 1][player.getColIdx()] == "w")
                    {
                        cout << "This location is water. Please choose a different direction to travel." << endl;
                        cin.clear();
                        cin >> travelDirection;
                    }
                    else
                    {
                        player.setLocation(player.getRowIdx() - 1,player.getColIdx());
                        location = true;
                        cout << player.getRowIdx() << endl;
                        cout << player.getColIdx() << endl;
                    }
                }
                else if(travelDirection == 2) // South                  
                {
                    if(player.getRowIdx() + 1 >= 25)
                    {
                        cout << "This location is out of bounds. Please choose a different direction to travel." << endl;
                        cin.clear();
                        cin >> travelDirection;
                    }
                    else if(map[player.getRowIdx() + 1][player.getColIdx()] == "w")
                    {
                        cout << "This location is water. Please choose a different direction to travel." << endl;
                        cin.clear();
                        cin >> travelDirection;
                    }
                    else
                    {
                        player.setLocation(player.getRowIdx() + 1,player.getColIdx());
                        location = true;
                        cout << player.getRowIdx() << endl;
                        cout << player.getColIdx() << endl;
                    }   
                } 
                else if (travelDirection == 3) // East
                {
                    if(player.getColIdx() + 1 >= 16)
                    {
                        cout << "This location is out of bounds. Please choose a different direction to travel." << endl;
                        cin.clear();
                        cin >> travelDirection;
                    }
                    else if(map[player.getRowIdx()][player.getColIdx() + 1] == "w")
                    {
                        cout << "This location is water. Please choose a different direction to travel." << endl;
                        cin.clear();
                        cin >> travelDirection;
                    }
                    else
                    {
                        player.setLocation(player.getRowIdx(),player.getColIdx() + 1);
                        location = true;
                        cout << player.getRowIdx() << endl;
                        cout << player.getColIdx() << endl;
                    } 
                }
                else if(travelDirection == 4) // West
                {
                    if(player.getColIdx() - 1 < 0)
                    {
                        cout << "This location is out of bounds. Please choose a different direction to travel." << endl;
                        cin.clear();
                        cin >> travelDirection;
                    }
                    else if(map[player.getRowIdx()][player.getColIdx() - 1] == "w")
                    {
                        cout << "This location is water. Please choose a different direction to travel." << endl;
                        cin.clear();
                        cin >> travelDirection;
                    }
                    else
                    {
                        player.setLocation(player.getRowIdx(),player.getColIdx() - 1);
                        location = true;
                        cout << player.getRowIdx() << endl;
                        cout << player.getColIdx() << endl;
                    } 
                }
                else
                {
                    cout << "Invalid option. Enter 1 for North, 2 for South, 3 for East, or 4 for West." << endl;
                    cin.clear();
                    cin >> travelDirection;
                }
            }
            // after player moves location, check for interactions
            if(map[player.getRowIdx()][player.getColIdx()] != "G" && map[player.getRowIdx()][player.getColIdx()] != "C")
            {
                bool encounter = false;
                int wildPokeIdxToBattle;
                for(int i = 0;i < 20;i++) // iterating through poke location 2D array
                {
                    
                    if(wildPokeLoc[i][0] >= player.getRowIdx() - 2 && wildPokeLoc[i][0] <= player.getRowIdx() + 2 && wildPokeLoc[i][1] >= player.getColIdx() - 2 && wildPokeLoc[i][1] <= player.getColIdx() + 2)
                    {
                        wildPokeIdxToBattle = i; // wild pokemon in vacinity
                        //cout << "Wild " << wildPokemon[wildPokeIdxToBattle].getName() << " in vacinity with index: " << wildPokeIdxToBattle << endl;
                        if(player.checkIfPokeIsNew(wildPokeIdxToBattle) == true)
                        {
                            //cout << "Player has not encountered this pokemon yet." << endl;
                            encounter = true;
                            player.addWildPokeFaught(wildPokeIdxToBattle);
                        }
                        else
                        {
                            
                        }
                    }
                }
                if(encounter == true) // wild encounter below
                {
                    int numWildFleeAttempts = 0;
                    int numPlayerFleeAttempts = 0;
                    player.addWildEncounter();
                    Pokemon wildPoke = Pokemon();
                    wildPoke = wildPokemon[wildPokeIdxToBattle];
        
                    Pokemon playerPokemon = Pokemon();
                    playerPokemon = player.getActivePokemon();
                    //Encounter encounter = Encounter();
                    //wildPokemon[wildPokeIdxToBattle]; // wild pokemon in vacinity
                    cout << "You ran into a wild " << wildPokemon[wildPokeIdxToBattle].getName() << "!" << endl;
                    wildPokemon[wildPokeIdxToBattle].getStats();
                    // wildPokemon[wildPokeIdxToBattle].getHPBar();
                    cout << "Your ACTIVE Pokemon is: " << endl;
                    player.getActivePokemon().getStats();
                    int battleDecision;
                    cout << "What do you want to do (pick 1, 2, or 3):" << endl;
                    cout << "1. Fight" << endl;
                    cout << "2. Switch Active Pokemon" << endl;
                    cout << "3. Run" << endl;
                    cin.clear();
                    cin >> battleDecision;
                    bool isBattleOver = false;
                    int willPokemonFight;
                    while(isBattleOver == false)
                    {
                        if(battleDecision == 1) // Fight
                        {
                            if(player.getNumWildEncounters() == 1 || player.getNumWildEncounters() == 2) 
                            {
                                cout << "You have had " << player.getNumWildEncounters() << " wild encounters." << endl;
                                player.addPokemon(wildPokemon[wildPokeIdxToBattle]);
                                isBattleOver = true;
                                break;
                            }
                            else
                            {
                                if(playerPokemon.getliveHP() <= 0)
                                {
                                    cout << "You're pokemon has fainted, you must switch pokemon to continue battle." << endl;
                                    player.switchActivePokemon();
                                }
                                else
                                {
                                    willPokemonFight = ((rand() % 10) + 1);
                                    if(willPokemonFight >= 1 && willPokemonFight <= 6) // wild pokemon fights
                                    {
                                        // fight sequence
                                        cout << "Fight!" << endl;
                                        

                                        int A;
                                        int D;
                                        if(playerPokemon.getSpeed() > wildPoke.getSpeed()) // player poke attacks first
                                        {
                                            A = (rand() % (playerPokemon.getAttack() + 1));
                                            D = (rand() & (wildPoke.getDefense() + 1));
                                            if(A > D) // player poke attack
                                            {
                                                cout << playerPokemon.getName() << " attacked for " << (A - D) << " damage." << endl;
                                                wildPoke.setliveHP(wildPoke.getliveHP() - (A - D));
                                                cout << endl;
                                                cout << "Wild pokes live HP:" << wildPoke.getliveHP() << endl;
                                                wildPoke.getHPBar();
                                                if(wildPoke.getliveHP() <= 0) // if wild poke faints
                                                {
                                                    cout << "The wild " << wildPokemon[wildPokeIdxToBattle].getName() << " has fainted." << endl;
                                                    wildPoke.restoreHP();
                                                    player.addPokemon(wildPoke);
                                                    playerPokemon.levelUp();
                                                    isBattleOver = true;
                                                    break;
                                                    
                                                }
                                            }
                                            else
                                            {
                                                
                                            }
                                            wildPokemon[wildPokeIdxToBattle] = wildPoke; // updates wild poke

                                            A = (rand() % (wildPoke.getAttack() + 1));
                                            D = (rand() % (playerPokemon.getDefense() + 1));
                                            if(A > D) // wild poke attack
                                            {
                                                playerPokemon.setliveHP(playerPokemon.getliveHP() - (A - D));
                                                cout << endl;

                                                playerPokemon.getHPBar();
                                                if(playerPokemon.getliveHP() <= 0) // if active poke faints
                                                {
                                                    cout << "Your pokemon has fainted." << endl;
                                                    wildPoke.levelUp(); // good
                                                    player.updatePoke(playerPokemon,0);
                                                    if(player.allPokeFainted() == true)
                                                    {
                                                        cout << "You lost, youre trash" << endl;
                                                        player.nearestPokeCenter(pokeCenterLoc);
                                                        player.pokeCenter();
                                                        wildPoke.levelUp();
                                                        isBattleOver = true;
                                                        break;
                                                    }
                                                    
                                                }
                                            }
                                            else
                                            {
                                                
                                            }
                                            // add pokeon attacking here right?
                                            player.updatePoke(playerPokemon,0);
                                        }
                                        else // wild poke attacks first
                                        {
                                            A = (rand() % (wildPoke.getAttack() + 1));
                                            D = (rand() % (playerPokemon.getDefense() + 1));
                                            if(A > D) // wild poke attacks
                                            {
                                                playerPokemon.setliveHP(playerPokemon.getliveHP() - (A - D));
                                                cout << endl;
                                                playerPokemon.getHPBar();
                                                if(playerPokemon.getliveHP() <= 0) // if active poke faints
                                                {
                                                    cout << "Your pokemon has fainted." << endl;
                                                    wildPoke.levelUp(); // good
                                                    player.updatePoke(playerPokemon,0);
                                                    if(player.allPokeFainted() == true)
                                                    {
                                                        cout << "You lost, youre trash" << endl;
                                                        player.nearestPokeCenter(pokeCenterLoc);
                                                        player.pokeCenter();
                                                        wildPoke.levelUp();
                                                        wildPokemon[wildPokeIdxToBattle] = wildPoke;
                                                        isBattleOver = true;
                                                        break;
                                                    }
                                                    
                                                }
                                            }
                                            else
                                            {
                                                
                                            }
                                            player.updatePoke(playerPokemon,0);
                                            A = (rand() % (playerPokemon.getAttack() + 1));
                                            D = (rand() & (wildPoke.getDefense() + 1));
                                            if(A > D) // player poke attack
                                            {
                                                wildPoke.setliveHP(wildPoke.getliveHP() - (A - D));
                                                cout << endl;
                                                wildPoke.getHPBar();
                                                if(wildPoke.getliveHP() <= 0) // if wild poke faints
                                                {
                                                    wildPoke.restoreHP();
                                                    player.addPokemon(wildPoke);
                                                    playerPokemon.levelUp();
                                                    player.updatePoke(playerPokemon,0);
                                                    wildPokemon[wildPokeIdxToBattle] = wildPoke;

                                                    isBattleOver = true;
                                                    break;
                                                    
                                                }
                                            }
                                            else
                                            {
                                                
                                            }
                                            // add players pokemon attacking here?
                                            wildPokemon[wildPokeIdxToBattle] = wildPoke;
                                            player.updatePoke(playerPokemon,0);
                                        }
                                        //if(player.)
                                        
                                    }
                                    else // wild pokemon attempts to flee
                                    {
                                        numWildFleeAttempts++;
                                        // compute flee shit here
                                        int F = ((wildPokemon[wildPokeIdxToBattle].getSpeed() * 32) / ((double)((player.getActivePokemon().getSpeed() / 4) % 256 + 30) * numWildFleeAttempts));
                                        if(F > 255) // wild pokemon flees successfully
                                        {
                                            cout << "The wild pokemon has fled." << endl;
                                            isBattleOver = true;
                                            break;
                                        }
                                        else
                                        {
                                            if(rand() % 256 < F)
                                            {
                                                // randomize location.
                                                cout << "The wild pokemon has fled!" << endl;
                                                isBattleOver = true; // wild pokemon escapes
                                                break;

                                            }
                                            else 
                                            {
                                                cout << "The pokemon failed to flee and now joines your conquest." << endl;
                                                player.addPokemon(wildPokemon[wildPokeIdxToBattle]);
                                                isBattleOver = true; // wild pokemon escape fails
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else if(battleDecision == 2) // Switch Active Pokemon
                        {
                            player.switchActivePokemon();
                        }
                        else if(battleDecision == 3) // Run
                        {
                            numPlayerFleeAttempts++;
                            if(playerPokemon.getSpeed() > wildPoke.getSpeed()) // speed is strictly greater
                            {
                                isBattleOver = true;
                                player.nearestPokeCenter(pokeCenterLoc);
                                player.pokeCenter();
                            }
                            else
                            {
                                int playerF = (((playerPokemon.getSpeed() * 32) / ((wildPoke.getSpeed() / 4) % 256) + 30) * numPlayerFleeAttempts);
                                if(playerF > 255) // player escapes
                                {
                                    isBattleOver = true;
                                    player.nearestPokeCenter(pokeCenterLoc);
                                    player.pokeCenter();
                                    // teleport to nearest pokecenter
                                }
                                else
                                {
                                    if((rand() % 256) < playerF)
                                    {
                                        isBattleOver = true; // player escapes
                                        player.nearestPokeCenter(pokeCenterLoc);
                                        player.pokeCenter();
                                    }
                                    else
                                    {
                                        isBattleOver = false; // player escape fails
                                    }
                                }
                            }
                            
                        }
                        else
                        {
                            cout << "Invalid input. Enter 1, 2, or 3:" << endl;
                            cin.clear();
                            cin >> battleDecision;
                        }
                        
                        }
                }
                else
                {
                    cout << "Player has no wild encoutner and is not on a gym or pokecenter tile" << endl;
                }
            }
            else if(map[player.getRowIdx()][player.getColIdx()] == "G") // Trainer battle
            {
                cout << "Trainer " << trainers[player.getTrainersFaught()].getName() << " wants to battle!" << endl;
                cout << endl;
                bool isTrainerBattleOver = false;
                int numPokeDefeated = 0;
                while(isTrainerBattleOver == false) // battle stuff
                {
                    Trainer trainer = Trainer();
                    trainer = trainers[player.getTrainersFaught()]; // change all to just trainer
                    //trainer.printAllPoke();
                    cout << "Their active pokemon is: " << endl;
                    
                    Pokemon trainersPoke = Pokemon();
                    trainersPoke = trainer.getPokeAtIdx(numPokeDefeated); // USE TRAINERPOKE AND UPDATE IT AFTER FIGHT SEQUENCE
                    trainersPoke.getStats();
                    cout << endl;
                    cout << "Your active pokemon is: " << endl;
                    Pokemon playerPoke = Pokemon();
                    playerPoke = player.getPokeFromSuite(0);
                    playerPoke.getStats();
                    //player.getActivePokemon().getStats();
                    cout << "What do you want to do (pick 1 or 2): " << endl;
                    cout << "1. Fight" << endl;
                    cout << "2. Switch Active Pokemon" << endl;
                    int fightDecision;
                    cin.clear();
                    cin >> fightDecision;
                    while((cin.fail() == true) || (fightDecision != 1 && fightDecision != 2))
                    {
                        cin.clear();
                        cin.ignore(10000,'\n');
                        cout << "Invalid input, please enter 1 or 2:" << endl;
                        cin >> fightDecision;
                    }
                    if(fightDecision == 1) // fight
                    {
                        cout << endl;
                        cout << "===FIGHT SEQUENCE BELOW===" << endl;
                        cout << endl;
                        if(playerPoke.getliveHP() <= 0)
                        {
                            cout << "You're active pokemon fainted. Switch pokemon to continue battle." << endl;
                        }
                        else
                        {
                            // cout << trainersPoke.getName();
                            // trainersPoke.getHPBar();
                            // cout << endl;
                            // cout << playerPoke.getName();
                            // playerPoke.getHPBar();
                            // cout << endl;
                            if(trainersPoke.getSpeed() <= playerPoke.getSpeed()) // player attacks then trainer attacks
                            {
                                // players poke attacks first
                                int A = (rand() % (playerPoke.getAttack() + 1));
                                int D = (rand() & (trainersPoke.getDefense() + 1));
                                if(A > D) // player poke attack
                                {
                                    cout << playerPoke.getName() << " attacks!" << endl;
                                    //cout << trainersPoke.getName() << "'s live HP is: " << trainersPoke.getliveHP() << endl;
                                    trainersPoke.setliveHP(trainersPoke.getliveHP() - (A - D));
                                    cout << endl;
                                    cout << trainersPoke.getName() << "'s new HP is " << trainersPoke.getliveHP() << endl;
                                    trainersPoke.getHPBar();
                                    cout << endl;
                                    trainer.updatePokemon(trainersPoke,numPokeDefeated);
                                    if(trainersPoke.getliveHP() <= 0) // if active poke faints
                                    {
                                        cout << trainersPoke.getName() << " has fainted." << endl;
                                        playerPoke.levelUp(); // good
                                        player.updatePoke(playerPoke,0);
                                        trainer.updatePokemon(trainersPoke,numPokeDefeated);
                                        numPokeDefeated++;
                                        if(trainer.allPokeFainted() == true)
                                        {
                                            cout << "Congrats! You have defeated Trainer " << trainer.getName() << endl; 
                                            // loop through traines poke and add them to player.                               
                                            isTrainerBattleOver = true;
                                            player.defeatTrainer();
                                            trainers[player.getTrainersFaught()] = trainer;
                                            for(int i = 0;i < trainer.getNumPokemonInParty();i++)
                                            {
                                                player.addPokemon(trainer.getPokeAtIdx(i));
                                            }
                                            map[player.getRowIdx()][player.getColIdx()] = "p";
                                            player.addTrainerFaught();
                                            break;
                                        }
                                    }
                                }
                                else// trainers pokemon attacks first, have them attack then player attack.
                                {

                                }

                                A = (rand() % (trainersPoke.getAttack() + 1));
                                D = (rand() % (playerPoke.getDefense() + 1));
                                if(A > D && trainersPoke.getliveHP() > 0) // wild poke attack
                                {
                                    //cout << "Current HP: " << playerPoke.getliveHP() << endl;
                                    cout << "The enemy pokemon attacks!" << endl;
                                    playerPoke.setliveHP(playerPoke.getliveHP() - (A - D));
                                    cout << endl;
                                    cout << "Your " << playerPoke.getName() << " suffered " << to_string(A - D) << " damage." << endl;
                                    //cout << "Current HP after attack: " << playerPoke.getliveHP() << endl;
                                    cout << playerPoke.getName() << endl;
                                    playerPoke.getHPBar();
                                    cout << endl;
                                    player.updatePoke(playerPoke,0);
                                    if(playerPoke.getliveHP() <= 0) // if active poke faints
                                    {
                                        cout << "Your pokemon has fainted." << endl;
                                        trainersPoke.levelUp(); // good
                                        player.updatePoke(playerPoke,0);
                                        trainer.updatePokemon(trainersPoke,numPokeDefeated);
                                        if(player.allPokeFainted() == true)
                                        {
                                            cout << "You lost, youre trash" << endl;
                                            player.nearestPokeCenter(pokeCenterLoc);
                                            player.pokeCenter();
                                            //trainers[player.getTrainersFaught()].getTActivePokemon().levelUp();
                                            isTrainerBattleOver = true;
                                            map[player.getRowIdx()][player.getColIdx()] = "p";
                                            player.addTrainerFaught();
                                            break;
                                        }
                                        
                                    }
                                }
                                else
                                {

                                }
                            }
                            else //
                            {
                                // trainer attack
                                int A = (rand() % (trainersPoke.getAttack() + 1));
                                int D = (rand() % (playerPoke.getDefense() + 1));
                                if(A > D) // wild poke attack
                                {
                                    //cout << "Current HP: " << player.getActivePokemon().getliveHP() << endl;
                                    playerPoke.setliveHP(playerPoke.getliveHP() - (A - D));
                                    cout << endl;
                                    cout << "Your " << playerPoke.getName() << " suffered " << to_string(A - D) << " damage." << endl;
                                    //cout << "Current HP after attack: " << playerPoke.getliveHP() << endl;
                                    cout << playerPoke.getName();
                                    playerPoke.getHPBar();
                                    cout << endl;
                                    player.updatePoke(playerPoke,0);
                                    if(playerPoke.getliveHP() <= 0) // if active poke faints
                                    {
                                        cout << "Your pokemon has fainted." << endl;
                                        player.updatePoke(playerPoke,0);
                                        trainersPoke.levelUp(); // good
                                        trainer.updatePokemon(trainersPoke,numPokeDefeated);
                                        if(player.allPokeFainted() == true)
                                        {
                                            cout << "You lost, youre trash" << endl;
                                            player.nearestPokeCenter(pokeCenterLoc);
                                            player.pokeCenter();
                                            //trainersPoke.levelUp();
                                            trainer.updatePokemon(trainersPoke,numPokeDefeated);
                                            isTrainerBattleOver = true;
                                            map[player.getRowIdx()][player.getColIdx()] = "p";
                                            player.addTrainerFaught();
                                            break;
                                        }
                                        
                                    }
                                }
                                else
                                {

                                }
                                A = (rand() % (playerPoke.getAttack() + 1));
                                D = (rand() & (trainersPoke.getDefense() + 1));
                                if(A > D && playerPoke.getliveHP() > 0) // player poke attack
                                {
                                    cout << playerPoke.getName() << " attacks." << endl;
                                    //cout << trainersPoke.getName() << "'s live HP is: " << trainersPoke.getliveHP() << endl;
                                    trainersPoke.setliveHP(trainersPoke.getliveHP() - (A - D));
                                    cout << endl;
                                    cout << trainersPoke.getName() << "'s HP is " << trainersPoke.getliveHP() << endl;
                                    trainersPoke.getHPBar();
                                    cout << endl;
                                    trainer.updatePokemon(trainersPoke,numPokeDefeated);
                                    if(trainersPoke.getliveHP() <= 0) // if active poke faints
                                    {
                                        cout << trainersPoke.getName() << " has fainted." << endl;
                                        playerPoke.levelUp(); // good
                                        player.updatePoke(playerPoke,0);
                                        trainer.updatePokemon(trainersPoke,numPokeDefeated);
                                        numPokeDefeated++;
                                        if(trainer.allPokeFainted() == true)
                                        {
                                            cout << "Congrats! You have defeated Trainer " << trainer.getName() << endl; 
                                            trainers[player.getTrainersFaught()] = trainer;  
                                            for(int i = 0;i < trainer.getNumPokemonInParty();i++)
                                            {
                                                player.addPokemon(trainer.getPokeAtIdx(i));
                                            }           
                                            player.defeatTrainer();
                                            map[player.getRowIdx()][player.getColIdx()] = "p";
                                            player.addTrainerFaught();                  
                                            isTrainerBattleOver = true;
                                            break;
                                        }
                                        
                                    }
                                }
                                else // trainers pokemon attacks first, have them attack then player attack.
                                {

                                }


                                // player attack
                            }
                        }
                        cout << "==========================" << endl;
                    }
                    else if(fightDecision == 2) // switch pokemon
                    {
                        player.switchActivePokemon();
                    }
                    trainers[player.getTrainersFaught()] = trainer;
                }
                
                // 
                
                // WHEN THE BATTLE IS OVER
                map[player.getRowIdx()][player.getColIdx()] = "p";
                player.addTrainerFaught();
                // if player won, player.defeatTrainer();
            }
            else if(map[player.getRowIdx()][player.getColIdx()] == "C") // Pokemon Center procedure
            {
                cout << "Pokemon center procedure" << endl;
                player.pokeCenter();
            }
            
            
        }
        else if(turnChoice == 2) // Rest
        {
            player.rest();
        }
        else if(turnChoice == 3) // Try your luck
        {
        // look in 7x7 area around player
        // iterate through wildPokeLoc array
        // if the number is good, player has 50% chance of catching it.
            for(int i = 0;i < 20;i++)
            {
                if(player.checkIfPokeIsNew(i) == true)
                {
                    if((wildPokeLoc[i][0] >= player.getRowIdx() - 3) && (wildPokeLoc[i][0] <= player.getRowIdx() + 3) && (wildPokeLoc[i][1] >= player.getColIdx() - 3) && (wildPokeLoc[i][1] <= player.getColIdx() + 3))
                    {
                        // there's a pokemon in thte 7x7 area
                        if((rand() % 2) == 1)
                        {
                            player.addPokemon(wildPokemon[i]);
                            player.addWildPokeFaught(i);
                        }
                    }
                }
            }
        }// after each turn, check if player has won. if so break loop and commence end sequence
        else // infinite loop when input is not numeric
        {
            cout << "Invalid input, please enter 1, 2, 3, or 4:" << endl;
            cin.clear();
            cin >> turnChoice;
            //cin.clear();
        }
        if(player.didPlayerWin() == true)
        {
            cout << "You've won!" << endl;
            break;
        }
        else
        {
            if(((rand() % 10) + 1) <= 3)
            {
                cout << "Catch or release case" << endl;
                int catchOrRelease;
                randPokeIdx = rand() % 151;
                Pokemon pokemon = Pokemon(allPokemon[randPokeIdx].getName(), allPokemon[randPokeIdx].getHP(),allPokemon[randPokeIdx].getAttack(),allPokemon[randPokeIdx].getDefense(),allPokemon[randPokeIdx].getSpeed(),allPokemon[randPokeIdx].getMax(),allPokemon[randPokeIdx].getType1(),allPokemon[randPokeIdx].getType2());
                cout << "Suddenly, " << pokemon.getName() << " appears in your path. Do you want to:" << endl;
                cout << "1. Catch it" << endl;
                cout << "2. Release it" << endl;
                cin >> catchOrRelease;
                while(catchOrRelease != 1 && catchOrRelease != 2)
                {
                    cout << "Invalid input, please enter a 1 or 2:" << endl;
                    cin.clear();
                    cin >> catchOrRelease;
                }
                if(catchOrRelease == 1)
                {
                    char yOrN;
                    player.addPokemon(pokemon);
                    if(player.getNumPokemon() < 6)
                    {
                        
                        cout << "Do you want to make " << pokemon.getName() << " your active pokemon? (Y/N)" << endl;
                        cin >> yOrN;
                        if(yOrN == 'Y' || yOrN == 'y')
                        {
                            // active pokemon function
                            player.makePokeActive();
                        }
                    }
                }
            }
            if(((rand() % 100) + 1) <= 25) // 25
            {
                cout << "Random item spawn" << endl;
                if(((rand() % 10) + 1) >= 5) // 5
                {
                    player.addPokeballs(2);
                    cout << "Great news! You found some pokeballs, your pokeball supply has increased to " << player.getNumPokeballs() << " pokeballs." << endl;
                }
                else
                {
                    int selection;
                    cout << "You found a rare candy, which pokemon would you like to level up?" << endl;
                    player.printPokemonNamesInParty();
                    cin.clear();
                    cin >> selection;
                    while(selection < 1 || selection > player.getSuiteSize())
                    {
                        cout << "Enter the number of the pokemon you want to level up: " << endl;
                        cin.clear();
                        cin >> selection;
                    }
                    if(selection == 1)
                    {
                        Pokemon pokemon = Pokemon();
                        pokemon = player.getPokeFromSuite(0);
                        pokemon.levelUp();
                        cout << "New level is: " << pokemon.getLevel() << endl;
                        player.updatePoke(pokemon,0);
                    }
                    else if(selection == 2)
                    {
                        Pokemon pokemon = Pokemon();
                        pokemon = player.getPokeFromSuite(1);
                        pokemon.levelUp();
                        player.updatePoke(pokemon,1);
                    }
                    else if(selection == 3)
                    {
                        Pokemon pokemon = Pokemon();
                        pokemon = player.getPokeFromSuite(2);
                        pokemon.levelUp();
                        player.updatePoke(pokemon,2);
                    }
                    else if(selection == 4)
                    {
                        Pokemon pokemon = Pokemon();
                        pokemon = player.getPokeFromSuite(3);
                        pokemon.levelUp();
                        player.updatePoke(pokemon,3);
                    }
                    else if(selection == 5)
                    {
                        Pokemon pokemon = Pokemon();
                        pokemon = player.getPokeFromSuite(4);
                        pokemon.levelUp();
                        player.updatePoke(pokemon,4);
                    }
                    else if(selection == 6)
                    {
                        Pokemon pokemon = Pokemon();
                        pokemon = player.getPokeFromSuite(5);
                        pokemon.levelUp();
                        player.updatePoke(pokemon,5);
                    }
                        
                }
            }
            if(player.getNumPokemon() > 1)
            {
                if(((rand() % 100) + 1) <= 20)
                {
                    int indexToRemove = ((rand() % player.getSuiteSize()));
                    cout << "Oh no! After years of legendary battles, " << player.getNamePokeIdx(indexToRemove) << " died of old age. Thank you for your companionship, dear friend." << endl;
                    player.removePokemon(indexToRemove);
                }
            }
            //randomize pokelocs
            //cout << "About to randomize poke locations" << endl;
            
            // GETTING SEG FAULT BELOW!
            
            for(int i = 0;i < 20;i++) // randomized poke locations
            {
                if(player.checkIfPokeIsNew(i) == true)
                {
                    bool pokePlaced2 = false;
                    while(pokePlaced2 == false)
                    {
                        int direction = rand() % 4;
                        if(direction == 0) // north
                        {
                            if(wildPokeLoc[i][0] - 1 < 0 || map[wildPokeLoc[i][0] - 1][wildPokeLoc[i][1]] == "C" || map[wildPokeLoc[i][0] - 1][wildPokeLoc[i][1]] == "G" || ((player.getRowIdx() == wildPokeLoc[i][0] - 1) && player.getColIdx() == wildPokeLoc[i][1]))
                            {
                                pokePlaced2 = false;
                            }
                            else
                            {
                                wildPokeLoc[i][0] = (wildPokeLoc[i][0] - 1);
                                pokePlaced2 = true;
                            }
                        }
                        else if(direction == 1) // south
                        {
                            if(wildPokeLoc[i][0] + 1 > 24 || map[wildPokeLoc[i][0] + 1][wildPokeLoc[i][1]] == "C" || map[wildPokeLoc[i][0] + 1][wildPokeLoc[i][1]] == "G" || ((player.getRowIdx() == wildPokeLoc[i][0] + 1) && player.getColIdx() == wildPokeLoc[i][1]))
                            {
                                pokePlaced2 = false;
                            }
                            else 
                            {
                                wildPokeLoc[i][0] = (wildPokeLoc[i][0] + 1);
                                pokePlaced2 = true;
                            }
                        }
                        else if(direction == 2) // east
                        {
                            if(wildPokeLoc[i][1] + 1 > 15 || map[wildPokeLoc[i][0]][wildPokeLoc[i][1] + 1] == "C" || map[wildPokeLoc[i][0]][wildPokeLoc[i][1] + 1] == "G" || ((player.getRowIdx() == wildPokeLoc[i][0]) && player.getColIdx() == wildPokeLoc[i][1] + 1))
                            {
                                pokePlaced2 = false;
                            }
                            else
                            {
                                wildPokeLoc[i][1] = (wildPokeLoc[i][1] + 1);
                                pokePlaced2 = true;
                            }
                        }
                        else if(direction == 3) // west
                        {
                            if(wildPokeLoc[i][1] - 1 < 0 || map[wildPokeLoc[i][0]][wildPokeLoc[i][1] - 1] == "C" || map[wildPokeLoc[i][0]][wildPokeLoc[i][1] - 1] == "G" || ((player.getRowIdx() == wildPokeLoc[i][0]) && player.getColIdx() == wildPokeLoc[i][1] - 1))
                            {
                                pokePlaced2 = false;
                            }
                            else
                            {
                                wildPokeLoc[i][1] = (wildPokeLoc[i][1] - 1);
                                pokePlaced2 = true;
                            }
                        }
                    }
                }
            }
            cout << endl;
            // cout << "Number of badges: " << player.getNumBadges() << endl;
            // cout << "Players Different types: " << endl;
            // player.didPlayerWin();
            //cout << "About to print mini map" << endl;
            for(int i = -3;i <= 3;i++) // rows
            {
                for(int j = -3;j <= 3;j++) // columns
                {
                    // iterating through player row plus i.
                    if(player.getRowIdx() + i  < 0 || player.getRowIdx() + i > 24 || player.getColIdx() + j < 0 || player.getColIdx() + j > 15) // if the row Index is out of bounds
                    {
                        cout << " X";
                        // if(player.getColIdx() + j < 0 || player.getColIdx() + j > 15) // if the column idx is out of bounds
                        // {
                        // cout << " x";
                        // }
                    }
                    else
                    {
                        if(i == 0 && j == 0)
                        {
                            cout << " @";
                        }
                        else
                        {
                            //cout << player.getRowIdx() + i << endl; // -1
                            if(map[player.getRowIdx() + i][player.getColIdx() + j] == "w")
                            {
                                cout << " ~";
                            }
                            else if(map[player.getRowIdx() + i][player.getColIdx() + j] == "p")
                            {
                                cout << " *";
                            }
                            else
                            {
                                cout << ' ' << map[player.getRowIdx() + i][player.getColIdx() + j];
                            }
                        }
                    }
                    // player.getRowIdx()
                    // player.getColIdx()
                }
                cout << endl;
            }
            cout << "The sun is shining " + player.getName() + "! It's a beautiful day, we have " << player.getNumPokeballs() << " Pokeball(s) left and your Pokemon are stronk." << endl;
            cout << endl;
            cout << "Here are the stats of the current Pokemon in your party:" << endl;
            player.printPokemonInParty();
            cout << "Please choose from the following options: " << endl;
            cout << endl;
            cout << "1. Travel" << endl;
            cout << "2. Rest" << endl;
            cout << "3. Try your luck" << endl;
            cout << "4. Quit the game" << endl;
            cin.clear();
            cin >> turnChoice;
            cin.clear();
        
        }
        // after each turn, randomize pokemon location, check if the player won
    }
    
    // End of game sequence
    cout << "Thank you for playing!" << endl;
    char playerWon;
    if(player.didPlayerWin() == true)
    {
        playerWon = 'Y';
    }
    else
    {
        playerWon = 'N';
    }
    fstream file;
    file.open("results.txt",ios::app);
    file << player.getName() << ' ' << playerWon << ' ' << player.getNumPoints() << endl << endl;
}
