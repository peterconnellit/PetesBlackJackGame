using namespace std;

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
    for (cardIter = m_HandCards.begin(); cardIter != m_HandCards.end(); ++cardIter)
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
