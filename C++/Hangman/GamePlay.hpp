//
//  GamePlay.hpp
//  Hangman
//
//  Created by Sara Rut Fridjónsdóttir on 15/03/2017.
//  Copyright © 2017 Sara Rut Fridjónsdóttir. All rights reserved.
//

#ifndef GamePlay_hpp
#define GamePlay_hpp

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <regex>
#include "GameScore.hpp"

using namespace std;

class GamePlay : public GameScore
{
public:
    GamePlay();
    void welcome(); //explaing the roles
    void getData(); // get all the data from the file and put it in to a vector
    void addToFile(); // adds a new word to the file
    void guessCount(); // how many times the player wants to guess
    string getRandomWord(); // finds a random word for the player
    void theWordIs(); //what that random word is that the player is guessing on
    void makeWordToUnderscoure(); // makes the random word into underscoure
    void guessWord(); // player guesses what the word is
    void forWord(); // see if the word the player guess on is right
    void forLetter(); // see how many letters the players has guessed on

    void writeData(); //writes out the data
    
private:
    vector<string> data;
    
    string word;
    string underscore;
    string letter;
    string guessedLetters;
    int guess;
    bool currectLetter;
};

#endif /* GamePlay_hpp */
