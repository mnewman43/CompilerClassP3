#ifndef NODE_H
#define NODE_H

#include <string>

#include "token.h"

using namespace std;

    struct node_t   {
        int level;
        int charVal;
        string nonterminal;
        vector<token> tk;
        node_t* left;
        node_t* right;
    };

#endif