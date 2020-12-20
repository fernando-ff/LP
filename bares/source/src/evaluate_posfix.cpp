#include "../include/evaluate_posfix.h"

typedef short int required_int_type; //!< The interger type we accept as valid for an expression.

std::string execute_operator( value_type v1, value_type v2, const char op ){
    switch( op )
    {
        case '^':   if (!limiting_total(pow( v1,v2 ))) return ( "Numeric overflow error!" );
                    return std::to_string(pow( v1,v2 ));
        case '*':   if (!limiting_total(v1*v2)) return ( "Numeric overflow error!" );
                    return std::to_string(v1*v2);
        case '/':   if ( v2 == 0 ) return ( "Division by zero!" );
                    if (!limiting_total(v1/v2)) return ( "Numeric overflow error!" );
                    return std::to_string(v1/v2);
        case '%':   if ( v2 == 0 ) return ( "Division by zero!" );
                    if (!limiting_total(v1%v2)) return ( "Numeric overflow error!" );
                    return std::to_string(v1%v2);
        case '+':   if (!limiting_total(v1+v2)) return ( "Numeric overflow error!" );
                    return std::to_string(v1+v2);
        case '-':   if (!limiting_total(v1-v2)) return ( "Numeric overflow error!" );
                    return std::to_string(v1-v2);
        default:    throw std::runtime_error( "ERRO FATAL" );
    }
}

bool limiting_total (value_type number){
    if((number > std::numeric_limits< required_int_type >::max()) or (number < std::numeric_limits< required_int_type >::min()))
        return false;
    else 
        return true;
}

std::string evaluate_to_postfix( std::vector <Token> postfix ){
    std::stack< value_type > stack;
    
    for( Token token : postfix ){
        if(token.type == Token::token_t::OPERAND)
            stack.push( stoll(token.value) );
        else 
        {
            if ( std::string("*^/%+-").find(token.value) != std::string::npos )
            {
                value_type op2 = stack.top(); 
                stack.pop();
                value_type op1 = stack.top(); 
                stack.pop();
                auto result = execute_operator( op1, op2, token.value[0] ); 
                if((result == ( "Division by zero!" )) or (result == ( "Numeric overflow error!" )))
                    return result;
                stack.push( stoll(result) );
            } 
            else 
                assert( false );    
        }
    }

    //!< Cheking if have numeric overflow
    value_type total = stack.top();
    if(!limiting_total(total))
        return ( "Numeric overflow error!" );
    

    return std::to_string(total);
}