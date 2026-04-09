#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>

#include "node.h"


node_t *parser(vector<token>);
node_t *S(vector<token>);
node_t *A(vector<token>);
node_t *B(vector<token>);
node_t *C(vector<token>);
node_t *D(vector<token>);
node_t *E(vector<token>);
node_t *F(vector<token>);
node_t *G(vector<token>);
node_t *H(vector<token>);
node_t *J(vector<token>);
node_t *K(vector<token>);

#endif