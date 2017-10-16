// DeckOfCards class definition
class DeckOfCards
{
public:
    DeckOfCards(); // constructor initializes deck
    void shuffle(); // shuffles cards in deck
    void deal(int); // deals cards in deck
    int * fivehand(int, int);
    void compare_two_fivehand(int *, int *);
private:
    int deck[ 4 ][ 13 ]; // represents deck of cards
}; // end class DeckOfCards