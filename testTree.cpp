#include "testTree.h"

void printTree(node_t *node, ofstream &outFile, int level)   {
    if(node == nullptr)  {
        return;
    }
    for(int i = 0; i < level; i++)  {
        outFile << "   ";
    }
    outFile << node->nonterminal << endl;
    for(int i = 0; i < node->tk.size(); i++) {
        for(int j = 0; j < level; j++)  {
            outFile << "    ";
        }
        outFile << "  " << node->tk.at(i).instance << endl;
    }

    printTree(node->left, outFile, level + 1);
    printTree(node->right, outFile, level + 1);
}