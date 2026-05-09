#include "codeGen.h"

int brOut = 0;
int brIn = 0;
int tempVar = 0;

int decodeInt(string val)   {
    int num;
    string letters;
    string numStr;
    for(int i = 0; i < val.size(); i++) {
        if(isdigit(val[i])) {
            letters = val.substr(0, i);
            numStr = val.substr(i, val.size()-1);
            break;
        }
    }
    num = stoi(numStr);
    if(letters.size() > 1)  {
        num *= -1;
    }
    return num;
}

void codeGen(node_t *tree, vector<token> tkList, ofstream &outFile, vector<string> &semantics)  {
    int genBrOut;
    int genBrIn;
    int genTempVar;
    int num;

    if(tree == nullptr) {
        return;
    }

    if(!tkList.empty()) {
        if(tree->nonterminal == "A" && tkList.at(0).instance == "&")    {
            genBrIn = brIn;
            outFile << "in" << genBrIn << ": ";
        }
    }

    if(tree->left != nullptr)   {
        codeGen(tree->left, tree->left->tk, outFile, semantics);
    }

    if(!tkList.empty()) {
        switch(static_cast<int>(tkList.at(0).instance[0]))  {
            case 34:
            case 35:    // " and # are types of identifiers
                if(tree->nonterminal == "H")    {
                    if(tkList.size() < 2 || (tkList.at(1).instance != ","
            && tkList.at(1).instance != "." && tkList.at(1).instance != "+"))   {
                        outFile << tkList.at(0).instance << endl;
                    }
                }
                break;
            case 36:    // $ Declares and reads a variable
                if(tree->nonterminal == "B")    {
                    outFile << "READ " << tkList.at(1).instance << endl;
                }
                break;
            case 37:    // % indicates an if statement
                if(tree->nonterminal == "A")    {
                    genBrOut = brOut;
                    brOut++;
                    if(tree->tk.at(2).instance == ",")  {
                        outFile << "BRNEG out" << genBrOut << endl;
                    }
                    else if(tree->tk.at(2).instance == ".") {
                        outFile << "BRPOS out" << genBrOut << endl;
                    }
                    else if(tree->tk.at(2).instance == "+") {
                        outFile << "BRNEG out" << genBrOut << endl;
                        outFile << "BRPOS out" << genBrOut << endl;
                    }
                }
                else if (tree->nonterminal == "G")  {
                    outFile << "LOAD " << tkList.at(1).instance << endl;
                    outFile << "SUB " << semantics.at(semantics.size()-1) << endl;
                }
                break;
            case 38:    // & indicates a while loop
                if(tree->nonterminal == "A")    {
                    genBrOut = brOut;
                    brOut++;
                    if(tree->tk.at(2).instance == ",")  {
                        outFile << "BRNEG out" << genBrOut << endl;
                    }
                    else if(tree->tk.at(2).instance == ".") {
                        outFile << "BRPOS out" << genBrOut << endl;
                    }
                    else if(tree->tk.at(2).instance == "+") {
                        outFile << "BRNEG out" << genBrOut << endl;
                        outFile << "BRPOS out" << genBrOut << endl;
                    }
                }
                else if (tree->nonterminal == "G")  {
                    outFile << "LOAD " << tkList.at(1).instance << endl;
                    outFile << "SUB " << semantics.at(semantics.size()-1) << endl;
                }
                break;
            case 39:    // ' is a delimiter, usually starts a block
                if(tree->nonterminal == "J")    {
                    outFile << "LOAD ";
                }
                break;
            case 40:    // ( Adds to accumulator
                if(tree->nonterminal == "E")    {
                    outFile << "ADD ";
                }
                break;
            case 41:    // ) Subtracts from accumulator
                if(tree->nonterminal == "E")    {
                    outFile << "SUB ";
                }
                break;
            case 42:    // * Outputs the value of an identifier
                if(tree->nonterminal == "B")    {
                    outFile << "WRITE " << tkList.at(1).instance << endl;
                }
                break;
            case 43:    // + Means equal to
                break;
            case 44:    // , Means greater than
                break;
            case 45:    // - Stores a value
                if(tree->nonterminal == "C")    {
                    outFile << "STORE " << tkList.at(1).instance << endl;
                }
                break;
            case 46:    // . Means less than
                break;
            default:
                if(isalpha(tkList.at(0).instance[0]) && tree->nonterminal == "H")   {
                    num = decodeInt(tkList.at(0).instance);
                    outFile << num << endl;
                    break;
                }
        }
    }
    if(tree->right != nullptr)   {
        codeGen(tree->right, tree->right->tk, outFile, semantics);
    }
    if(!tkList.empty()) {
        switch(static_cast<int>(tkList.at(0).instance[0]))  {
            case 37:    //If statement, after the block
                if(tree->nonterminal == "A")    {
                    outFile << "out" << genBrOut << ": ";
                }
                break;
            case 38:    //End of a while loop
                if(tree->nonterminal == "A")    {
                    outFile << "BR in" << genBrIn << endl;
                    outFile << "out" << genBrOut << ": "; 
                }
                break;
            case 39:
                if(tree->nonterminal == "J")    {
                    genTempVar = tempVar;
                    outFile << "STORE x" << genTempVar << endl;
                    tempVar++;
                    semantics.push_back("x" + to_string(genTempVar));
                }
        }
    }
}