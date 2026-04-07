#include "testScanner.h"

vector<token> testScanner(ifstream &inFile) {
    vector<token> tkScan;
    int line = 1;
    bool comment = false;   //Used to indicate when a phrase is in a comment

    while(!inFile.eof())    {
        string lineVal, val;
        vector<string> lineStr;
        getline(inFile, lineVal);   //Reads all the strings in a line
        stringstream ss(lineVal);

        //Splits the string into multiple strings separated by whitespace
        while(ss >> val)    {
            lineStr.push_back(val);
        }

        //Takes the strings and makes them all tokens
        for(int i = 0; i < lineStr.size(); i++) {
            if(lineStr.at(i).find('!') != string::npos) {
                comment = !comment;
                continue;
            }
            if(!comment)    {
                token nextToken = scanner(lineStr.at(i), line);
                tkScan.push_back(nextToken);
                if(nextToken.tokenType == -1)   {
                    return tkScan;
                }
            }
        }
        line++;
    }
    token eofTk;
    eofTk.tokenType = 0;
    eofTk.instance = "EOFTk";
    eofTk.lineNum = line;
    tkScan.push_back(eofTk);

    return tkScan;
}