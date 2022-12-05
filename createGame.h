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