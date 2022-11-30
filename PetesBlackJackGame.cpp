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
    if (m_IsCardFaceUp)
    {
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
    regardless of the type of reference (or pointer) used for function call.
    They are mainly used to achieve Runtime polymorphism
    Functions are declared with a virtual keyword in base class.
    The resolving of function call is done at runtime.
    https://www.geeksforgeeks.org/virtual-function-cpp/ */
    virtual ~PlayerHand();

    /*Add card to the PlayerHand using pointers.
    We do not want to create a new card, so we use pointers to reference existing cards on the heap*/
    void Add(Card* pCard);

    //Clear PlayerHand of all cards by removing pointers from vector, also destroys card from heap (freeing occupied memory).
    void Clear();

    //Get PlayerHand total value of cards, Ace is treated as 1 or 11 based on other cards in PlayerHand
    int GetHandTotal() const;

/*Vector with pointer is inaccessible outside the class, but can be accessed by any subclass.
Vectors are dynamic and can resize when an element is inserted or deleted.
Advantages = can insert cards easily and can store multiple objects (in our case card pointers)
Disadvantages = Memory consumption is more (Non-contiguous) and data is not indexed (unlike Array's).
https://www.mygreatlearning.com/blog/vectors-in-c/#:~:text=Vectors%20in%20C%2B%2B%20are%20sequence,regular%20pointers%20to%20its%20elements.
Memory management will be rectified with Clear().
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

//Pointer to card
void PlayerHand::Add(Card* pCard)
{
    //Push adds new card to vector from back
    m_HandCards.push_back(pCard);
}

//Vector memory management//
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

int PlayerHand::GetHandTotal() const
{
    //If PlayerHand has no cards, return 0
    if (m_HandCards.empty())
    {
        return 0;
    }

    //If first card is face down, card value = 0, so return 0.
    if (m_HandCards[0]->GetCardValue() == 0)
    {
        return 0;
    }

    //Add card values, treat Ace as 1. Pointers used again
    int handTotal = 0;
    vector<Card*>::const_iterator cardIter;
    for (cardIter = m_HandCards.begin(); cardIter != m_HandCards.end(); ++cardIter)
    {
        handTotal += (*cardIter)->GetCardValue();
    }

    //If PlayerHand already has Ace
    bool hasAce = false;
    for (cardIter = m_HandCards.begin(); cardIter != m_HandCards.end(); ++cardIter)
    {
        if ((*cardIter)->GetCardValue() == Card::Ace) {
            hasAce = true;
        }
    }

    //Treat Ace as 11 if PlayerHand is low enough for it
    if (hasAce && handTotal <= 11)
    {
        //Add 10 (Ace already has a value of 1)
        handTotal += 10;
    }

    return handTotal;
}


//BASE PLAYER CLASS
//Common elements for both human and computer players to inherit
class BasePlayer : public PlayerHand
{
    /*Overloaded friend << operator can now display BasePlayer objects on screen.
    References to BasePlayer are accepted, and as a result so are Player and House objects*/
    friend ostream& operator << (ostream& os, const BasePlayer& aBasePlayer);

public:
    //A string object is accepted for the name of the BasePlayer
    BasePlayer(const string& playerName = "");

    //Destructor inherits virtual trait from PlayerHand
    virtual ~BasePlayer();

    /*Does player want to continue to hit.
    Function has no meaning for BasePlayer class, becomes purely virtual meaning abstract.
    Both player and house will require their own implimentation.*/
    virtual bool PlayerHit() const = 0;

    //If player has total greater than 21, returns bust. Applies to all human players and also House
    bool PlayerBusted() const;

    //Notify players or House of bust. Applies to all and so definition of the member function can go in this class
    void HasBust() const;

protected:
    string m_PlayerName;
};

BasePlayer::BasePlayer(const string& playerName) :
    m_PlayerName(playerName)
{}

BasePlayer::~BasePlayer()
{}

bool BasePlayer::PlayerBusted()const
{
    return (GetHandTotal() > 21);
}

void BasePlayer::HasBust() const
{
    cout << "O dear " << m_PlayerName << " has bust....\n";
    cout << "If at first you dont succeed, It's probably never going to happen!!!\n\n";
}


//HUMAN PLAYER CLASS
//Derived from BasePlayer class
class HumanPlayer : public BasePlayer
{
public:
    HumanPlayer(const string& playerName = "");

