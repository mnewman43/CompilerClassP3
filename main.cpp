#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "testScanner.h"
#include "parser.h"
#include "semantics.h"

using namespace std;

int main(int argc, char*argv[]) {
    string filename;
    vector<token> tokenScanner;
    vector<string> statSem;
    node_t *tree = new node_t;

    //Checks number of arguments in commmand line
    if(argc > 2)    {
        cerr << "FATAL: Improper usage." << endl;
        cerr << "Usage: ./P1 [filename]" << endl;
        return -1;
    }

    //Checks if filename was given in command line
    if(argc == 1)   {
        cout << "Filename must be entered:" << endl;
        cin >> filename;
    }
    else    {
        filename = argv[1];
    }

    //Checks for open file
    ifstream inFile(filename);
    if(!inFile.is_open())   {
        cerr << "FATAL: File not opened" << endl;
        return -1;
    }

    tokenScanner = testScanner(inFile);

    for(int i = 0; i < tokenScanner.size(); i++)    {
        if(tokenScanner.at(i).tokenType == -1)  {
            cerr << "Scanner was not completed. Please try again." << endl;
            return -1;
        }
    }
    
    tree = parser(tokenScanner);

    statSem = semantics(tokenScanner);

    cout << "Symbol Table: " << endl;
    for(int i = 0; i < statSem.size(); i++)   {
        cout << statSem.at(i) << " ";
    }
    cout << endl;

    return 0;
}
