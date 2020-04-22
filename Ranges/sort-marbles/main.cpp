#include <iostream>
#include <assert.h>
#include <iterator>

enum ball_t { B=0, W=1 };
ball_t * sortMarbles( ball_t *first, ball_t *last ){
    auto slow { first };
    auto fast { first };
    while( fast != last){
        if( B == *fast ){
            auto k { *slow };
            *slow = *fast;
            *fast = k;
            slow++;
        }
        fast++;
    }
    return slow;
}
void print( ball_t *A, ball_t * last ){
    std::cout << "A = [ " << *A;
    for (; A != last; A++)
    {
        std::cout << ", " << *A;
    }
    std::cout << " ]" << std::endl;
    
}
int main(void) {
    ball_t A[] { W, B, B, W, W, B, W };
    auto size { sizeof(A)/sizeof(ball_t) };
    ball_t A_sorted[] { B, B, B, W, W, W, W };
    auto result = sortMarbles( A, A+size );
    print( A, A+size );
    assert( std::distance( A,result ) == 3 );
    for ( size_t i{0} ; i < size; i++){
        assert( A[i] == A_sorted[i]);
    }
    return 0;
}