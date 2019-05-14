//
//  main.cpp
//  Hangman
//
//  Created by Sara Rut Fridjónsdóttir on 15/03/2017.
//  Copyright © 2017 Sara Rut Fridjónsdóttir. All rights reserved.
//

#include <fstream>
#include <iostream>
#include "GamePlay.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    srand(static_cast<unsigned int>(time(0)));
  
    char addInput;
    char input;
    GamePlay h;
    
    h.readFromFile();
    h.getData();
    h.welcome();
    
    do
    {
        cout << "Do you want to add a new word to the game(y/n): ";
        cin >> addInput;
    
        if(addInput == 'y' || addInput == 'Y')
        {
            h.addToFile();
        }
        else
        {
            cout << endl;
            cout << "A word will be selected at random :)" << endl;
            cout << endl;
        }

        h.guessCount();
        h.makeWordToUnderscoure();
        h.guessWord();
        
        cout << "Do you want to play again (y/n): ";
        cin >> input;
        cout << endl;
        
    }while(input == 'y' || input == 'Y');
    
    h.writeInToFile();
    h.seeAllHighScore();
    
    return 0;
}
