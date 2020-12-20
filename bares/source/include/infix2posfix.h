#ifndef _INFIX2POSTFIX_H_
#define _INFIX2POSTFIX_H_

#include <stack>     
#include <string>
#include <cassert>  
#include <cmath>     
#include <vector>    

#include "../include/token.h"

std::vector<Token> infix_to_postfix(std::vector<Token> );
bool has_higher_or_eq_precedence( char op1 , char op2 );
short get_precedence( char op );

#endif