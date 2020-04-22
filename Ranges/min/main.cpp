#include <iostream>
#include <iterator>

using namespace std;

const int *min( const int *first, const int *last) {
    auto min { first+1 };
    while( first != last ){
        if( *min > *first ){
            min = first;
        }
        first++;
    }
    return min;
}
int main(void){
    int A[] { 1, 2, -3, -4, 5, -6 };
    size_t size { sizeof(A)/sizeof(A[0]) };
    auto result =  min( A, A+size );
    cout << *result << endl;
}