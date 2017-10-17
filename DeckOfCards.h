#include<vector>
using std::vector;


// DeckOfCards class definition
class DeckOfCards
{
public:
    DeckOfCards(); // constructor initializes deck
    void shuffle(); // shuffles cards in deck
    void deal(int); // deals cards in deck
    vector<int> evaluate_fivecard_hand(vector<int> &);
    void show_hand(vector<int> &);
    int compare_two_hands(vector<int>&, vector<int>&);
    vector<int> deal_redraw_decision(vector<int> &cards);
private:
    int deck[ 4 ][ 13 ]; // represents deck of cards
    int decksuit[52];
    int deckface[52];
}; // end class DeckOfCards