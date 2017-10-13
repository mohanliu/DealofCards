#include <iostream>
using std::cout;
using std::endl;
using std::left;
using std::right;

#include <iomanip>
using std::setw;

#include <cstdlib> // prototypes for rand and srand
using std::rand;
using std::srand;

#include <ctime> // prototype for time
using std::time;

#include <algorithm>
using std::find;
using std::reverse;
using std::distance;

#include <iterator>
using std::begin;
using std::end;

#include "DeckOfCards.h" // DeckOfCards class definition

// DeckOfCards default constructor initializes deck
DeckOfCards::DeckOfCards()
{
    // loop through rows of deck
    for ( int row = 0; row <= 3; row++ )
    {
        // loop through columns of deck for current row
        for ( int column = 0; column <= 12; column++ )
        {
            deck[ row ][ column ] = 0; // initialize slot of deck to 0
        } // end inner for
    } // end outer for
    
//    srand(time(NULL));
    
} // end DeckOfCards default constructor

// shuffle cards in deck
void DeckOfCards::shuffle()
{
    int row; // represents suit value of card
    int column; // represents face value of card
    
    // for each of the 52 cards, choose a slot of the deck randomly
    for ( int card = 1; card <= 52; card++ )
    {
        do // choose a new random location until unoccupied slot is found
        {
            row = rand() % 4; // randomly select the row
            column = rand() % 13; // randomly select the column
        } while( deck[ row ][ column ] != 0 ); // end do...while
        
        // place card number in chosen slot of deck
        deck[ row ][ column ] = card;
    } // end for
} // end function shuffle

// deal cards in deck
void DeckOfCards::deal(int total)
{
    // initialize suit array
    static const char *suit[ 4 ] =
    { "Hearts", "Diamonds", "Clubs", "Spades" };
    
    // initialize face array
    static const char *face[ 13 ] =
    { "Deuce", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Jack", "Queen", "King" ,"Ace"};
    
    // for each of the 52 cards
    for ( int card = 1; card <= total; card++ )
    {
        // loop through rows of deck
        for ( int row = 0; row <= 3; row++ )
        {
            // loop through columns of deck for current row
            for ( int column = 0; column <= 12; column++ )
            {
                // if slot contains current card, display card
                if ( deck[ row ][ column ] == card )
                {
                    cout << setw( 5 ) << right << face[ column ]
                    << " of " << setw( 8 ) << left << suit[ row ]
                    << ( card % 2 == 0 ? '\n' : '\t' );
                } // end if
            } // end innermost for
        } // end inner for
    } // end outer for
    cout << endl;
} // end function deal

int * DeckOfCards::fivehand(int s, int f)
{
    // initialize suit array
    static const char *suit[ 4 ] =
    { "Hearts", "Diamonds", "Clubs", "Spades" };
    
    // initialize face array
    static const char *face[ 13 ] =
    { "Deuce", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Jack", "Queen", "King" ,"Ace"};

    static int output[ 6 ] = { 0 };
    
    int suitrank[ 4 ] = { 0 }; 
    int facerank[ 13 ] = { 0 }; 
    
    // for each of the 52 cards
    for ( int card = s; card <= f; card++ )
    {
        // loop through rows of deck
        for ( int row = 0; row <= 3; row++ )
        {
            // loop through columns of deck for current row
            for ( int column = 0; column <= 12; column++ )
            {
                // if slot contains current card, display card
                if ( deck[ row ][ column ] == card )
                {
                    //cout << setw( 5 ) << right << face[ column ]
                    //<< " of " << setw( 8 ) << left << suit[ row ]
                    //<< ('\n');
                    suitrank[ row ] += 1;
                    facerank[ column ] += 1;
                } // end if
            } // end innermost for
        } // end inner for
    } // end outer for
    
    // Flush tag
    int ifflush = (find( suitrank, suitrank + 4, 5) !=  end(suitrank) )?  1 : 0;
    
    // Four of kind, Full House, Three of kind, two pairs and one pair
    int flag = 0;
    int c = 1;
    for ( int d = 5; d >= 1; d-- )
    {
        for (int i = 12; i >= 0; i-- )
        {
            if ( facerank[i] == d )
            {
                for ( int n = 0; n < d; n++ )
                {
                    //cout << setw(9) << face[i];
                    output[ c++ ] = i + 2;
                }
                if ( d > 1 )
                    flag = flag * 10 + d;
            }
        }
    }
    //cout << endl;
    
    switch (flag) {
        case 4:
            //cout << "Four of kind" << endl;
            output[ 0 ] = 7;
            break;
        case 32:
            //cout << "Full house" << endl;
            output[ 0 ] = 6;
            break;
        case 3:
            //cout << "Three of kind" << endl;
            output[ 0 ] = 3;
            break;
        case 22:
            //cout << "Two pairs" << endl;
            output[ 0 ] = 2;
            break;
        case 2:
            //cout << "One pair" << endl;
            output[ 0 ] = 1;
            break;
            
        default:
            break;
    }

    // Straight or plain or Flush straight or Flush
    if ( flag != 0 )
        return output;
    else
    {
        int *firstcard = find(facerank,end(facerank),1);
        int *nextempty = find(firstcard+1,end(facerank),0);

        if ( nextempty - firstcard == 5 )
        {
            output[ 0 ] = 4;
        }
        else if ( firstcard == begin(facerank)     &&
                  nextempty == begin(facerank) + 4 &&
                  facerank[12] == 1 )
        {
            output[ 0 ] = 4;
            for ( int t = 1; t < 6; t++ )
                output[ t ] = 6 - t;
        }
        else
        {
            output[ 0 ] = 0;
        }
        
        if ( output[ 0 ] == 4 && ifflush == 1 )
        {
            output[ 0 ] = 8;
            //cout << "Straigh Flush" << endl;
        }
        else if ( output[ 0 ] == 4 && ifflush == 0 )
        {
            output[ 0 ] = 4;
            //cout << "Straigh" << endl;
        }
        else if ( output[ 0 ] == 0 && ifflush == 1 )
        {
            output[ 0 ] = 5;
            //cout << "Flush" << endl;
        }
        else
        {
            output[ 0 ] = 0;
            //cout << "Plain" << endl;
        }
        return output;
    }
}


void compare_2

