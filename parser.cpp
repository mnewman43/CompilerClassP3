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

node_t *S(vector<token> tkList)    {
    node_t *p;
    vector<token> ATk;
    vector<token> KTk;
    int i;
    
    for(i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "S";
    ATk.push_back(tkList.at(0));
    for (i = 1; tkList.at(i).instance != "$" || tkList.at(i).instance != "*"
    || tkList.at(i).instance != "-" || tkList.at(i).instance != "%"
    || tkList.at(i).instance != "&"; i ++)  {
        //^^ These are all the possible tokens that are at the start of nonterminal A ^^
        ATk.push_back(tkList.at(i));
    }
    p->left = A(ATk);
    for(;i < tkList.size() -1; i++)    {
        KTk.push_back(tkList.at(i));
    }
    p->right = K(KTk);

    if(tkList.at(tkList.size()-1).instance != "'")  {
        cerr << "ERROR: Nonterminal S was not formatted properly." << endl;
    }
    return p;
}


node_t *A(vector<token> tkList)    {
    node_t *p;
    vector<token> leftTk;
    vector<token> rightTk;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "A";
    
    if(tkList.at(0).instance == "$" || tkList.at(0).instance == "*")    {
        p->right = B(tkList);
    }
    else if(tkList.at(0).instance == "-")   {
        p->right = C(tkList);
    }
    else if(tkList.at(0).instance == "%" || tkList.at(0).instance == "&")   {
        int i;
        int apostrophe = 0; //The second apostrophe marks where J ends and S starts
        for(i = 0; apostrophe < 2 && i < tkList.size(); i++)   {
            leftTk.push_back(tkList.at(i));
            if(tkList.at(i+1).instance == "'")    {
                apostrophe++;
            }
        }
        p->left = G(leftTk);
        i++;    //Skips over the t3 token in nonterminal A
        for(;i < tkList.size(); i++)    {
            rightTk.push_back(tkList.at(i));
        }
        p->right = S(rightTk);
    }
    else    {
        cerr << "ERROR: Nonterminal A was not formatted properly." << endl;
        exit(-1);
    }
}
node_t *B(vector<token> tkList)    {
    node_t *p;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "B";

    if(tkList.size() > 2 || tkList.at(1).tokenType != 1)    {
        cerr << "ERROR: Nonterminal B was not formatted properly." << endl;
        exit(-1);
    }
    return p;
}

node_t *C(vector<token> tkList)    {
    node_t *p;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "C";
    return p;
}

node_t *D(vector<token> tkList)    {
    node_t *p;
    p->tk = tkList;
    p->nonterminal = "D";
    if(!tkList.empty()) {
        vector<token> ETk;
        vector<token> HTk;
        ETk.push_back(tkList.at(0));
        p->left = E(ETk);

        for(int i = 1; i < tkList.size(); i++)  {
            HTk.push_back(tkList.at(i));
        }
    }
}

node_t *E(vector<token> tkList)    {
    node_t *p;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "E";
    if(tkList.at(0).instance != "(" || tkList.at(0).instance != ")")  {
        cerr << "ERROR: Nonterminal E was not formatted properly" << endl;
        exit(-1);
    }
    return p;
}

node_t *F(vector<token> tkList)    {
    node_t *p;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "F";
    if(tkList.at(0).instance != "," || tkList.at(0).instance != "."
    || tkList.at(0).instance != "+")   {
        cerr << "ERROR: Nonterminal F was not formatted properly" << endl;
        exit(-1);
    }
    if(tkList.size() > 1)   {
        vector<token> childTk;
        for(int i = 1; i < tkList.size(); i++)  {
            childTk.push_back(tkList.at(i));
        }
        if(childTk.at(0).instance == "'") {
            p->right = J(childTk);
        }
        else    {
            cerr << "ERROR: Nonterminal G was not formatted properly" << endl;
            exit(-1);
        }
    }
    return p;
}

node_t *G(vector<token> tkList)    {
    node_t *p;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "G";
    if(tkList.at(0).instance != "%" || tkList.at(0).instance != "&")  {
        cerr << "ERROR: Nonterminal G was not formatted properly" << endl;
        exit(-1);
    }
    if(tkList.size() > 1)   {   //Can reference to nonterminal H because of nonterminal A
        vector<token> childTk;
        for(int i = 1; i < tkList.size(); i++)  {
            childTk.push_back(tkList.at(i));
        }
        if(childTk.at(0).tokenType == 1 || childTk.at(0).tokenType == 2) {
            p->right = H(childTk); 
        }
        else    {
            cerr << "ERROR: Nonterminal G was not formatted properly" << endl;
            exit(-1);
        }
    }
    return p;
}

node_t *H(vector<token> tkList)    {
    node_t *p;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "H";
    if(tkList.at(0).tokenType != 1 || tkList.at(0).tokenType != 2)  {
        cerr << "ERROR: Nonterminal H was not formatted properly" << endl;
        exit(-1);
    }
    if(tkList.size() > 1)   {
        vector<token> childTk;
        for(int i = 1; i < tkList.size(); i++)  {
            childTk.push_back(tkList.at(i));
        }
        if(childTk.at(0).instance == "," || childTk.at(0).instance == "."
        || childTk.at(0).instance == "+")   {
            p->right = F(childTk);
        }
        else if(childTk.at(0).instance == "(" || childTk.at(0).instance == ")") {
            p->right = D(childTk);
        }
        else    {
            cerr << "ERROR: Nonterminal H was not formatted properly" << endl;
            exit(-1);
        }
    }
    return p;
}

node_t *J(vector<token> tkList)    {
    node_t *p;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "J";
    vector<token> HTk;
    for(int i = 1; i < tkList.size(); i++)  {
        HTk.push_back(tkList.at(i));
    }
    p->right = H(HTk);  //D can be referenced through H
    return p;
}

node_t *K(vector<token> tkList) {
    node_t *p;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "K";
    if(!tkList.empty()) {
        vector<token> STk;
        vector<token> KTk;
        int i, apostrophe = 0;
        for(i = 0; (apostrophe < 2 || (apostrophe < 1
        && (tkList.at(i).instance == "%" || tkList.at(i).instance == "&")))
        && i < tkList.size(); i++) {
            STk.push_back(tkList.at(i));
            if(tkList.at(i+1).instance == "'")  {
                apostrophe++;
            }
        }
        p->left = S(STk);
        i++;
        for(; i < tkList.size(); i++)   {
            KTk.push_back(tkList.at(i));
        }
        p->right = K(KTk);
    }
    return p;
}