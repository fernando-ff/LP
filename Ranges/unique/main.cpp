#include <iostream>


int * unique( int *first, int *last){
    auto slow { first };
    auto fast { first };
    while( fast != last){
        auto check { first };
        auto aux { 1 };
        while( check != slow ){
            if( *check == *fast){
                aux = 0;
                break;
            }
            check++;
        }
        if( aux == 1){
            *slow = *fast;
            slow++; 
        }
        fast++;
    }
    return slow;
}
void print( int *A, int* last ) {
    std::cout << "A = [ " << *A;
    for (; A != last; A++)
    {
        std::cout << ", " << *A;
    }
    std::cout << " ]" << std::endl;
    
}

int main(void) {
    int A[] { 1, 2, 1, 2, 3, 3, 1, 2, 4, 5, 3, 4, 5 };
    size_t size{ sizeof(A)/sizeof(A[0]) };
    auto last = unique( A, A+size );
    print( A, last );
}