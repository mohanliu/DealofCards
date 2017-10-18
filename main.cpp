#include "DeckOfCards.h" // DeckOfCards class definitions

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <iomanip>
using std::setw;

#include <cstdlib> // prototypes for rand and srand
using std::rand;
using std::srand;

#include <ctime> // prototype for time
using std::time;

#include<vector>
using std::vector;

#include<algorithm>
using std::max_element;
using std::remove;

#include <string>
using std::string;

#include <sstream>
using std::stringstream;

void analyse_results(int n) //check results for a large number of five-hands
{
    int count[9] = {0};

	for (int t = 0 ;t < n ; t++)
    {
        DeckOfCards deckOfCards; // create DeckOfCards object
        deckOfCards.shuffle(); // shuffle the cards in the deck
        vector<int> first_five = {1, 2, 3, 4, 5};
        vector<int> p = deckOfCards.evaluate_fivecard_hand(first_five);
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
    vector<int> first_five = {1, 2, 3, 4, 5};
    vector<int> second_five = {6, 7, 8, 9, 10};
    vector<int> p1 = deckOfCards.evaluate_fivecard_hand(first_five);
    vector<int> p2 = deckOfCards.evaluate_fivecard_hand(second_five);

   	deckOfCards.show_hand(p1);
   	deckOfCards.show_hand(p2);

   	cout << endl;

    int r = deckOfCards.compare_two_hands(p1, p2);
    if ( r == 1 )
    	cout << "First Win" << endl;
    else if ( r == 2 )
    	cout << "Second Win" << endl;
    else if ( r == 0 )
    	cout << "Tie" << endl;
}

int dealer_redraw()
{
	DeckOfCards deckOfCards; // create DeckOfCards object
    deckOfCards.shuffle(); // shuffle the cards in the deck

    cout << "=================================" << endl;
    deckOfCards.deal(8);
    vector<int> first_five = {1, 2, 3, 4, 5};
    vector<int> old_eval = deckOfCards.evaluate_fivecard_hand(first_five);
    vector<int> new_cards = deckOfCards.deal_redraw_decision(old_eval);

    // Find out the cases the no need to redraw cards
    if ( *max_element(new_cards.begin(), new_cards.end()) == 5 )
        return -1;

    vector<int> new_eval = deckOfCards.evaluate_fivecard_hand(new_cards);

   	deckOfCards.show_hand(old_eval);
   	deckOfCards.show_hand(new_eval);
   	cout << endl;
   	
    int r = deckOfCards.compare_two_hands(old_eval,new_eval);
    if ( r == 1 )
    	cout << "Original is better" << endl;
    else if ( r == 2 )
    	cout << "Redraw helps" << endl;
    else if ( r == 0 )
    	cout << "Make no differences" << endl;
    
    return r;
}

void check_dealer_redraw(int n)
{
	int nn = 0;
    int k = n;
	for (int i = 0; i < n; i++)
	{
		int v = dealer_redraw();
		if ( v == 2 )
			nn++;
        if ( v == -1 )
            k--;
	}
	cout << nn << " out of " << k << ": Redraw helps" << endl;
}

void computer_vs_player()
{
	DeckOfCards deckOfCards; // create DeckOfCards object
    deckOfCards.shuffle(); // shuffle the cards in the deck

    cout << "=================================" << endl;
    deckOfCards.deal(16);

    // Dealer's Turn 
    vector<int> computer_eval;
    vector<int> first_five = {1, 2, 3, 4, 5};
    vector<int> old_eval = deckOfCards.evaluate_fivecard_hand(first_five);
    vector<int> new_cards = deckOfCards.deal_redraw_decision(old_eval);

    // Find out the cases the no need to redraw cards
    if ( *max_element(new_cards.begin(), new_cards.end()) == 5 )
        computer_eval = old_eval;
    else
    	computer_eval = deckOfCards.evaluate_fivecard_hand(new_cards);

    // Display dealer's final
    for ( int i = 6; i < 11; i++)
    	deckOfCards.display_card( computer_eval[ i ] );
    deckOfCards.show_hand(computer_eval);

    int player_start = *max_element(new_cards.begin(), new_cards.begin() + 5 );
    vector<int> player_cards = {player_start + 1, player_start + 2, 
    	player_start + 3, player_start + 4, player_start + 5};
    vector<int> player_original = deckOfCards.evaluate_fivecard_hand(player_cards);

    // Display player's original cards
    for ( int i = 6; i < 11; i++)
    	deckOfCards.display_card( player_original[ i ] );
    cout << "Number of cards I want to replace" << endl;

    // Players decide the card numbers to redraw
	string rawInput;
	vector<int> to_remove;
	cout << "Enter a number, or numbers separated by a space, between 1 and 1000." << endl;
	getline(cin, rawInput);
    stringstream stream(rawInput);

    while(1) { // Convert input values to a vector to_remove
        int n;
        stream >> n;
        if(!stream)
            break;
        to_remove.push_back(n);
    }

    for (int i = 0; i < to_remove.size(); i++)
    {
        int v = to_remove[i];
        player_cards.erase( 
                    remove( player_cards.begin(), player_cards.end(), v ), 
                    player_cards.end() );
        player_cards.push_back( player_start + 6 + i );
    } 

    for (int j = 0; j < player_cards.size(); j++)
        cout << player_cards[j] << endl;

}

int main()
{
	srand(time(0));
    //analyse_results(500);   
    //compare_two_hands();
    //check_dealer_redraw(10000);
    computer_vs_player();
    return 0;
} // end main