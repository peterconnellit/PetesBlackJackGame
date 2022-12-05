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