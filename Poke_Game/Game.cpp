#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "Game.h"

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

using namespace std;

Game::Game()
{
    Pokemon allPokemon[151];
    string map[25][16];
    Trainer trainers[15];
    int wildPokeLoc[20][2];
    Pokemon wildPokemon[20];
}
void Game::readPokeFile()
{
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
            Pokemon pokemon = Pokemon(tempArr[1],stoi(tempArr[2]),stoi(tempArr[3]),stoi(tempArr[4]),stoi(tempArr[5]),stoi(tempArr[6]),tempArr[7],"");
            allPokemon[count2] = pokemon;
            //cout << "Success1" << endl;
        }
        else
        {
            Pokemon pokemon = Pokemon(tempArr[1],stoi(tempArr[2]),stoi(tempArr[3]),stoi(tempArr[4]),stoi(tempArr[5]),stoi(tempArr[6]),tempArr[7],tempArr[8]);
            allPokemon[count2] = pokemon;
            //cout << "Success2" << endl;
        }
        //cout << count << endl;
        //allPokemon[count] = pokemon;
        count2++;
        //cout << count << endl;
    }
    
}
void Game::readMap()
{
    ifstream inFile;
    inFile.open("mapPoke.txt");
    
     // map is the 2d map array
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
    inFile.close();
}
void Game::readTrainerArr()
{
    for(int i = 0;i < 15;i++) // iterating through each trainer and assigning them pokemon
    {
        Trainer trainer = Trainer();
        trainers[i] = trainer;
        trainer.setNumPokemonInParty();
        //cout << trainer.getNumPokemonInParty() << endl; // test
        trainer.setName();
        //cout << trainer.getName() << endl;
        int randPokeIdx;
        vector<int> pokeIdx;
        for(int j = 0;j < trainer.getNumPokemonInParty();j++) // iterating through pokemon for each trainer
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
            trainer.addPokemon(pokemon); // add this to trainer class
            //pokemon.getStats();
            // get random pokemon and push it into the trainers suite
        }
        //trainer.getPokemon(); // add this debug function to trainer.h
    }
}
void Game::setWildPokeArr(Player aPlayer)
{
    int randRowIdx;
    int randColIdx;
    for(int i = 0;i < 20;i++) // iterating through pokemon
    {
        int randPokeIdx = rand() % 151;
        Pokemon pokemon = Pokemon(allPokemon[randPokeIdx].getName(), allPokemon[randPokeIdx].getHP(),allPokemon[randPokeIdx].getAttack(),allPokemon[randPokeIdx].getDefense(),allPokemon[randPokeIdx].getSpeed(),allPokemon[randPokeIdx].getMax(),allPokemon[randPokeIdx].getType1(),allPokemon[randPokeIdx].getType2());
        wildPokemon[i] = pokemon;
        //cout << i << endl;
        bool pokeConflict = false;
        bool pokePlaced = false;
        while(pokePlaced == false)
        {
            randRowIdx = (rand() % 26);
            randColIdx = (rand() % 17);
            //cout << "yep? map[randRowIdx][randColIdx] = " << map[randRowIdx][randColIdx] << endl;
            if(map[randRowIdx][randColIdx] == "p") // this accounts for everything except for other wild pokemon and the players location
            {
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
                    
                    if(randRowIdx == aPlayer.getRowIdx() && randColIdx == aPlayer.getColIdx()) // add these punctions to player.h, if location is the same as the players
                    {
                        //cout << "Pokemon location is the same as the players" << endl;
                        pokePlaced = false;
                    }
                    else
                    {
                        pokePlaced = true;
                        //cout << "Pokemon at Row: " << randRowIdx << " Column: " << randColIdx << endl;
                        wildPokeLoc[i][0] = randRowIdx;
                        wildPokeLoc[i][1] = randColIdx;
                    }

                }
            }
        }
        //cout << i << endl;
        //cout << "end of loop" << endl;
    }
}
void Game::printMap(Player aPlayer)
{
    for(int i = -3;i <= 3;i++) // rows
    {
        for(int j = -3;j <= 3;j++) // columns
        {
            // iterating through player row plus i.
            if(aPlayer.getRowIdx() + i  < 0 || aPlayer.getRowIdx() + i > 25) // if the row Index is out of bounds
            {
                
            }
            if(aPlayer.getColIdx() + i < 0 || aPlayer.getColIdx() + i > 16) // if the column idx is out of bounds
            {
                
            }
            else
            {
                if(i == 0 && j == 0)
                {
                    cout << '@';
                }
                else
                {
                    if(map[aPlayer.getRowIdx() + i][aPlayer.getColIdx() + j] == "w")
                    {
                        cout << '~';
                    }
                    else if(map[aPlayer.getRowIdx() + i][aPlayer.getColIdx() + j] == "p")
                    {
                        cout << '*';
                    }
                    else
                    {
                        cout << map[aPlayer.getRowIdx() + i][aPlayer.getColIdx() + j];
                    }
                }
            }
            // player.getRowIdx()
            // player.getColIdx()
        }
        cout << endl;
    }
}
void Game::beginningOfTurn(Player aPlayer)
{
    //cout << "Hello" << endl;
    for(int i = -3;i <= 3;i++) // rows
    {
        for(int j = -3;j <= 3;j++) // columns
        {
            // iterating through player row plus i.
            if(aPlayer.getRowIdx() + i  < 0 || aPlayer.getRowIdx() + i > 25) // if the row Index is out of bounds
            {
                
            }
            if(aPlayer.getColIdx() + i < 0 || aPlayer.getColIdx() + i > 16) // if the column idx is out of bounds
            {
                
            }
            else
            {
                if(i == 0 && j == 0)
                {
                    cout << '@';
                }
                else
                {
                    if(map[aPlayer.getRowIdx() + i][aPlayer.getColIdx() + j] == "w")
                    {
                        cout << '~';
                    }
                    else if(map[aPlayer.getRowIdx() + i][aPlayer.getColIdx() + j] == "p")
                    {
                        cout << '*';
                    }
                    else
                    {
                        cout << map[aPlayer.getRowIdx() + i][aPlayer.getColIdx() + j];
                    }
                }
            }
            // player.getRowIdx()
            // player.getColIdx()
        }
        cout << endl;
    }

    
    cout << "The sun is shining " + aPlayer.getName() + "! It's a beautiful day, we have " << aPlayer.getNumPokeballs() << " Pokeball(s) left and your Pokemon are stronk." << endl;
    cout << endl;
    cout << "Here are the stats of the current Pokemon in your party:" << endl;
    aPlayer.printPokemonInParty();
    cout << "Please choose from the following options: " << endl;
    cout << endl;
    cout << "1. Travel" << endl;
    cout << "2. Rest" << endl;
    cout << "3. Try your luck" << endl;
    cout << "4. Quit the game" << endl;
    
}
Pokemon Game::getPokeAt(int index)
{
    return allPokemon[index];
}

