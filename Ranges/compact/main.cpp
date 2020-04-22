#include <iostream>

int * compact( int *first, int *last){
    auto slow { first };
    auto fast { first };
    while( fast != last ){
        if( *fast > 0){
            *slow = *fast;
            slow++;
        }
        fast++;
    }
    return last = slow;
}
void print( int *A, int *last){
    std::cout << "A = [ " << *A;
    A++;
    while( A != last){
        std::cout << ", " << *A;
        A++;
    }
    std::cout << " ]" << std::endl;
}
int main(void){
    int A[]{ -2, -8, 2, 7, -3, 10, 1, 0, -3, 7 };
    size_t size { sizeof(A)/sizeof(A[0]) };
    print( A, A+size );
    auto last = compact( A, A+size );
    print( A, last );
}