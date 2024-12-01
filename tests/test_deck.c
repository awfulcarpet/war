#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/deck.h"

void
pushing(void) {
	printf("starting pushing tests: ");
	struct Deck *deck = push(NULL, 1, HEART);
	assert(get_length(deck) == 1);

	deck = push(deck, 5, CLUB);
	assert(get_length(deck) == 2);
	assert(deck->card.num == 5);
	assert(deck->card.suit == CLUB);


	for (int i = 0; i < 10; i++) {
		deck = push(deck, i, i % 4);
	}
	assert(get_length(deck) == 12);

	printf("all pushing tests pass\n");
}

void
transfering(void) {
	printf("starting transfering tests: ");
	struct Deck *deck = push(NULL, 1, HEART);
	deck = push(deck, 5, CLUB);
	struct Deck *player = NULL;
	struct Deck *cpu = NULL;

	deck = transfer(deck, &player);
	deck = transfer(deck, &cpu);

	assert(player->card.suit == CLUB);
	assert(cpu->card.suit == HEART);
	assert(deck == NULL);
	printf("all transfering tests pass\n");
}

int
main(void) {
	pushing();
	transfering();
	/*struct Deck deck = {*/
	/*	{*/
	/*		HEART,*/
	/*		1,*/
	/*	},*/
	/*	NULL,*/
	/*};*/
	/*print_deck(&deck);*/
	return 0;
}

