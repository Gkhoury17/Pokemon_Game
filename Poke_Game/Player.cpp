#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include <algorithm>
//#include "Pokemon.h"

using namespace std;

Player::Player()
{
    cout << "Creating player..." << endl;
    numPokemon = 0;
    numBadges = 0;
    numPoints = 0;
    numPokeballs = 10;
    numWildEncounters = 0;
    name = "";
    rowIndex = 0;
    columnIndex = 0;
    numTrainersFaught = 0;
    vector<Pokemon> totalPokemon;
    vector<Pokemon> suite;
}
int Player::getNumPokeballs()
{
    return numPokeballs;
}
int Player::getNumPoints()
{
    return numPoints;
}
int Player::getNumBadges()
{
    return numBadges;
}
int Player::getNumWildEncounters()
{
    return numWildEncounters;
}
int Player::getRowIdx()
{
    return rowIndex;
}
int Player::getColIdx()
{
    return columnIndex;
}
string Player::getName()
{
    return name;
}
void Player::printPokemonInParty()
{
    //cout << "Suite size: " << suite.size() << endl;
    for(int i = 0;i < suite.size();i++)
    {
        suite[i].getStats();
        cout << endl;
    }
    
}
Pokemon Player::getActivePokemon()
{
    return suite[0];
    // for(int i = 0;i < suite.size();i++)
    // {
    //     if(suite[i].getliveHP() > 0)
    //     {
    //         return suite[i];
    //     }
        
    // }
    
}

