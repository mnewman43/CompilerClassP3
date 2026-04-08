#include "parser.h"

node_t *parser(vector<token> tkList)    {
    node_t *root;
    vector<token> childTk(tkList);
    childTk.pop_back();     //Removes the EOFtk from the token list meant to go into S

    root->right = S(childTk);
    if(tkList.at(tkList.size()-1).tokenType != 0)   {
        cerr << "ERROR: EOFtk not detected." << endl;
    }
    return root;
}