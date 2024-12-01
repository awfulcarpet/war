#include <stdio.h>
#include <assert.h>

#include <raylib.h>

#include "deck.h"

enum {
	WIDTH = 800,
	HEIGHT = 450,
};

int
main(void) {
	InitWindow(WIDTH, HEIGHT, "war card game");
	SetTargetFPS(60);

	struct Deck *deck = NULL;
	struct Deck *player = NULL;
	struct Deck *cpu = NULL;

	deck = fill(deck);
	assert(get_length(deck) == 52);

	deck = shuffle(deck);

	deck = deal(deck, &player, &cpu);
	assert(get_length(player) == get_length(cpu));

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(GREEN);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