    virtual ~HumanPlayer();

    //Does player want to continue to hit. Inherited from BasePlayer class
    virtual bool PlayerHit() const;

    //Player wins
    void PlayerWins() const;

    //Player loses
    void PlayerLoses() const;

    //Player pushes
    void PlayerPushes() const;
};

HumanPlayer::HumanPlayer(const string& playerName) :
    BasePlayer(playerName)
{}
HumanPlayer::~HumanPlayer()
{}

bool HumanPlayer::PlayerHit() const
{
    cout << m_PlayerName << ", everyone has the right to be stupid...do you want a hit? (Y/N):";
    char answer;
    cin >> answer;
    return (answer == 'y' || answer == 'Y');
}

//Outputs to player decisions 
void HumanPlayer::PlayerWins() const
{
    cout << m_PlayerName << "You win.... ya filthy animal!!!\n\n";
}

void HumanPlayer::PlayerLoses() const
{
    cout << m_PlayerName << " loses. Machine (not) learning anything here!!!\n\n";
}

void HumanPlayer::PlayerPushes() const
{
    cout << m_PlayerName << " pushes.\n\n";
}


//HOUSEPLAYER CLASS
//Represents cpu AI opponent = Will Power. Derived from BasePlayer class
class HousePlayer : public BasePlayer
{
public:
    HousePlayer(const string& playerName = "AI Opponent = Will Power");

    virtual ~HousePlayer();

    //HousePlayer hitting (hits on 15 or less)
    virtual bool PlayerHit() const;

    //Hides First card at beginning of game and reveals after all players have settled on cards taken
    void HideFirstCard();
};

HousePlayer::HousePlayer(const string& playerName) :
    BasePlayer(playerName)
{}

HousePlayer::~HousePlayer()
{}

bool HousePlayer::PlayerHit() const
{
    return (GetHandTotal() <= 15);
}

void HousePlayer::HideFirstCard()
{
    if (!(m_HandCards.empty()))
    {
        m_HandCards[0]->FlipCard();
    } 
    else {
        cout << "There is no card to flip!\n";
    }
}


//CARD DECK CLASS
//Represents a deck of cards (derived from PlayerHand class)
class CardDeck : public PlayerHand
{
public:
    CardDeck();

    virtual ~CardDeck();

    //Here we create deck of 52 cards
    void PopulateDeck();

    //Shuffle deck
    void ShuffleDeck();

    //Deal single card
    void DealCard(PlayerHand& aPlayerHand);

    //Give additional cards to BasePlayer
    void SpareCards(BasePlayer& aBasePlayer);
};

CardDeck::CardDeck()
{
    m_HandCards.reserve(52);
    PopulateDeck();
}

CardDeck::~CardDeck()
{}

void CardDeck::PopulateDeck()
{
    Clear();

    //Create deck of cards (pre increment through cardsuits enum)
    for (int s = Card::Clubs; s <= Card::Spades; ++s)
    {
        //Creates each card rank for each suit (Static_cast converts enums into integers)
        for (int r = Card::Ace; r <= Card::King; ++r) {
            Add(new Card(static_cast<Card::cardRanks>(r), static_cast<Card::cardSuits>(s)));
        }
    }
}

void CardDeck::ShuffleDeck()
{
    /*Uses built-in random generator from <algorithm> Standard Template Library
    https://learn.microsoft.com/en-us/troubleshoot/developer/visualstudio/cpp/libraries/use-random-shuffle-stl */
    random_shuffle(m_HandCards.begin(), m_HandCards.end());
}

/* & denotes a reference instead of a pointer to an object
https://stackoverflow.com/questions/1943276/what-does-do-in-a-c-declaration
A reference variable does not consume any extra memory.
It has the same memory address as the variable it refers to.
A pointer needs extra space for itself.
https://www.codespeedy.com/advantages-of-reference-variables-over-pointer-variables-in-cpp/ 
References and pointers have both been used in program as each have advantages, 
also used for the purposes of demonstration */
void CardDeck::DealCard(PlayerHand& aPlayerHand)
{
    if (!m_HandCards.empty())
    {
        aPlayerHand.Add(m_HandCards.back());
        m_HandCards.pop_back();
    }
    else {
        cout << "You need a break, and i'm out of cards.\n\n";
    }
}












int main()
{
    std::cout << "Hello World!\n";
}


