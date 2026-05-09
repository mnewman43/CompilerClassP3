#include "parser.h"

node_t *parser(vector<token> tkList)    {
    node_t *root = new node_t;
    vector<token> childTk(tkList);

    cout << "Parsing list of tokens..." << endl;

    childTk.pop_back();     //Removes the EOFtk from the token list meant to go into S
    root->right = S(childTk);
    if(tkList.at(tkList.size()-1).tokenType != 0)   {
        cerr << "ERROR: EOFtk not detected." << endl;
    }
    return root;
}

node_t *S(vector<token> tkList)    {
    node_t *p = new node_t;
    vector<token> ATk;
    vector<token> KTk;
    int i = 0, apostrophe = 0;
    p->nonterminal = "S";

    if(tkList.at(0).instance == "$" || tkList.at(0).instance == "*")    {
        ATk.push_back(tkList.at(0));
        ATk.push_back(tkList.at(1));
    }
    else if(tkList.at(0).instance == "-")  {
        for(i = 0; apostrophe < 2 && i < tkList.size()-1; i++)    {
            if(tkList.at(i).instance == "'")    {
                apostrophe++;
            }
            if(tkList.at(i).instance == "$" || tkList.at(i).instance == "*")    {
                break;
            }
            ATk.push_back(tkList.at(i));
        }
    }
    else if(tkList.at(0).instance == "%" || tkList.at(0).instance == "&")   {
        if(tkList.size() < 3)   {
            cerr << "ERROR: Nonterminal S was not formatted properly" << endl;
            for(int i = 0; i < tkList.size(); i++)  {
                cerr << tkList.at(i).instance << " ";
            }
            exit(-1);
        }
        int maxDelim = 3;
        ATk.push_back(tkList.at(0));
        for(i = 1; i < tkList.size()-1 && apostrophe < maxDelim; i++)   {
            if(tkList.at(i).instance == "'")    {
                apostrophe++;
            }
            else if(tkList.at(i).instance == "-")   {
                maxDelim += 2;
            }
            else if(tkList.at(i).instance == "%" || tkList.at(i).instance == "&")   {
                maxDelim += 3;
            }
            ATk.push_back(tkList.at(i));
        }
    }
    p->left = A(ATk);
    for(i = ATk.size(); i < tkList.size()-1; i++)    {
        KTk.push_back(tkList.at(i));
    }
    p->right = K(KTk);

    if(tkList.at(tkList.size()-1).instance != "'")  {
        cerr << "ERROR: Nonterminal S was not formatted properly." << endl;
        cerr << "List had " << tkList.size() << " tokens" << endl;
        for(int i = 0; i < tkList.size(); i++)  {
            cerr << tkList.at(i).instance << " ";
        }
    }
    p->tk.push_back(tkList.at(tkList.size()-1));
    return p;
}


node_t *A(vector<token> tkList)    {
    node_t *p = new node_t;
    vector<token> leftTk;
    vector<token> rightTk;
    p->nonterminal = "A";

    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }

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
            if(tkList.at(i).instance == "'")  {
                apostrophe++;
            }
            leftTk.push_back(tkList.at(i));
        }
        p->left = G(leftTk);
        for(i = leftTk.size(); i < tkList.size(); i++)    {
            rightTk.push_back(tkList.at(i));
        }

        p->right = S(rightTk);
    }
    else    {
        cerr << "ERROR: Nonterminal A was not formatted properly: ";
        for(int i = 0; i < tkList.size(); i++)  {
            cerr << tkList.at(i).instance << " ";
        }
        cerr << endl;
        exit(-1);
    }
    return p;
}
node_t *B(vector<token> tkList)    {
    node_t *p = new node_t;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "B";
    if(tkList.size() != 2 || tkList.at(1).tokenType != 1)    {
        cerr << "ERROR: Nonterminal B was not formatted properly." << endl;
        exit(-1);
    }
    return p;
}

node_t *C(vector<token> tkList)    {
    node_t *p = new node_t;
    int i;
    vector<token> JTk;
    p->nonterminal = "C";
    for(i = 0; i < tkList.size() && tkList.at(i).instance != "'"; i++)  {
        p->tk.push_back(tkList.at(i));
    }
    for(; i < tkList.size(); i++)   {
        JTk.push_back(tkList.at(i));
    }
    p->left = J(JTk);

    return p;
}

