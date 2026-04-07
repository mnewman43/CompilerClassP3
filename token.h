#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

using namespace std;

struct token    {
    /*
        TOKEN TYPE DICTIONARY:
            -1: Error Detected, terminates program if spotted.
            0: EOFtk
            1: t1_tk
            2: t2_tk
            3: t3_tk
    */
    int tokenType;
    string instance;
    int lineNum;
};

#endif