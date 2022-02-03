#include <ctime>
#include <assert.h>
#include <iostream>

namespace wikibooks_design_patterns {
///////////////////////////////////////////////////////////////////////////////
//! An abstract class that is common to several games in which players play 
//!  against the others, but only one is playing at a given time.
class Game {
protected: // Functions to be implemented by derived classes
    virtual void initializeGame() = 0;
    virtual void makePlay(int player) = 0;
    virtual bool endOfGame() = 0;
    virtual void printWinner() = 0;

public:
    Game(): playersCount(0), movesCount(0), playerWon(-1) {
        srand( (unsigned)time( NULL));
    }

    // A method that calls the class's implementations 
    void playOneGame(const int playersCount = 0) {
        if (playersCount) this->playersCount = playersCount;
        InitializeGame();
        assert( this->playersCount );
        int j = 0;
        while (!endOfGame()) {
            makePlay(j);
            j = (j + 1) % this->playersCount;
            if( !j ) ++movesCount;
        }
        printWinner();
    }

private:
    void InitializeGame() {
        movesCount = 0;
        playerWon = -1;
        initializeGame();
    }

protected:
    int playersCount, movesCount, playerWon;
};
///////////////////////////////////////////////////////////////////////////////
// Now we can extend this class in order to implement actual games:
class Monopoly: public Game {
private:
    enum { MOVES_WIN_CORRECTION = 20, };
public: // Implementation of necessary concrete methods
    void initializeGame() {
        playersCount = rand() * 7 / RAND_MAX + 2;
    };
    void makePlay(int player) {
        if (movesCount < 20) return;
        const int chances = (movesCount > 199) ? 199 : movesCount;
        const int random = MOVES_WIN_CORRECTION * rand() * 200 / RAND_MAX;
        if (random < chances) playerWon = player;
    }

    // Return true if game is over according to Monopoly rules
    bool endOfGame() { return (-1 != playerWon); }

    // Display who won
    void printWinner() {
        assert(playerWon >= 0);
        assert(playerWon < playersCount);
        std::cout<<"Monopoly, player "<<playerWon<<" won in "<<
            movesCount<<" moves."<<std::endl;
    }
};
///////////////////////////////////////////////////////////////////////////////
class Chess: public Game {
private:
    enum { MOVES_WIN_CORRECTION = 7, };
public: // Implementation of necessary concrete methods
    void initializeGame() {
        playersCount = 2;
    };

    void makePlay(int player) {
        assert(player < playersCount);
        if (movesCount < 2) return;
        const int chances = (movesCount > 99) ? 99 : movesCount;
        const int random = MOVES_WIN_CORRECTION * rand() * 100 / RAND_MAX;
        if (random < chances) playerWon = player;
    }

    // Return true if in Checkmate or Stalemate has been reached
    bool endOfGame() { return (-1 != playerWon); }

    // Display the winning player
    void printWinner() {
        assert(playerWon >= 0);
        assert(playerWon < playersCount);
        std::cout<<"Player "<<playerWon<<" won in "<<movesCount<<" moves."<<std::endl;
    }
};
} //< End wikibooks_design_patterns namespace

///////////////////////////////////////////////////////////////////////////////
int main()
{
    using namespace wikibooks_design_patterns;

    Game* game = NULL;

    Chess chess;
    game = &chess;
    for (unsigned i = 0; i < 100; ++i)
	    game->playOneGame();

    Monopoly monopoly;
    game = &monopoly;
    for (unsigned i = 0; i < 100; ++i)
	    game->playOneGame();

    return 0;
}