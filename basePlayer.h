using namespace std;

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
    Both player and house will require their own implementation.
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
