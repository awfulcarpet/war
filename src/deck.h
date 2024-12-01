#include "card.h"

// Deck is a stack
struct Deck {
	struct Card card;
	struct Deck *next;
};

struct Deck * push(struct Deck *head, int num, enum SUIT suit);
struct Card * transfer(struct Deck **src, struct Deck **dst);
int get_length(struct Deck *deck);
void print_deck(struct Deck *deck);