node_t *D(vector<token> tkList)    {
    node_t *p = new node_t;
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
        p->right = H(HTk);
    }
    return p;
}

node_t *E(vector<token> tkList)    {
    node_t *p = new node_t;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "E";
    if(tkList.at(0).instance != "(" && tkList.at(0).instance != ")")  {
        cerr << "ERROR: Nonterminal E was not formatted properly" << endl;
        exit(-1);
    }
    return p;
}

node_t *F(vector<token> tkList)    {
    node_t *p = new node_t;
    p->tk.push_back(tkList.at(0));
    p->nonterminal = "F";
    if(tkList.at(0).instance != "," && tkList.at(0).instance != "."
    && tkList.at(0).instance != "+")   {
        cerr << "ERROR: Nonterminal F was not formatted properly" << endl;
        exit(-1);
    }
    if(tkList.size() > 1)   {
        vector<token> childTk;
        for(int i = 1; i < tkList.size(); i++)  {
            childTk.push_back(tkList.at(i));
        }
        if(childTk.at(0).instance == "'") {
            p->left = J(childTk);
        }
        else    {
            cerr << "ERROR: Nonterminal G was not formatted properly" << endl;
            exit(-1);
        }
    }
    return p;
}

node_t *G(vector<token> tkList)    {
    node_t *p = new node_t;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "G";
    if(tkList.at(0).instance != "%" && tkList.at(0).instance != "&")  {
        cerr << "ERROR: Nonterminal G was not formatted properly: ";
        cerr << tkList.at(0).instance << endl;
        exit(-1);
    }
    if(tkList.size() > 1)   {   //Can reference to nonterminal H because of nonterminal A
        vector<token> childTk;
        for(int i = 1; i < tkList.size(); i++)  {
            childTk.push_back(tkList.at(i));
        }
        if(childTk.at(0).tokenType == 1 || childTk.at(0).tokenType == 2) {
            p->left = H(childTk); 
        }
        else    {
            cerr << "ERROR: Nonterminal G was not formatted properly: ";
            for(int i = 0; i < tkList.size(); i++)  {
                cerr << tkList.at(i).instance << " ";
            }
            cout << endl;
            exit(-1);
        }
    }
    return p;
}

node_t *H(vector<token> tkList)    {
    node_t *p = new node_t;
    for(int i = 0; i < tkList.size(); i++)  {
        p->tk.push_back(tkList.at(i));
    }
    p->nonterminal = "H";
    if(tkList.at(0).tokenType != 1 && tkList.at(0).tokenType != 2)  {
        cerr << "ERROR: Nonterminal H was not formatted properly" << endl;
        cerr << "Token was " << tkList.at(0).instance << endl;
        cerr << "Token type: " << tkList.at(0).tokenType << endl;
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
        //else    {
            //cerr << "ERROR: Nonterminal H was not formatted properly" << endl;
            //cerr << "Child token started with: " << childTk.at(0).instance << endl;
            //exit(-1);
        //}
    }
    return p;
}

node_t *J(vector<token> tkList)    {
    node_t *p = new node_t;
    p->tk.push_back(tkList.at(0));
    p->nonterminal = "J";
    vector<token> HTk;
    for(int i = 1; i < tkList.size() && tkList.at(i).instance != "'"; i++)  {
        HTk.push_back(tkList.at(i));
    }
    p->right = H(HTk);  //D can be referenced through H
    return p;
}

node_t *K(vector<token> tkList) {
    node_t *p = new node_t;
    p->nonterminal = "K";
    vector<token> STk;
    vector<token> KTk;
    if(!tkList.empty()) {
        int apostrophe;
        int maxDelim = 1;
        for(int i = 0; i < tkList.size() && apostrophe < maxDelim; i++)   {
            if(tkList.at(i).instance == "'")    {
                apostrophe++;
            }
            else if(tkList.at(i).instance == "-")   {
                maxDelim += 2;
            }
            else if(tkList.at(i).instance == "%" || tkList.at(i).instance == "&")   {
                maxDelim += 3;
            }
            STk.push_back(tkList.at(i));
        }
        p->left = S(STk);
        for(int i = STk.size(); i < tkList.size(); i++) {
            KTk.push_back(tkList.at(i));
        }
        p->right = K(KTk);
    }
    return p;
}