#include <iostream>
void rotate ( int *first , int *n_first , int *last ) {
    auto slow { first };
    auto fast { n_first };
    while ( fast != last ){
        auto k { *slow };
        *slow = *fast;
        *fast = k;
        slow++;
        fast++;
    }
}
void print( int *A, int *last ){
    std::cout << "A = [ " << *A;
    A++;
    for (; A != last; A++)
    {
        std::cout << ", " << *A;
    }
    std::cout << " ] " << std::endl;
    
}
int main(){
    int A[]{ 1, 2, 3, 4, 5, 6, 7 };
    size_t size{ sizeof(A)/sizeof(A[0]) };
    rotate( A, A+2, A+size );
    print( A, A+size );
}