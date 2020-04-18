#include <iostream> // std::cout, std::endl
#include<iterator> // std::begin(), std::end()

void negate( int *first, int *last ){
    while ( first != last )
    {
        if( *first < 0 ) *first = -*first;
        else *first = -*first;
        first++;
    }
}
void print( int Vet[], size_t size){
    std::cout << "Vet = [ ";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << Vet[i] << ", ";
    }
    std::cout << "]";
}

int main(){
    int Vet[]{ 1, 2, -3, -4, -5, -6 };
    size_t size{ sizeof(Vet)/sizeof(Vet[0]) };
   //negate( std::begin(Vet), std::end(Vet) );
    //print( Vet, size );
    //negate( std::begin(Vet)+2, std::end(Vet) );
    //print( Vet, size );
    negate( std::begin(Vet)+3, std::end(Vet)+4 );
    print( Vet, size );

    
    return 0;
}