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

#include<vector>
using std::vector;

void analyse_results(int n) //check results for a large number of five-hands
{
    int count[9] = {0};

	for (int t = 0 ;t < n ; t++)
    {
        DeckOfCards deckOfCards; // create DeckOfCards object
        deckOfCards.shuffle(); // shuffle the cards in the deck
        vector<int> p = deckOfCards.fivehand(1, 5);
        count[p[0]]++;
        if ( p[0] > 7)
            deckOfCards.deal(5);
    }

    for ( int c = 8; c >=0; c--)
    {
        cout << "LEVEL " << setw(7) << c << setw(10) << count[c] << endl;
    }
}

void compare_two_hands()
{
	DeckOfCards deckOfCards; // create DeckOfCards object
    deckOfCards.shuffle(); // shuffle the cards in the deck
    deckOfCards.deal(10);
    vector<int> p1 = deckOfCards.fivehand(1, 5);
    vector<int> p2 = deckOfCards.fivehand(6, 10);
    int r = deckOfCards.compare_two_fivehand(p1, p2);
}

int main()
{
		srand(time(0));

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


    //analyse_results(500);   
    compare_two_hands();
    return 0; // indicates successful termination
} // end main