void Player::addWildEncounter()
{
    numWildEncounters++;
    
}
void Player::setLocation(int newRowIndex, int newColumnIndex)
{
    rowIndex = newRowIndex;
    columnIndex = newColumnIndex;
}
void Player::setName(string newName)
{
    name = newName;
}
void Player::addPokemon(Pokemon pokemon)
{
    if(types.size() > 0) // if player has 1 or more types
    {
        bool isNewType1 = false;
        bool isNewType2 = false;
        for(int i = 0;i < types.size();i++) //iterating through types of pokemon the player has
        {
            if(pokemon.getType1() != types[i]) //
            {
                isNewType1 = true;
            }
            if(pokemon.getType2() != "")
            {
                if(pokemon.getType2() != types[i])
                {
                    isNewType2 = true;
                }
            }
        }
        if(isNewType1 == true)
        {
            types.push_back(pokemon.getType1());
        }
        if(isNewType2 == true)
        {
            types.push_back(pokemon.getType2());
        }
    }
    else
    {
        types.push_back(pokemon.getType1());
        if(pokemon.getType2() != "")
        {
            types.push_back(pokemon.getType2());
        }
    }
    if(numPokemon >= 6)
    {
        cout << "Your party is full, " << pokemon.getName() << " was added to your Pokedex." << endl;
        totalPokemon.push_back(pokemon);
        numPokemon++;
    }
    else
    {
        cout << pokemon.getName() << " was added to your party!" << endl;
        suite.push_back(pokemon);
        totalPokemon.push_back(pokemon);
        numPokemon++;
    }
}
void Player::defeatTrainer()// should this take in trainer and player objects?
{
    // add all of trainers pokemon to players pokemon
    numBadges++;
    numPokeballs = numPokeballs + 5;
    numPoints = numPoints + 60;
    //player cant battle same trainer twice.
}
void Player::caughtWildPokemon()
{
    numPoints = numPoints + 10;
    numPokeballs = numPokeballs - 1;
}
void Player::rest()
{
    numPokeballs = numPokeballs - 1;
    for(int i = 0;i < suite.size();i++) // iterating through players party
    {
        if(suite[i].getliveHP() + 1 <= suite[i].getHP())
        {
            suite[i].setliveHP(suite[i].getliveHP() + 1);
        }
    }
}
bool Player::didPlayerWin()
{
    vector<string>typesUniq;
    for(int i = 0;i < totalPokemon.size();i++) // iterating through each pokemon
    {
        int matches1 = 0;
        int matches2 = 0;
        for(int j = 0;j < typesUniq.size();j++)
        {
            if(totalPokemon[i].getType1() == typesUniq[j])
            {
                matches1++;
            }
            if(totalPokemon[i].getType2() == typesUniq[j] && totalPokemon[i].getType2() != "")
            {
                matches2++;
            }
        }
        if(matches1 == 0)
        {
            typesUniq.push_back(totalPokemon[i].getType1());
        }
        if(matches2 == 0)
        {
            if(totalPokemon[i].getType2() != "")
            {
                typesUniq.push_back(totalPokemon[i].getType2());
            }
        }
        
    }
    for(int i = 0;i < typesUniq.size();i++)
    {
        cout << typesUniq[i] << endl;
    }
    if(typesUniq.size() >= 8)
    {
        cout << "You won!" << endl;
        cout << "You had 8 or more different types of pokemon." << endl;
        return true;
    }
    if(numBadges >= 6)
    {
        cout << "You won!" << endl;
        cout << "You had 6 or more badges" << endl;
        return true;
    }
    

    return false;
}
void Player::printTypesVector()
{
    for(int i = 0;i < types.size();i++)
    {
        cout << types[i] << endl;
    }
}
void Player::switchActivePokemon()
{
    if(suite.size() < 2)
    {
        cout << "You have no other pookemon" << endl;
    }
    else
    {
        int pokeIdx;
        cout << "Pick another active pokemon:" << endl;
        for(int i = 0;i < suite.size();i++)
        {
            cout << to_string(i + 1) << ". " << suite[i].getName() << endl;
        }
        cin >> pokeIdx;
        while(pokeIdx < 1 || pokeIdx > suite.size())
        {
            cout << "Invalid input." << endl;
            cin.clear();
            cin >> pokeIdx;
        }
        Pokemon pokemon = Pokemon();
        pokemon = suite[0];
        suite[0] = suite[pokeIdx - 1];
        suite[pokeIdx - 1] = pokemon;
    }
}
void Player::addPokeballs(int numBalls)
{
    numPokeballs = numPokeballs + numBalls;
}
// start thinking about live HP
void Player::printPokemonNamesInParty()
{
    for(int i = 0;i < suite.size();i++)
    {
        cout << i + 1 << '.' << suite[i].getName() << endl;
    }
}
int Player::getSuiteSize()
{
    return suite.size();
}
void Player::removePokemon(int index)
{
    suite.erase(suite.begin() + index);
    totalPokemon.erase(totalPokemon.begin() + index);
    numPokemon--;
}
string Player::getNamePokeIdx(int index)
{
    return suite[index].getName();
}
void Player::pokeCenter()
{
    for(int i = 0;i < suite.size();i++)
    {
        suite[i].restoreHP();
    }
    char yesOrNo;
    cout << "Welcome to the Pokémon Center. All Pokémon in your party have been healed. Do you want to change the members of your party (Y/N):" << endl;
    cin >> yesOrNo;
    if(yesOrNo == 'Y' || yesOrNo == 'y')
    {
        cout << "Here are all the Pokémon in your Pokédex. Choose at most 6 numbers, followed by Q for quit:" << endl;
        for(int i = 0;i < totalPokemon.size();i++)
        {
            cout << i + 1 << ". " << totalPokemon[i].getName() << endl;
        }
        for(int i = 0;i < suite.size();i++)
        {
            cout << "Pick your number " << to_string(i + 1) << " pokemon:" << endl;
            int pokeNum;
            cin >> pokeNum;
            Pokemon copiedPoke = Pokemon();
            copiedPoke = suite[i];
            suite[i] = totalPokemon[pokeNum - 1];
        }
        
    }
    
    
}
Pokemon Player::getPokeFromSuite(int index)
{
    return suite[index];
}
void Player::addWildPokeFaught(int index)
{
    idxOfWildPokeFaught.push_back(index);
}
bool Player::checkIfPokeIsNew(int index)
{
    bool isit = true;
    for(int i = 0;i < idxOfWildPokeFaught.size();i++)
    {
        if(idxOfWildPokeFaught[i] == index)
        {
            isit = false;
        }
    }
    return isit;
}
void Player::nearestPokeCenter(int pokeCenterLocs[][2])
{
    int pokeCenter;
    
    double nearestDifference;
    for(int i = 0;i < 15;i++)
    {
        
        int rowDifference;
        int colDifference;
        rowDifference = abs((rowIndex - pokeCenterLocs[i][0]));
        colDifference = abs((columnIndex - pokeCenterLocs[i][1]));
        double avgDistance = (rowDifference + colDifference) / 2;
        if(i == 0)
        {
            nearestDifference = avgDistance;
        }
        else if(avgDistance < nearestDifference)
        {
            nearestDifference = avgDistance;
            pokeCenter = i;
        }
    }
    rowIndex = pokeCenterLocs[pokeCenter][0];
    columnIndex = pokeCenterLocs[pokeCenter][1];
    cout << "You have been teleported to the nearest PokeCenter" << endl;
}
bool Player::allPokeFainted()
{
    for(int i = 0;i < suite.size();i++)
    {
        if(suite[i].getliveHP() > 0)
        {
            return false;
        }
    }
    return true;
}
void Player::makePokeActive()
{
    Pokemon pokemon = Pokemon(suite[0].getName(), suite[0].getHP(),suite[0].getAttack(), suite[0].getDefense(),suite[0].getSpeed(),suite[0].getMax(),suite[0].getType1(),suite[0].getType2());
    pokemon.setliveHP(suite[0].getliveHP());
    
    suite[0] = suite[suite.size() - 1];
    suite[suite.size() - 1] = pokemon;
}
int Player::getNumPokemon()
{
    return numPokemon;
}
void Player::tryLuck()
{
    
}
void Player::addTrainerFaught()
{
    numTrainersFaught++;
}
int Player::getTrainersFaught()
{
    return numTrainersFaught;
}
void Player::updatePoke(Pokemon pokemon, int idx)
{
    for(int i = 0;i < suite.size();i++)
    {
        if(i == idx)
        {
            suite[i] = pokemon;
        }
    }

}