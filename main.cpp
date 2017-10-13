// Fig. 8.27: fig08_27.cpp
// Card shuffling and dealing program.
#include "DeckOfCards.h" // DeckOfCards class definition

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <cstdlib> // prototypes for rand and srand
using std::rand;
using std::srand;

#include <ctime> // prototype for time
using std::time;

int main()
{
    //deckOfCards.deal(); // deal the cards in the deck

//    DeckOfCards deckOfCards; // create DeckOfCards object
//    deckOfCards.shuffle(); // shuffle the cards in the deck
//    deckOfCards.deal();
//    cout << "*****************************" << endl;
//
//    int * p = deckOfCards.fivehand(1, 5);
//    for ( int i = 0; i < 6; i++)
//        cout << setw(5) << p[i] ;
//    cout << endl;
//    cout << "*****************************" << endl;
//
//    int * q = deckOfCards.fivehand(6, 10);
//    for ( int i = 0; i < 6; i++)
//        cout << setw(5) << q[i] ;
//    cout << endl;
    
    
    srand(time(0));
    int count[9] = {0};
    for (int t=0 ;t <100000 ; t++)
    {
        DeckOfCards deckOfCards; // create DeckOfCards object
        deckOfCards.shuffle(); // shuffle the cards in the deck
        int * p = deckOfCards.fivehand(1, 5);
        count[*p]++;
        if ( p[0] > 7)
            deckOfCards.deal(5);
    }
    for ( int c = 8; c >=0; c--)
    {
        cout << "LEVEL " << setw(7) << c << setw(10) << count[c] << endl;
    }
    
    return 0; // indicates successful termination
} // end main


/**************************************************************************
 * (C) Copyright 1992-2005 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
