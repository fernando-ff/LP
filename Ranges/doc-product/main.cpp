#include <iostream>
#include <iterator>
using namespace std;
/*
 *Dot Product
 *def := Dados A, B arranjos quaisquers, talque a1,a2,..,an pertencem A e b1,b2,..,bn pertencem B.
 *       Sejam dotProduct uma função, talque
 *          A,B |-------> AxB  = { a1xb1, a2xb2,...., anxbn }
*/
int dotProduct( int *a_first, int *a_last, int *b_first ){
    int sum{0};
    for(; a_first != a_last; a_first++){
        sum = sum + ((*a_first) * (*b_first));
        b_first++;
    }
    return sum;
}
int main(void){
    int A[] { 1, 3, -5, 4, -2, -1 };
    auto result = dotProduct( A, A+3, A+3 );

    cout << "The result is:" << result << endl;
}