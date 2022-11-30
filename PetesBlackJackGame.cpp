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

//Encapsulation = access is limited to the scope of the class https://www.atatus.com/glossary/encapsulation/ 
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
    References to BasePlayer are accepted, and as a result so are HumanPlayer and HousePlayer objects*/
    friend ostream& operator << (ostream& os, const BasePlayer& aBasePlayer);

public:
    //A string object is accepted for the name of the BasePlayer
    BasePlayer(const string& playerName = "");

    //Destructor inherits virtual trait from PlayerHand
    virtual ~BasePlayer();

    /*Does player want to continue to hit.
    Function has no meaning for BasePlayer class, becomes purely virtual meaning abstract.
    Both player and house will require their own implimentation.
    Example of Abstraction*/
    virtual bool PlayerHit() const = 0;

    //If player has total greater than 21, returns bust. Applies to all human players and also House
    bool PlayerBusted() const;

    //Notify players or House of bust. Applies to all and so definition of the member function can go in this class
    void HasBust() const;

//Encapsulation
protected:
    string m_PlayerName;
};

BasePlayer::BasePlayer(const string& playerName) :
    m_PlayerName(playerName)
{}

BasePlayer::~BasePlayer()
{}

bool BasePlayer::PlayerBusted() const
{
    return (GetHandTotal() > 21);
}

void BasePlayer::HasBust() const
{
    cout << "\nO dear " << m_PlayerName << " has bust....\n";
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
    cout << m_PlayerName << " you win.... ya filthy animal!!!\n\n";
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
//Represents AI opponent = Will Power. Derived from BasePlayer class
class HousePlayer : public BasePlayer
{
public:
    HousePlayer(const string& playerName = "Will");

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
        /*Creates each card rank for each suit.
        Static_cast converts loop int variables to enums defined in Card*/
        for (int r = Card::Ace; r <= Card::King; ++r) {
            Add(new Card(static_cast<Card::cardRanks>(r), static_cast<Card::cardSuits>(s)));
        }
    }
}

