//
//  GameScore.hpp
//  Hangman
//
//  Created by Sara Rut Fridjónsdóttir on 20/03/2017.
//  Copyright © 2017 Sara Rut Fridjónsdóttir. All rights reserved.
//

#ifndef GameScore_hpp
#define GameScore_hpp

#include <iostream>
#include <list>
#include <fstream>

using namespace std;

class GameScore
{
public:
    GameScore();
    GameScore(string name, int hscore, int gameWon, int gameLost);

    void setName(); // sets the name of the player
    void readFromFile(); // reads from the file to the list
    void writeInToFile(); //writes in to the file and list
    void seeData(); // see the high score list
    int sethighscore(); // sets the high score of the player that is playing
    void yourHighScore(); //find out what high score the player has
    void setWinplusOne(); // count on how many won games
    void setLostplusOne(); // count on how many lost games
    void seeAllHighScore(); // see all the high score from the file
    
    friend ostream& operator <<(ostream& out, const GameScore& game);
    
private:
    list<GameScore> highScore;
    list<GameScore>::iterator it;
    string name;
    int hscore;
    int gameWon = 0;
    int gameLost = 0;
    char input;
};

#endif /* GameScore_hpp */
