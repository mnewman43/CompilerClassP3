#include "scanner.h"

token scanner(string val, int line) {
    string group;
    token tk;
    tk.instance = val;
    tk.lineNum = line;

    

    for(int i = 0; i < val.size(); i++) {
        if((!isdigit(val[i]) && !isalpha(val[i])) && (static_cast<int>(val[i]) < 32 && static_cast<int>(val[i]) > 47))    {
            cerr << "SCANNER ERROR: Invalid character detectied at line " << line << ": " << val << endl;
            cout << static_cast<int>(val[i]) << endl;
            tk.tokenType = -1;
            return tk;
        }
    }

    //Scans for t1_tk
    if(val[0] == '"' || val[0] == '#')  {
        for(int i = 1; i < val.size(); i++) {
            if(!isdigit(val[i]))    {
                cerr << "ERROR: Invalid use of t1_tk: " << val << endl;
                tk.tokenType = -1;
                return tk;
            }
        }
        tk.tokenType = 1;
    }
    //Scans for t2_tk
    else if(isalpha(val[0]))    {
        int firstDigit = 0;
        for(int i = 1; i < val.size(); i++) {
            if(isdigit(val[i])) {
                firstDigit = i;
                break;
            }
            else if(!isalpha(val[i]))   {
                cerr << "ERROR: Invalid use of t2_tk: " << val << endl;
                tk.tokenType = -1;
                return tk;
            }
        }
        for(int i = firstDigit; i < val.size(); i++)    {
            if(!isdigit(val[i]))    {   //Checks that there are digits and digits ONLY at the end of the string
                cerr << "ERROR: Invalid use of t2_tk: " << val << endl;
                tk.tokenType = -1;
                return tk;
            }
        }
        tk.tokenType = 2;
    }
    //Scans for t3_tk
    else if(static_cast<int>(val[0]) >= 36 && static_cast<int>(val[0]) <= 47)   {
        if(val.size() > 1)  {
            cerr << "ERROR: Invalid use of t3_tk: " << val << endl;
            tk.tokenType = -1;
            return tk;
        }
        tk.tokenType = 3;
    }
    return tk;
}