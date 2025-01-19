#include "card.h"

// Deck is a stack
struct Deck {
	struct Card card;
	struct Deck *next;
};

struct Deck * push(struct Deck *head, int num, enum SUIT suit);
struct Deck * transfer(struct Deck *src, struct Deck **dst);
struct Deck * fill(struct Deck *deck);
struct Deck * deal(struct Deck *deck, struct Deck **player1, struct Deck **player2);
struct Deck * shuffle(struct Deck *deck);
int get_length(struct Deck *deck);
void print_deck(struct Deck *deck);
void draw_deck(struct Deck *deck);
void update_deck(struct Deck *deck);
void move_deck(struct Deck *deck, Vector2 new);
struct Deck * get_nth(struct Deck *deck, int n);
struct Deck * send_to_bottom(struct Deck *deck);
void free_deck(struct Deck *deck);
