#include <iostream>
using namespace std;


/*
 *Swap, 
 *definição := Dados a, b end. de memorias quaisquers, swap troca os valores de a por b e de b por a. 
*/
void swap(int* start, int *end){
    auto k { *start };
    *start = *end;
    *end = k;
}
/* 
 * Seja reverse uma função, talque 
 * A={a1,a2,...,an} |------> {an,...,a2,a1} 
 * onde A é um aranjo qualquer e a1,a2,..an pertencem a A.
*/
void reverse( int *first, int *last){
    auto end { last-1 };
    for (auto start { first } ;start != end ; start++)
    {
        swap( start, end );
        end--;
        
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
int main(void){
    int A[] { 1, 2, 3, 4, 5 };
    size_t size { sizeof(A)/sizeof(A[0]) };
    reverse( A, A+size );
    print( A, size );
}