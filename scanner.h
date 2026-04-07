#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <vector>
#include <fstream>

#include "token.h"

using namespace std;

token scanner(string val, int line);

#endif