#ifndef EVALUATE_POSTFIX_H_
#define EVALUATE_POSTFIX_H_

#include <stack>     
#include <string>    
#include <cassert>   
#include <cmath>     
#include <stdexcept> 
#include <vector>    

#include "../include/token.h" 

using value_type = long int;    

bool is_operator( std::string s );
std::string execute_operator( value_type v1, value_type v2, const char op );
bool limiting_total (value_type number);
std::string evaluate_to_postfix( std::vector <Token> postfix );

#endif