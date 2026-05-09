#include "semantics.h"

vector<string> semantics(vector<token> tokenScanner)    {
    cout << "Beginning semantics generation..." << endl;
    vector<string> s;
       for(int i = 0; i < tokenScanner.size() - 1; i++)    {
        if(tokenScanner.at(i).instance == "$")  {
            if(tokenScanner.at(i+1).tokenType == 1)  {
                for(int j = 0; j < s.size(); j++)   {
                    if(tokenScanner.at(i+1).instance == s.at(j))    {
                        cerr << "ERROR: Variable " << s.at(j);
                        cerr << " declared twice" << endl;
                        exit(-1);
                    }
                }
                s.push_back(tokenScanner.at(i+1).instance);
                i++;
            }
            else    {
                cerr << "ERROR: Improper Variable declaration: " << tokenScanner.at(i).instance;
                cerr << " " << tokenScanner.at(i+1).instance << endl;
                exit(-1);
            }
        }
        if(tokenScanner.at(i).tokenType == 1)   {
            bool varFound = false;
            for(int j = 0; j < s.size(); j++)   {
                if(tokenScanner.at(i).instance == s.at(j))  {
                    varFound = true;
                    break;
                }
            }
            if(!varFound)   {
                cerr << "ERROR: Variable not declared: " << tokenScanner.at(i).instance << endl;
                exit(-1);
            }
        }
    }
    return s;
}