void Game::printFullMap()
{
    for(int i = 0;i < 25;i++) // 25 rows, 16 columns, prints out board.
    {
        for(int j = 0;j < 16;j++) // 16 columns
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}
void Game::travel(Player aPlayer)
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
            if(aPlayer.getRowIdx() - 1 < 0)
            {
                cout << "This location is out of bounds. Please choose a different direction to travel." << endl;
                cin.clear();
                cin >> travelDirection;
            }
            else if(map[aPlayer.getRowIdx() - 1][aPlayer.getColIdx()] == "w")
            {
                cout << "This location is water. Please choose a different direction to travel." << endl;
                cin.clear();
                cin >> travelDirection;
            }
            else
            {
                aPlayer.setLocation(aPlayer.getRowIdx() - 1,aPlayer.getColIdx());
                location = true;
                cout << aPlayer.getRowIdx() << endl;
                cout << aPlayer.getColIdx() << endl;
            }
        }
        else if(travelDirection == 2) // South                  
        {
            if(aPlayer.getRowIdx() + 1 >= 25)
            {
                cout << "This location is out of bounds. Please choose a different direction to travel." << endl;
                cin.clear();
                cin >> travelDirection;
            }
            else if(map[aPlayer.getRowIdx() + 1][aPlayer.getColIdx()] == "w")
            {
                cout << "This location is water. Please choose a different direction to travel." << endl;
                cin.clear();
                cin >> travelDirection;
            }
            else
            {
                aPlayer.setLocation(aPlayer.getRowIdx() + 1,aPlayer.getColIdx());
                location = true;
                cout << aPlayer.getRowIdx() << endl;
                cout << aPlayer.getColIdx() << endl;
            }   
        } 
        else if (travelDirection == 3) // East
        {
            if(aPlayer.getColIdx() + 1 >= 16)
            {
                cout << "This location is out of bounds. Please choose a different direction to travel." << endl;
                cin.clear();
                cin >> travelDirection;
            }
            else if(map[aPlayer.getRowIdx()][aPlayer.getColIdx() + 1] == "w")
            {
                cout << "This location is water. Please choose a different direction to travel." << endl;
                cin.clear();
                cin >> travelDirection;
            }
            else
            {
                aPlayer.setLocation(aPlayer.getRowIdx(),aPlayer.getColIdx() + 1);
                location = true;
                cout << aPlayer.getRowIdx() << endl;
                cout << aPlayer.getColIdx() << endl;
            } 
        }
        else if(travelDirection == 4) // West
        {
            if(aPlayer.getColIdx() - 1 < 0)
            {
                cout << "This location is out of bounds. Please choose a different direction to travel." << endl;
                cin.clear();
                cin >> travelDirection;
            }
            else if(map[aPlayer.getRowIdx()][aPlayer.getColIdx() - 1] == "w")
            {
                cout << "This location is water. Please choose a different direction to travel." << endl;
                cin.clear();
                cin >> travelDirection;
            }
            else
            {
                aPlayer.setLocation(aPlayer.getRowIdx(),aPlayer.getColIdx() - 1);
                location = true;
                // cout << player.getRowIdx() << endl;
                // cout << player.getColIdx() << endl;
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
}
void Game::encounter(Player aPlayer)
{
    vector <int> wildPokeIdxAlreadyFaught;
    if(map[aPlayer.getRowIdx()][aPlayer.getColIdx()] != "G" && map[aPlayer.getRowIdx()][aPlayer.getColIdx()] != "C")
    {
        bool encounter = false;
        int wildPokeIdxToBattle;
        for(int i = 0;i < 20;i++)
        {
            if(wildPokeLoc[i][0] >= aPlayer.getRowIdx() - 2 && wildPokeLoc[i][0] <= aPlayer.getRowIdx() + 2 && wildPokeLoc[i][1] >= aPlayer.getColIdx() - 2 && wildPokeLoc[i][1] <= aPlayer.getColIdx() + 2)
            {
                wildPokeIdxToBattle = i; // wild pokemon in vacinity
                bool newPoke = false; // now check if that pokemon is not one that the player has encountered
                if(wildPokeIdxAlreadyFaught.size() > 0)
                {
                    for(int j = 0;j < wildPokeIdxAlreadyFaught.size();j++)
                    {
                        if(wildPokeIdxAlreadyFaught[j] == wildPokeIdxToBattle)
                        {
                            
                        }
                        else
                        {
                            newPoke = true;
                        }
                    }
                    if(newPoke == true)
                    {
                        encounter = true;
                        wildPokeIdxAlreadyFaught.push_back(wildPokeIdxToBattle);
                    }
                    else
                    {
                        
                    }
                    // should i add a vector
                }
                else
                {
                    encounter = true;
                    wildPokeIdxAlreadyFaught.push_back(wildPokeIdxToBattle);
                }
                
            }
        }
        if(encounter == true) // wild encounter below
        {
            int numWildFleeAttempts = 0;
            aPlayer.addWildEncounter();
            //Encounter encounter = Encounter();
            wildPokemon[wildPokeIdxToBattle]; // wild pokemon in vacinity
            cout << "You ran into a wild " << wildPokemon[wildPokeIdxToBattle].getName() << "!" << endl;
            wildPokemon[wildPokeIdxToBattle].getStats();
            // wildPokemon[wildPokeIdxToBattle].getHPBar();
            cout << "Your ACTIVE Pokemon is: " << endl;
            aPlayer.getActivePokemon().getStats();
            int battleDecision;
            cout << "What do you want to do (oick 1, 2, or 3):" << endl;
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
                    if(aPlayer.getNumWildEncounters() == 1 || aPlayer.getNumWildEncounters() == 2) 
                    {
                        aPlayer.addPokemon(wildPokemon[wildPokeIdxToBattle]);
                        isBattleOver = true;
                    }
                    else
                    {
                        willPokemonFight = ((rand() % 10) + 1);
                        if(willPokemonFight >= 1 && willPokemonFight <= 6) // wild pokemon fights
                        {
                            // fight sequence
                            cout << "fight!" << endl;
                            //if(player.)
                            
                        }
                        else // wild pokemon attempts to flee
                        {
                            numWildFleeAttempts++;
                            // compute flee shit here
                            int F = ((wildPokemon[wildPokeIdxToBattle].getSpeed() * 32) / ((double)((aPlayer.getActivePokemon().getSpeed() / 4) % 256 + 30) * numWildFleeAttempts));
                            if(F > 255) // wild pokemon flees successfully
                            {
                                isBattleOver = true;
                            }
                            else
                            {
                                if(rand() % 256 < F)
                                {
                                    // randomize location.
                                    isBattleOver = true; // wild pokemon escapes
                                }
                                else 
                                {
                                    aPlayer.addPokemon(wildPokemon[wildPokeIdxToBattle]);
                                    isBattleOver = true; // wild pokemon escape fails
                                }
                            }
                        }
                    }
                }
                else if(battleDecision == 2) // Switch Active Pokemon
                {
                    
                }
                else if(battleDecision == 3) // Run
                {
                    
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
    
    else if(map[aPlayer.getRowIdx()][aPlayer.getColIdx()] == "C") // Pokemon Center procedure
    {
        cout << "Pokemon center procedure" << endl;
    }
}
void Game::trainerBattle(Player aPlayer)
{
    if(map[aPlayer.getRowIdx()][aPlayer.getColIdx()] == "G") // Trainer battle
    {
        cout << "Trainer battle" << endl;
        
    }
}
// bool Game::endOfTurn(Player aPlayer)
// {
//     cout << "Check if player won, randomize wild poke locations..whatever else" << endl;
//     if(aPlayer.getNumBadges() >= 6 || aPlayer.getNumTypes)
// }
void Game::printWildPokeLocs(Player aPlayer)
{
    for(int i = 0;i < 20;i++)
    {
        cout << wildPokeLoc[i][0] << ' ' << wildPokeLoc[i][1] << endl;
    }
}