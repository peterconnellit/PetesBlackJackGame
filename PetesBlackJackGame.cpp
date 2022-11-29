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
//Defines Access (attributes and methods), all can be accessed and modified from outside the Card class code
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

    //Nested loop for card values
    if (m_IsCardFaceUp){
        //Card is actual value
        cardValue = m_CardRanks;
        //Set Jack, Queen and King Face card values to 10
        if (cardValue > 10) {
            cardValue = 10;
        }
    }
    return cardValue;
}

void Card::FlipCard()
{
    m_IsCardFaceUp = !(m_IsCardFaceUp);
}


//PLAYER HAND CLASS
class PlayerHand 
{
public:
    PlayerHand();

    /*Virtual functions ensure that the correct function is called for an object,
    regardless of the type of reference(or pointer) used for function call.
    They are mainly used to achieve Runtime polymorphism
    Functions are declared with a virtual keyword in base class.
    The resolving of function call is done at runtime.
    https://www.geeksforgeeks.org/virtual-function-cpp/ */
    virtual ~PlayerHand();

    /*Add card to the PlayerHand using pointers.
    We do not want to create a new card, so we use pointers to reference existing card*/
    void Add(Card* pCard);

    //Clear PlayerHand of all cards
    void Clear();

    //Get PlayerHand total value of cards, Ace is treated as 1 or 11 based on other cards in PlayerHand
    int GetHandTotal() const;

//vector with pointer is inaccessible outside the class, but can be accessed by any subclasses
protected:
    vector<Card*> m_Cards;
};

















int main()
{
    std::cout << "Hello World!\n";
}


