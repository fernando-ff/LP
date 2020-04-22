#include <iostream>
/**
 * Dados os arranjos A,B quaisquers, tais que a1,a2,..an pertencem A.
 * Seja copy uma função talque
 * [a1,an),B |-----> B = {a1,a2,..,an-1} 
*/
int * copy( const int *first, const int *last, int *d_first ){

    while(first != last){
        *d_first = *first;
        d_first ++;
        first++; 
    }
    return d_first;
}
void print( int *B, int* b_last ){
    std::cout << "B = [ "<< *B ;
    B++;
    for (; B != b_last; B++)
    {
        
        std::cout << ", " << *B ;
    }
    std::cout << " ]" << std::endl;
    
}
int main(void) {
    int A[]{ 1, 2, 3, 4, 5 };
    int B[]{ 0, 0, 0 };
    
    auto b_last = copy( A+1, A+4, B);
    print( B, b_last );
}