void CardDeck::ShuffleDeck()
{
    /*Uses built-in random generator from the Standard Template Library <algorithm> header file.
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
also used for the purposes of demonstration.
Deal() accepts reference to HandCards object so we can use polymorphism on HumanPlayer and HousePlayer objects
and call Add() member function without knowing which object exactly*/
void CardDeck::DealCard(PlayerHand& aPlayerHand)
{
    if (!m_HandCards.empty())
    {
        aPlayerHand.Add(m_HandCards.back());
        m_HandCards.pop_back();
    }
    else {
        cout << "You need a break... and i'm out of cards!!!\n\n";
    }
}

/*Polymorphism = SpareCards() gives cards to BasePlayer object and accepts reference to both HumanPlayer and
HousePlayer. Can call PlayerBusted() and PlayerHit() without knowing the objects type*/
void CardDeck::SpareCards(BasePlayer& aBasePlayer)
{
    cout << endl;
    //Deal cards as long as player wants a hit and isn't already bust
    while (!(aBasePlayer.PlayerBusted()) && aBasePlayer.PlayerHit())
    {
        DealCard(aBasePlayer);
        cout << aBasePlayer << endl;

        if (aBasePlayer.PlayerBusted()) {
            aBasePlayer.HasBust();
        }
    }
}


//CREATEGAME CLASS
//Represents a game of PetesBlackJack

class CreateGame
{
public:
    CreateGame(const vector<string>& PlayerNames);

    ~CreateGame();

    //Launch game
    void PlayGame();

private:
    CardDeck m_CardDeck;
    HousePlayer m_HousePlayer;
    vector<HumanPlayer> m_HumanPlayers;
};

/*Class constructor accepts reference to a vector of string objects(Player names)
The class constructor instantiates a player object with each name.*/
CreateGame::CreateGame(const vector<string>& PlayerNames)
{
    //Create vector of players from vector of player names
    vector<string>::const_iterator pPlayerName;
    for (pPlayerName = PlayerNames.begin(); pPlayerName != PlayerNames.end(); ++pPlayerName)
    {
        m_HumanPlayers.push_back(HumanPlayer(*pPlayerName));
    }

    //Seeds random number generator then populates and shuffles deck
    srand(static_cast<unsigned int>(time(0)));
    m_CardDeck.PopulateDeck();
    m_CardDeck.ShuffleDeck();
}

CreateGame::~CreateGame()
{}

//Implimentation of game play pseudocode
void CreateGame::PlayGame()
{
    //Deals 2 cards to each player using pointers and nested for loops for HumanPlayers
    vector<HumanPlayer>::iterator pHumanPlayer;
    for (int i = 0; i < 2; ++i)
    {
        for (pHumanPlayer = m_HumanPlayers.begin(); pHumanPlayer != m_HumanPlayers.end(); ++pHumanPlayer) {
            m_CardDeck.DealCard(*pHumanPlayer);
        }
        m_CardDeck.DealCard(m_HousePlayer);
    }

    //Hide HousePlayer's First card
    m_HousePlayer.HideFirstCard();

    //Show hand of all players
    for (pHumanPlayer = m_HumanPlayers.begin(); pHumanPlayer != m_HumanPlayers.end(); ++pHumanPlayer)
    {
        cout << *pHumanPlayer << endl;
    }

    cout << m_HousePlayer << endl;

    //Deal additional cards to Humanplayers
    for (pHumanPlayer = m_HumanPlayers.begin(); pHumanPlayer != m_HumanPlayers.end(); ++pHumanPlayer)
    {
        m_CardDeck.SpareCards(*pHumanPlayer);
    }

    //Show HousePlayer's first card
    m_HousePlayer.HideFirstCard();
    cout << endl << m_HousePlayer;

    //Deal additional cards to Houseplayer
    m_CardDeck.SpareCards(m_HousePlayer);

    if (m_HousePlayer.PlayerBusted())
    {
        //Other players win
        for (pHumanPlayer = m_HumanPlayers.begin(); pHumanPlayer != m_HumanPlayers.end(); ++pHumanPlayer)
        {
            if (!(pHumanPlayer->PlayerBusted())) {
                pHumanPlayer->PlayerWins();
            }
        }
    }
    else
    {
        //Compare active HumanPlayers to HousePlayer
        for (pHumanPlayer = m_HumanPlayers.begin(); pHumanPlayer != m_HumanPlayers.end(); ++pHumanPlayer)
        {
            if (!(pHumanPlayer->PlayerBusted()))
            {
                if (pHumanPlayer->GetHandTotal() > m_HousePlayer.GetHandTotal()) {
                    pHumanPlayer->PlayerWins();
                }
                else if (pHumanPlayer->GetHandTotal() < m_HousePlayer.GetHandTotal()) {
                    pHumanPlayer->PlayerLoses();
                }
                else {
                    pHumanPlayer->PlayerPushes();
                }
            }
        }
    }

    //Remove All Cards from players
    for (pHumanPlayer = m_HumanPlayers.begin(); pHumanPlayer != m_HumanPlayers.end(); ++pHumanPlayer)
    {
        pHumanPlayer->Clear();
    }
    m_HousePlayer.Clear();
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

    //Save player name into vector
    vector<string>playerNames;
    string playerName;
    for (int i = 0; i < numOfPlayers; ++i)
    {
        cout << "\nEnter your name human (if you can spell): ";
        cin >> playerName;
        playerNames.push_back(playerName);
    }

    cout << endl;

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

// << operator is overloaded so that we can display card objects
ostream& operator<<(ostream& os, const Card& aCard)
{
    //Uses rank and suit values of the object as array indices. '0' compensates for rank enum beginning with '1'.
    const string CARDRANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9",
                            "10", "J", "Q", "K" };
    const string CARDSUITS[] = { "C", "D", "H", "S" };

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

