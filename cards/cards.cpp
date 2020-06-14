/*
 * Exercicio:
 * 
 * 1) Ler cartas da entrada padrão.
 * 2) Implementar alg. find_if()
 * 3) Implementar alg. filter()
 * 4) Aplicar nas situações:
 *      4A) Usar find_if para: Achar a primeira carta cujo valor da face seja uma figura (valete, dama, rei).
 *      4B) Usar find_if para: Achar a primeira carta que seja vermelha.
 *      4C) Usar filter para: Selecionar em um vetor apenas as cartas de "hearts"
 *      4D) Usar filter para: Selecionar apenas as cartas com figuras.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

//=== Declarations
struct Card {
    enum class suit : int
    {
        clubs    = 0,
        diamonds = 1,
        hearts   = 2,
        spades   = 3,
    };

    suit s;
    short r; // rank

    // Ctro
    Card()
    {
        s = suit::clubs;
        r = 1;
    }
    // Ctro with arguments.
    Card( suit s_, short r_ )
    {
        s = s_;
        r = r_;
    }
};

typedef std::vector<Card>::iterator itr; // Another alias for iterator

namespace lp1 {
//=== Prototype of function that should belong to a library
    typedef bool (*PredFunc)( const Card& ); // Simple alias
    itr find_if( itr first, itr last, PredFunc pred );
    itr filter( itr first, itr last, PredFunc pred );
}

/// Overwritten stream inserting operator to support `Card` type.
std::ostream& operator<<( std::ostream& os, const Card & c )
{
    // String representation for the card elements.
    std::string ranks_to_str[]{ "as", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "joker"};
    std::string suits_to_str[]{ "clubs", "diamonds", "hearts", "spades" };

    // Recal that card rank goes from 1 to 13.
    os << ranks_to_str[c.r-1];
    if ( c.r <= 13 ) os << " of " << suits_to_str[static_cast<int>(c.s)];

    return os;
}

/// Returns true if the card received is a face rank: jack, queen, king or joker.
bool face_card( const Card& c )
{
    return c.r >= 11;
}

/// Returns true if the card received belongs to any of the red suits: diamonds or hearts.
bool red_suit( const Card& c )
{
    return c.s == Card::suit::diamonds or c.s == Card::suit::hearts ;
}

/// Returns true if the card received belongs to the hearts suit.
bool hearts_suit( const Card& c )
{
    return c.s == Card::suit::hearts ;
}




/*! Read cards from the stdin and store them in a vector.
 * \param inpupt_cards Input vector, passed by reference so the function may fill it up with cards.
 */
void read_cards( std::vector<Card> & input_cards )
{
    short suit{0}, rank{0};
    // Keep reading until there is no more data available
    while( std::cin >> suit >> rank )
    {
        // Converting from integer to enumeration.
        Card::suit suit_type;
        switch( suit ) {
            case 0: suit_type = Card::suit::clubs;
                    break;
            case 1: suit_type = Card::suit::diamonds;
                    break;
            case 2: suit_type = Card::suit::hearts;
                    break;
            case 3: suit_type = Card::suit::spades;
                    break;
        }
        // Insert new card into the vector.
        Card c{ suit_type, rank }; // carta temporaria.
        input_cards.push_back( c );
        // input_cards.push_back( Card{ suit_type, (unsigned short) rank } );
    }
}

/// Prints the cards passed via argument.
std::string to_string( itr first, itr last )
{
    // Send all cards to a **string stream**
    std::ostringstream oss;
    oss << "[ ";
    // Traversing the elements in the range
    while ( first != last )
    {
        oss << *first;
        // Check whether this is NOT the last element.
        if ( first+1 != last )
            oss << " - ";
        first++;
    }

    oss <<  " ]";

    return oss.str(); // Returns the content of the string-stream as a string.
}

int main(void)
{
    // Vector de cartas.
    std::vector< Card >  cards;

    // [1]=== Read and print cards. 
    read_cards( cards );

    std::cout << ">>> Received " << cards.size()
              << " cards. They are:\n" << to_string( cards.begin(), cards.end() ) << '\n';

    // [2]=== Create a backup of the original cards.

    std::vector< Card > backup{ cards };

    std::vector< Card > backup2; // Criei um backup vazio.
    backup2 = cards; // Copiando as cartas para o backup.

    // [3]=== Locate individual cards w/ find_if()

    std::cout << ">>> [4A] first face card is:\n";
    auto result = lp1::find_if( cards.begin(), cards.end(), face_card );
    std::cout << *result << '\n';

    std::cout << ">>> [4B] first red card is:\n";
    result = lp1::find_if( cards.begin(), cards.end(), red_suit );
    std::cout << *result << '\n';

    // [4]=== Locate group of cards w/ filter()

    auto new_last = lp1::filter( backup.begin(), backup.end(), hearts_suit );
    std::cout << ">>> [4C] all 'hearts' cards:\n"
              << to_string( backup.begin(), new_last ) << '\n';

    backup = cards; // Copy original over the backup
    new_last = lp1::filter( backup.begin(), backup.end(), face_card );
    std::cout << ">>> [4D] all face cards:\n"
              << to_string( backup.begin(), new_last ) << '\n';

    return 0;
}


//====== LIB CODE
// THIS SHOULD BE IN A SEPARETE SOURCE FILE, range_func.cpp/range_func.h

namespace lp1 {
    /*!
     * Finds and returns the first occurrence of a card that satisfies the predicate
     * `pred`, otherwise it returns `last` if such a card is not present. 
     */
    // Card * find_if( Card *first, Card *last )
    itr find_if( itr first, itr last, PredFunc pred )
    {
        // Traverse all elements in range.
        while( first != last )
        {
            // Check wheter the predicate is valid for the current element.
            if ( pred( *first ) ) return first; // Yes! Return it.
            first++; // Advance to the next element.
        }
        return last; // Searching failed.
    }

    /// Move to the begining of the range all cards that satisfy the predicate `pred`, preserving the relative order of the original range.
    /*!
     * The strategy of this algorithm is to divide the range into three regions of elements:
     * [1] those elements filtered,
     * [2] those elements rejected, and
     * [3] those elements yet to be processed.
     *
     * To mark the frontier between these three regions we need two extra pointers besides
     * the original first, and last: slow and fast.
     *
     * Initially the first two regions are empty. As the `fast` iterator advances, the
     * function assigns the current elemento to either of the first two regions.
     * When the third regions ends, we have the filtered elements in the first region.
     *
     *  first       slow    fast     last
     *      |         |       |      |
     *      v         v       v      v
     *    [ a, b, c | r s t | ? ? ? ]
     *
     *  So, during the execution of the algorithm, the regions are:
     *  [1] filtered:      [first, slow)
     *  [2] rejected:      [slow, fast)
     *  [3] not-processed: [fast, last).
     */
    itr filter( itr first, itr last, PredFunc pred )
    {
        auto slow(first);
        auto fast(first);
        // Use fast pointer to traver the entire range.
        while( fast != last )
        {
            // If predicate holds for the current element, we copy it to the front part of the range.
            if( pred( *fast )  )
            {
                // Copy inidividal values of the card.
                slow->r = fast->r;
                slow->s = fast->s;
                // Expand the limit of the region of the filtered elements.
                slow++;
            }
            fast++; // Always advances.
        }
        return slow;
    }
}
