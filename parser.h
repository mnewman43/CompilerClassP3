#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>

#include "node.h"


node_t *parser(vector<token>);
node_t *S(vector<token>);


#endif