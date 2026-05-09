#ifndef CODEGEN_H
#define CODEGEN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "scanner.h"
#include "token.h"
#include "node.h"

using namespace std;

int decodeInt(string);
void codeGen(node_t*, vector<token>, ofstream&, vector<string>&);

#endif