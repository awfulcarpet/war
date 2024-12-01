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

struct Card * transfer(struct Deck **src, struct Deck **dst) {
	struct Deck *tmp = (*src)->next;
	(*src)->next = (*dst);
	*dst = *src;
	*src = tmp;
	return &(*dst)->card;
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
