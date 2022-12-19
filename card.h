using namespace std;

//CARD CLASS
class Card
{
    //Defines Access (attributes and methods), all can be accessed and modified from outside the Card class
public:
    //Define enumerations to 1.make code more readable and 2. limit values of m_ data members
    enum cardRanks { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
    enum cardSuits { Clubs, Diamonds, Hearts, Spades };

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