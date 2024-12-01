#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "deck.h"

struct Deck * push(struct Deck *head, int num, enum SUIT suit) {
	struct Deck *new = calloc(1, sizeof(struct Deck));

	struct Card card = {
		suit,
		num,
	};

	if (head == NULL) {
		head = new;

		head->card = card;
		head->next = NULL;

		return head;
	}

	new->card = card;
	new->next = head;
	head = new;

	return head;
}

struct Deck *
transfer(struct Deck *src, struct Deck **dst) {
	struct Deck *tmp = src->next;
	src->next = (*dst);
	*dst = src;
	src = tmp;
	return src;
}

void
print_deck(struct Deck *deck) {
	char *suits[] = {
		"HEART",
		"DIAMOND",
		"SPADE",
		"CLUB"
	};
	if (deck == NULL) {
		printf("deck is empty\n");
		return;
	}

	do {
		printf("%d %s\n", deck->card.num, suits[deck->card.suit]);
		deck = deck->next;
	} while (deck != NULL);
}

struct Deck *
fill(struct Deck *deck) {
	for (int i = 1; i <= 13; i++) {
		for (int j = 0; j < 4; j++) {
			deck = push(deck, i, j);
		}
	}
	return deck;
}

struct Deck *
deal(struct Deck *deck, struct Deck **player1, struct Deck **player2) {
	for (int i = 0; i < 52; i++) {
		if (i % 2 == 0)
			deck = transfer(deck, player1);
		else
			deck = transfer(deck, player2);
	}
	return deck;
}

static struct Deck *
get_nth(struct Deck *deck, int n) {
	if (n == 0)
		return NULL;
	for (int i = 1; i < n; i++) {
		if (deck != NULL)
			deck = deck->next;
		else
			return NULL;
	}
	return deck;
}

struct Deck *
shuffle(struct Deck *deck) {

	for (int i = 0; i < 10000; i++) {
		struct Deck *card1 = get_nth(deck, GetRandomValue(1, 52));
		struct Deck *card2 = get_nth(deck, GetRandomValue(1, 52));

		struct Card tmp = card1->card;

		card1->card.num = card2->card.num;
		card1->card.suit = card2->card.suit;

		card2->card.num = tmp.num;
		card2->card.suit = tmp.suit;
	}

	return deck;
}


int
get_length(struct Deck *deck) {
	if (deck == NULL)
		return 0;

	int length = 1;
	while (deck->next != NULL) {
		length++;
		deck = deck->next;
	}
	return length;
}
