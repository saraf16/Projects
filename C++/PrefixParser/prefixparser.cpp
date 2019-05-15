#include <iostream>
#include <cstdlib>
#include "prefixparser.h"

using namespace std;

int parseExpression(istream& ins){
    
    string nextstring;
    
    if(ins >> nextstring)
    {
        if(nextstring == "+")
        {
            return parseExpression(ins) + parseExpression(ins);
        }
        else if(nextstring == "-")
        {
            return parseExpression(ins) - parseExpression(ins);
        }
        else if(nextstring == "*")
        {
            return parseExpression(ins) * parseExpression(ins);
        }
        else if(nextstring == "/")
        {
            int returnvalue1;
            int returnvalue2;
            
            returnvalue1 = parseExpression(ins);
            returnvalue2 = parseExpression(ins);
            
            if(returnvalue2 == 0)
            {
                throw DivideByZeroException();
            }
            
            
            return returnvalue1 / returnvalue2;
        }
        else
        {
            return atoi(nextstring.c_str());
        }
    }

    return 0;

}
