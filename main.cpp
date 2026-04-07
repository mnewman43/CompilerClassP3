#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "testScanner.h"

using namespace std;

int main(int argc, char*argv[]) {
    string filename;
    vector<token> tokenScanner;

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
    for(int i = 0; tokenScanner.at(i).tokenType != 0 && i < tokenScanner.size(); i++)  {
        cout << "t" << setw(7) << left << tokenScanner.at(i).tokenType << " token ";
        cout << setw(8) << tokenScanner.at(i).instance;
        cout << setw(8) << right << tokenScanner.at(i).lineNum << endl;
    }
    cout << "EOFTk" << endl;

    return 0;
}
