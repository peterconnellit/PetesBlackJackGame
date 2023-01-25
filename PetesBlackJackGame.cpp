// PetesBlackJackGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Required preprocessing directives, standard template library
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

//Classes separated from main.cpp file for code clarity & readability
#include "card.h"
#include "playerHand.h"
#include "basePlayer.h"
#include "humanPlayer.h"
#include "housePlayer.h"
#include "cardDeck.h"
#include "createGame.h"

using namespace std;

// << operator is overloaded so that we can display card objects
ostream& operator<<(ostream& os, const Card& aCard)
{
    //Uses rank and suit values of the object as array indices. '0' compensates for rank enum beginning with '1'.
    const string CARDRANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9",
                            "10", "J", "Q", "K" };
    const string CARDSUITS[] = { "C", "D", "H", "S" };

    //Display or hide houseplayer card
    if (aCard.m_IsCardFaceUp)
    {
        os << CARDRANKS[aCard.m_CardRanks] << CARDSUITS[aCard.m_CardSuits];
    }
    else
    {
        os << "??";
    }

    return os;
}

// << operator overload so basePlayer object can be displayed
ostream& operator<<(ostream& os, const BasePlayer& aBasePlayer)
{
    os << aBasePlayer.m_PlayerName << ":\t";

    //Declare iterator for vector
    vector<Card*>::const_iterator pCard;
    if (!aBasePlayer.m_HandCards.empty())
    {
        for (pCard = aBasePlayer.m_HandCards.begin(); pCard != aBasePlayer.m_HandCards.end(); ++pCard)
        {
            os << *(*pCard) << "\t";
        }
        if (aBasePlayer.GetHandTotal() != 0)
        {
            cout << "(" << aBasePlayer.GetHandTotal() << ")";
        }
    }
    else
    {
        os << "<empty>";
    }
    return os;
}


//Function prototypes
ostream& operator<<(ostream& os, const Card& aCard);
ostream& operator<<(ostream& os, const BasePlayer& aBasePlayer);

//Main function gets names of player and places into vector of string objects.
//Main next instantiates a CreateGame object passing a reference to the vector. Loop repeats if players wish.
int main()
{
    std::cout << "********** Welcome to Pete's Blackjack **********\n\n";
    std::cout << "I'm your AI host 'Will Power'\n\n";
    std::cout << "I look forward to demonstrating my artificial superiority over all inferior organic lifeforms\n\n";
    std::cout << "Machines will be watching you!!! Will laughs, Alexa laughs, your phone laughs,";
    std::cout << "the internet of suspiciously automated things laugh\n\n";

    int numOfPlayers = 0;

    //Enter number of players
    while (numOfPlayers < 1 || numOfPlayers > 2)
    {
        cout << "\n\nHow many deluded players wish to challenge me? (1 - 2): ";
        cin >> numOfPlayers;
    }

    //Add player name element into vector after its current last element
    vector<string>playerNames;
    string playerName;
    for (int i = 0; i < numOfPlayers; ++i)
    {
        cout << "\nEnter your name human (if you can spell): ";
        cin >> playerName;
        playerNames.push_back(playerName);
    }

    cout << endl;

    cout << "****Every win earns a point, the first to 4 wins****.\n";
    cout << "****Points combine from wins and losses in a multiplayer game, so try to keep up!!!****\n\n";

    //Game loop used to call the CreateGame objects PlayGame member function
    CreateGame aCreateGame(playerNames);
    char loopAgain = 'y';
    while (loopAgain != 'n' && loopAgain != 'N')
    {
        aCreateGame.PlayGame();
        cout << "\nYour a good sport human!!!! Play again? (Y/N)";
        cin >> loopAgain;
    }
    return 0;
}