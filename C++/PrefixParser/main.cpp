//
//  main.cpp
//  PrefixParser
//
//  Created by Sara Rut Fridjónsdóttir on 08/02/2017.
//  Copyright © 2017 Sara Rut Fridjónsdóttir. All rights reserved.
//

#include <fstream>
#include "prefixparser.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    ifstream fin;
    fin.open("test.txt");
    
    string inp;
    while (fin >> inp) {
        if (inp == "new") {
            cout << "New test" << endl;
        }else if (inp == "parse") {
            cout << "Calling parseExpression()" << endl;
            try {
                int result = parseExpression(fin);
                cout << "Parsed expression: " << result << endl;
            }
            catch(DivideByZeroException) {
                cout << "Caught DivideByZeroException" << endl;
            }
        }else {
            cout << "INVALID INPUT: " << inp << endl;
        }
    }
    
    fin.close();
    
    return 0;
}
