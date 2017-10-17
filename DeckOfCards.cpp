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

#include<vector>
using std::vector;

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
        decksuit[ card-1 ] = row;
        deckface[ card-1 ] = column;
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

// Evaluate a five-card hand (given the indices of the five cards)
vector<int> DeckOfCards::evaluate_fivecard_hand(vector<int> &cards)
{    
    // Input a vector (length = 5) of number of cards in a deck, start from 1 to 52.
    // For example: cards = {1, 2, 3, 4 ,5}, then this function deal with the first 
    // five cards


    vector<int> output(11, 0); 
    // 1st Value: Level of your hand
    // 2-6: sorting from high to low
    // 7-11: number of cards
    
    int suitrank[ 4 ] = { 0 }; 
    int facerank[ 13 ] = { 0 }; 
    int row;
    int column;

    // Collect the faces and suits of these five cards
    for ( int n = 0; n < 5; n++)
    {
        row = decksuit[ cards[ n ] - 1 ];
        column = deckface[ cards[ n ] - 1 ];
        suitrank[ row ] += 1;
        facerank[ column ] += 1;
    }
    
    // Flush tag
    int ifflush = (find( suitrank, suitrank + 4, 5) !=  end(suitrank) )?  1 : 0;
    
    // Sorting base on faces, duplicate cards first, then from big to small
    int flag = 0;
    int c = 1;
    for ( int d = 5; d >= 1; d-- )
    {
        for (int i = 12; i >= 0; i-- )
        {
            if ( facerank[i] == d )
            {
                for ( int n = 0; n < d; n++ )
                    output[ c++ ] = i + 2;
                if ( d > 1 )
                    flag = flag * 10 + d;
            }
        }
    }

    // Get the order of the five cards
    for ( int f = 1; f <= 5; f++ )
    {
        for ( int k = 0; k < 6 - f; k++)
        {
            if ( output[ f ] == deckface[ cards[ k ] - 1 ] + 2 )
            {
                output[ f + 5 ] = cards[ k ];
                cards.erase(cards.begin()+k);
                break;
            }
        }
    }

    // Four of kind, Full House, Three of kind, two pairs and one pair
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

        // Check whether there is a straight
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
        
        // Check whether there is a flush in suit
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

void DeckOfCards::show_hand(vector<int> &eval)
{
    const static char *Level[9] = 
    {"Plain", "One Pair", "Two Pairs", "Three of kind", "Straight",
    "Flush", "Full House", "Four of kind", "Straight Flush"};
    cout << Level[ eval[ 0 ] ] << endl;
    for ( int i = 1; i < 11; i++)
    {
        cout << setw(4) << eval[i];
    }
    cout << endl;
}

// Compare two five-card hands
int DeckOfCards::compare_two_hands(vector<int> &eval1, vector<int> &eval2)
{
    for (int j = 0; j < 6; j++)
    {
        if (eval1[j] > eval2[j])
        {
            //cout << "First Win" << endl;
            return 1;
        }
        else if (eval1[j] < eval2[j])
        {
            //cout << "Second Win" << endl;
            return 2;
        }
    }
    //cout << "Tie" << endl;
    return 0;
}

// Dealer should decide whether or not to redraw one, two, three cards
vector<int> DeckOfCards::deal_redraw_decision(vector<int> &eval)
{
    vector<int> new_cards;
    int num_to_redraw = -1;

    if ( eval[ 0 ] == 3 )
    {
        cout << "Renew last two cards" << endl;
        num_to_redraw = 2;
        for (int i = 0; i < 3; i++)
            new_cards.push_back(eval[6+i]);
        for (int j = 0; j < 2; j++)
            new_cards.push_back(6 + j);
    }
    else if ( eval[ 0 ] == 2 )
    {
        cout << "Renew last card" << endl;
        num_to_redraw = 1;
        for (int i = 0; i < 4; i++)
            new_cards.push_back(eval[6+i]);
        for (int j = 0; j < 1; j++)
            new_cards.push_back(6 + j);
    }
    else if ( eval[ 0 ] == 1 )
    {   

        cout << "Renew last three cards" << endl;
        num_to_redraw = 3;
        for (int i = 0; i < 2; i++)
            new_cards.push_back(eval[6+i]);
        for (int j = 0; j < 3; j++)
            new_cards.push_back(6 + j);
    }
    else if ( eval[ 0 ] > 3 )
    {   
        cout << "No need to redraw" << endl;
        num_to_redraw = 0;
    }
    else
    {
        num_to_redraw = 0;
    }

    if ( num_to_redraw != -1 )
    {
        for (int i = 0; i < 5 - num_to_redraw; i++)
            new_cards.push_back(eval[6+i]);
        for (int j = 0; j < num_to_redraw; j++)
            new_cards.push_back(6 + j);            
    }

    return new_cards;
}