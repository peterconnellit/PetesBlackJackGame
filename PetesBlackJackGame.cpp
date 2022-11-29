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
//Defines Access (attributes and methods), all can be accessed and modified from outside the Card class
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
    We do not want to create a new card, so we use pointers to reference existing cards on the heap*/
    void Add(Card* pCard);

    //Clear PlayerHand of all cards
    void Clear();

    //Get PlayerHand total value of cards, Ace is treated as 1 or 11 based on other cards in PlayerHand
    int GetHandTotal() const;

/*Vector with pointer is inaccessible outside the class, but can be accessed by any subclass.
Vectors are dynamic and can resize when an element is inserted or deleted.
Advantages = can insert cards easily and can store multiple objects (in our case card pointers)
Disadvantages = Memory consumption is more (Non-contiguous) and data is not indexed (Array's are).
https://www.mygreatlearning.com/blog/vectors-in-c/#:~:text=Vectors%20in%20C%2B%2B%20are%20sequence,regular%20pointers%20to%20its%20elements.
Memory management will be rectified later on.
Vector works well for our small program.*/
protected:
    vector<Card*> m_HandCards;
};

PlayerHand::PlayerHand()
{
    //Ensure capacity is enough to contain cards
    m_HandCards.reserve(7);
}

PlayerHand::~PlayerHand()
{
    Clear();
}

void PlayerHand::Add(Card* pCard)
{
    //Push adds new card to vector from back
    m_HandCards.push_back(pCard);
}

/*Vector memory management*/
void PlayerHand::Clear()
{
    //Free memory on heap by iterating through vector
    vector<Card*>::iterator cardIter = m_HandCards.begin();
    for(cardIter = m_HandCards.begin(); cardIter !=m_HandCards.end(); ++cardIter)
    {
        delete* cardIter;
        *cardIter = 0;
    }
    //Clears vector of pointers
    m_HandCards.clear();
}















int main()
{
    std::cout << "Hello World!\n";
}


