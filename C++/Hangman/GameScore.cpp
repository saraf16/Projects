//
//  GameScore.cpp
//  Hangman
//
//  Created by Sara Rut Fridjónsdóttir on 20/03/2017.
//  Copyright © 2017 Sara Rut Fridjónsdóttir. All rights reserved.
//

#include "GameScore.hpp"


GameScore::GameScore()
{
    name = " ";
    hscore = 0;
    gameWon = 0;
    gameLost = 0;
}

GameScore::GameScore(string name, int hscore, int gameWon, int gameLost)
{
    this->name = name;
    this->hscore = hscore;
    this->gameWon = gameWon;
    this->gameLost = gameLost;
}

void GameScore::setName()
{
    
    cout << endl;
    cout << "+---+" << endl;
    cout << " |  |" << endl;
    cout << " 0  |" << endl;
    cout << "/|\\ |" << endl;
    cout << "/ \\ |" << endl;
    cout << "    |" << endl;
    cout << "=========     Name of player: ";
    cin >> name;
}

void GameScore::readFromFile()
{
    ifstream in;
    string word;
    in.open("score.txt");
    
    if(in.fail())
    {
        cout << " File failed to open" << endl;
        exit(1);
    }
    else
    {
        GameScore score;
        
        while(in >> score.name >> score.hscore >> score.gameWon >> score.gameLost)
        {
            highScore.push_back(score);
        }
    }
    
    in.close();
    
    highScore.sort([](const GameScore &l, const GameScore &r) { return l.hscore > r.hscore; });
}

void GameScore::writeInToFile()
{
    ofstream out;
    out.open("score.txt", ios::app);
    if(out.fail())
    {
        cout << " File failed to open" << endl;
        exit(1);
    }
    else
    {
        GameScore tempt(name, hscore, gameWon, gameLost);
        out << endl;
        out << name << " " << hscore << " "<< gameWon << " " << gameLost;
        highScore.push_back(tempt);
        cout << "You have been added to the high score list" << endl;
    }
    
    out.close();
    
    highScore.sort([](const GameScore &l, const GameScore &r) { return l.hscore > r.hscore; });

}

void GameScore::seeData()
{
    for(it = highScore.begin(); it != highScore.end(); it++)
    {
        cout << *it;
    }
}

void GameScore::setWinplusOne()
{
    gameWon++;
}

void GameScore::setLostplusOne()
{
    gameLost++;
}

int GameScore::sethighscore()
{
    return hscore = (gameWon * 5) - gameLost;
    
}

void GameScore::yourHighScore()
{
    cout << "Your high score is: " <<  sethighscore() << endl;
    cout << "You have won: " << gameWon << endl;
    cout << "You have lost: " << gameLost << endl;
}

void GameScore::seeAllHighScore()
{
    cout << "Do you want to see all the high scores (y/n): ";
    cin >> input;
    
    if(input == 'y' || input == 'Y')
    {
        seeData();
    }
}

ostream& operator <<(ostream& out, const GameScore& game)
{
    out << "---------------" << endl;
    out << "Name: " << game.name << endl;
    out << "High score: " << game.hscore << endl;
    out << "Won: " << game.gameWon << endl;
    out << "Lost: " << game.gameLost << endl;
    
    return out;
}
