// PetesBlackJackGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Card
{
public:
    enum cardRanks {Ace=1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};

    enum cardSuits {Clubs, Diamonds, Hearts, Spades};

    //We can use overloading to send Card object to standard output operator <<
    friend ostream& operator << (ostream& os, const Card& aCard);






};













int main()
{
    std::cout << "Hello World!\n";
}


