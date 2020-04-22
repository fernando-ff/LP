#include <iostream>
using namespace std;
/*
 *Scalar Multiplication
 *def:= Seja k um inteiro qualquer e Scalar Multiplication uma função, talque
 *A={a1,a2,..an} |-----> A={a1*k, a2*k,..., an*k},
 *onde A é um arranjo qualquer e a1,a2,..an são elementos pertencentes a A.
*/
void scalar_multiplication( int *first, int *last, int k){
    for (; first != last; first++)
    {
        *first = *first * k;
    }
    
}
void print( int A[], size_t size ){
    cout << "A = [ " << A[0];
    for (size_t i{1}; i < size; i++)
    {
        cout  <<", "<< A[i];
    }
    cout << " ]" << endl;
    
}
int main(){
    int A[] { 1, 2, -3, -4, -5, -6 };
    size_t size{ sizeof(A)/sizeof(A[0] ) };
    scalar_multiplication( A, A+size, 3);
    print( A, size );
}