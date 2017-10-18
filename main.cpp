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



    // Player's Turn
    int player_start = *max_element(new_cards.begin(), new_cards.begin() + 5 );
    vector<int> player_cards = {player_start + 1, player_start + 2, 
    	player_start + 3, player_start + 4, player_start + 5};
    vector<int> player_original = deckOfCards.evaluate_fivecard_hand(player_cards);

    // Display player's original cards
    cout << "Here is your card: " << endl;
    for ( int i = 6; i < 11; i++)
    	deckOfCards.display_card( player_original[ i ] );

    // Players decide the card numbers to redraw
	string rawInput;
	vector<int> to_remove;
	int flag;
	int c;
	cout << "Number of cards you want to replace (no more than 3 cards)" << endl;
	do
	{
		getline(cin, rawInput);
    	stringstream stream(rawInput);
    	c = 0;
    	flag = 0;

    	while(1) { // Convert input values to a vector to_remove
        	int n;
       		stream >> n;
       		if(!stream)
            	break;

       		if ( n > player_start + 5 || n < player_start + 1 )
       		{
       			cout << "Wrong numbers. Please enter again: ";
       			flag = 1;
       			break;
       		}
       		if ( c > 3 )
       		{
       			cout << "Too many cards. Please enter less: ";
       			flag = 1;
       			break;
       		}

        	to_remove.push_back(n);
        	c++;
    	}
    } while ( flag == 1 );

    // Player redraw the cards
    for (int i = 0; i < to_remove.size(); i++)
    {
        int v = to_remove[ i ];
        player_cards.erase( 
                    remove( player_cards.begin(), player_cards.end(), v ), 
                    player_cards.end() );
        player_cards.push_back( player_start + 6 + i );
    } 

    // Player's final cards
    vector<int> player_final = deckOfCards.evaluate_fivecard_hand(player_cards);

    // Show results
    int r = deckOfCards.compare_two_hands(player_final,computer_eval);
    cout << endl;
    if ( r == 1 )
    {
    	cout << "=========================" << endl;
    	cout << "You win! Congratulations." << endl;
    	cout << "=========================" << endl;
    }
    else if ( r == 2 )
    {
    	cout << "=============================" << endl;
    	cout << "Computer wins. Try next time." << endl;
    	cout << "=============================" << endl;
	}
    else if ( r == 0 )
    {
    	cout << "===========" << endl;
    	cout << "It's a tie." << endl;
    	cout << "===========" << endl;
	}

    // Display Infomation
    cout << endl;
    cout << "Computer final hand: " << endl;  
    deckOfCards.show_hand( computer_eval );      
    for ( int i = 6; i < 11; i++) 
    	// Display dealer's final
    	deckOfCards.display_card( computer_eval[ i ] );
    cout << endl;

    cout << "Your final hand" << endl;
    deckOfCards.show_hand( player_final );
    for ( int i = 6; i < 11; i++)
    	// Display player's final
    	deckOfCards.display_card( player_final[ i ] );

    cout << endl;
    deckOfCards.deal(16);


}

int main()
{
    srand(time(0));
    //analyse_results(500000);   
    //compare_two_hands();
    //check_dealer_redraw(10000);
    computer_vs_player();
    return 0;
} // end main
