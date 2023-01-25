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
    cout << "\n" << m_PlayerName << ", everyone has the right to be stupid...do you want a hit? (Y/N):";
    char answer;
    cin >> answer;
    return (answer == 'y' || answer == 'Y');
}

//Outputs to player decisions 
void HumanPlayer::PlayerWins() const
{
    cout <<"\n" << m_PlayerName << " you win.... ya filthy animal!!!\n\n";
}

void HumanPlayer::PlayerLoses() const
{
    cout << "\n" << m_PlayerName << " loses. Machine (not) learning anything here!!!\n\n";
}

void HumanPlayer::PlayerPushes() const
{
    cout << "\n" << m_PlayerName << " pushes.\n\n";
}
