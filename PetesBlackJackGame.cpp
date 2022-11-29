// PetesBlackJackGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

//CARD CLASS
class Card
{
public:
    //Define emmumerations to 1.make code more readible and 2. limit values of m_ data members
    enum cardRanks {Ace=1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};

    enum cardSuits {Clubs, Diamonds, Hearts, Spades};

    /*We can use overloading to send Card object to standard output operator <<
    so we can display card object on screen*/
    friend ostream& operator << (ostream& os, const Card& aCard);

    Card(cardRanks r = Ace, cardSuits s = Spades, bool ifu = true);

    //GetCardValue returns the value of a card 1 to 11 (Ace value = 1 or 11)
    int GetCardValue() const;

    //FlipCard() flips card face up or down depending on state
    void FlipCard();

private:
    cardRanks m_CardRanks;
    cardSuits m_CardSuits;
    bool m_IsCardFaceUp;
};

//Scope resolution operator used to reference identifiers
Card::Card(cardRanks r, cardSuits s, bool ifu) : m_CardRanks(r), m_CardSuits(s), m_IsCardFaceUp(ifu) {}

int Card::GetCardValue() const
{
    //Card face down value = 0
    int cardValue = 0;

    //Nested loops
    if (m_IsCardFaceUp)
    {
        //Card is actual value
        cardValue = m_CardRanks;
    }
}













int main()
{
    std::cout << "Hello World!\n";
}


