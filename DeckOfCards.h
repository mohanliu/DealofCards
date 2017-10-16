#include<vector>
using std::vector;


// DeckOfCards class definition
class DeckOfCards
{
public:
    DeckOfCards(); // constructor initializes deck
    void shuffle(); // shuffles cards in deck
    void deal(int); // deals cards in deck
    vector<int> fivehand(int, int);
    int compare_two_fivehand(vector<int>&, vector<int>&);
private:
    int deck[ 4 ][ 13 ]; // represents deck of cards
}; // end class DeckOfCards