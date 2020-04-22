#include <iostream>
void partition( int* first, int *last ){
    int k { 0 };
    auto slow { first };
    auto fast { first };
    while( fast != last){
        if( *fast < *last ){
            k = *slow ;
            *slow = *fast;
            *fast = k;
            slow++;
        }
        fast++;
    }
    k = *slow ;
    *slow = *last;
    *last = k;
}
void print( int *A, int *last ){
    std::cout << "A = [" << *A;
    A++;
    for (; A != last; A++)
    {
        std::cout << ", " << *A;
    }
    std::cout << " ]" << std::endl;
    
}
int main(){
    int A[]{ -5, 7, 10, 7, 8, 9, 1, 7, -2, 3 };
    size_t size { sizeof(A)/sizeof(A[0]) };
    partition( A, A+size-1 );
    print( A, A+size );
}