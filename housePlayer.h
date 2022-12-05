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
