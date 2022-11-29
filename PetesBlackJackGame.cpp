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

    Card(cardRanks r = Ace, cardSuits s = Spades, bool ifu = true);

    //GetCardValue returns the value of a card
    int GetCardValue() const;

    //FlipCard() flips card face up or down depending on state
    void FlipCard();

private:
    cardRanks m_CardRanks;
    cardSuits m_CardSuits;
    bool m_IsCardFaceUp;
};















int main()
{
    std::cout << "Hello World!\n";
}


