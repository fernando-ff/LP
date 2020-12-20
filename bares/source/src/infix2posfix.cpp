#include "../include/infix2posfix.h" 

short get_precedence( char op ){
    switch( op )
    {
        case '^' : return 3;
        case '*' :
        case '/' :
        case '%' : return 2;
        case '+' :
        case '-' : return 1;
        case '(' : return 0;
        default  : assert( false );  return -1;
    }
}

bool has_higher_or_eq_precedence( char op1 , char op2 ){
    int p_op1 = get_precedence( op1 );
    int p_op2 = get_precedence( op2 );

    if ( p_op1 > p_op2 )
        return true;
    else 
    {
        if ( p_op1 < p_op2 )
            return false;
        else 
        { 
            //!< p_op1 == p_op2            
            if (  op1  == '^' )
                return false; //!< If the association is right-left         
            return true; //!< Normal rule
        }
    }
}

std::vector<Token> infix_to_postfix(std::vector<Token> e){
    std::vector<Token> output;
    std::stack<Token> stack;

    for(Token t : e) 
    {
        if(t.type == Token::token_t::OPERAND)
            output.push_back( Token(t.value, Token::token_t::OPERAND) );
        else
        {
            if(t.value[0] == '(')
                stack.push( Token(t.value, Token::token_t::CLOSING) );
            else
            {
                if(t.value[0] == ')')
                {
                    while(stack.top().value[0] != '(')
                    {
                        output.push_back( Token(stack.top().value, Token::token_t::CLOSING));
                        stack.pop();
                    }
                    stack.pop();
                }
                else
                {
                    if(std::string("*^/%+-").find(t.value[0]) != std::string::npos)
                    {
                        while( not stack.empty() and has_higher_or_eq_precedence( stack.top().value[0], t.value[0]))
                        {
                            output.push_back(Token(stack.top().value, Token::token_t::OPERATOR));
                            stack.pop();
                        }
                        stack.push(Token(t.value, Token::token_t::OPERATOR));
                    }
                }
                
            }
            
        }
    }
    while (not stack.empty())
    {
        output.push_back(Token(stack.top().value, Token::token_t::OPERATOR));
        stack.pop();
    }

    return output;
    
}
