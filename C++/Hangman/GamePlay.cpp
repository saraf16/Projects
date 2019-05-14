//
//  GamePlay.cpp
//  Hangman
//
//  Created by Sara Rut Fridjónsdóttir on 15/03/2017.
//  Copyright © 2017 Sara Rut Fridjónsdóttir. All rights reserved.
//

#include "GamePlay.hpp"

GamePlay::GamePlay()
{
    
}


void GamePlay::welcome()
{
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+" << endl;
    cout << "|W| |e| |l| |c| |o| |m| |e|   |t| |o|   |H| |a| |n| |g| |m| |a| |n|" << endl;
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+" << endl;
    
    cout << "********************************************************************* " << endl;
    cout << "  Here is how it works! You get a random word and have to guess        " << endl;
    cout << "  what word it is. If you guess a wrong word or a letter in the word   " << endl;
    cout << "  you will have one fewer guesses left. You on the other hand get    " << endl;
    cout << "  to decide how many guesses you like in the beginning of the game!      " << endl;
    cout << "  You get 5 scoures if you win a game and -1 for every lost game      " << endl;
    cout << "********************************************************************* " << endl;
    
    setName();
    
}

void GamePlay::getData()
{
    ifstream in;
    string word;
    in.open("data.txt");
    
    if(in.fail())
    {
        cout << " File failed to open" << endl;
        exit(1);
    }
    else
    {
        while(in >> word)
        {
            data.push_back(word);
        }
    }
    
    in.close();
}

void GamePlay::writeData()
{
    for(vector<string>::iterator it = data.begin(); it != data.end(); it++)
    {
        cout << *it << endl;
    }
}

void GamePlay::addToFile()
{
    string word;
    do{
    cout << "What word do you want to add (a-z): " << endl;
    cin >> word;
    }while(!(regex_match(word, regex("(^[a-z]*$)"))));
    

    ofstream out;
    out.open("data.txt", ios::app);
    if(out.fail())
    {
        cout << " File failed to open" << endl;
        exit(1);
    }
    else
    {
        out << endl;
        out << word;
        data.push_back(word);
        cout << "Your word has been added" << endl;
    }
    
    out.close();

}

string GamePlay::getRandomWord()
{
    return data[rand() % data.size()];
}

void GamePlay::theWordIs()
{
    cout << endl;
    cout << "The word is: " << underscore << endl;
}

void GamePlay::makeWordToUnderscoure()
{
    word = getRandomWord();
    
    underscore = "";
    
    
    for(int i = 0; i < word.length(); i++)
    {
        underscore += "-";
    }
    
    theWordIs();
}

void GamePlay::guessCount()
{
    do{
        cout << "How many guesses do you want (1 - 100): ";
        cin >> guess;
    }while(guess > 100 || guess < 1);
}

void GamePlay::guessWord()
{
    guessedLetters = "";
    while(guess > 0)
    {
        currectLetter = false;
        
        cout << "You have " << guess << " guesses left" << endl;
        cout << "Enter a letter or a whole word: ";
        cin >> letter;
        guessedLetters += letter + " ";
        cout << "The letters you have enterd are: " << guessedLetters << endl;
        
        if(letter.length() > 1)
        {
            forWord();

        }
        else
        {
            forLetter();

        }
        
        if(currectLetter == false)
        {
            guess --;
        }
        
        theWordIs();
        
        if(underscore == word)
        {
            cout << "You have won!" << endl;
            setWinplusOne();
            yourHighScore();

            break;
        }
        else if(guess == 0)
        {
            cout << "Sorry you have lost! :(" << endl;
            cout << "The word was: " << word << endl;
            setLostplusOne();
            yourHighScore();
        }
    }
}

void GamePlay::forWord()
{
    if(letter == word)
    {
        underscore = letter;
        currectLetter = true;
    }
    
}
void GamePlay::forLetter()
{
    for(int i = 0; i < word.length(); i++)
    {
        if(letter[0] == tolower(word[i]))
        {
            underscore[i] = letter[0];
            currectLetter = true;
        }
    }
}

