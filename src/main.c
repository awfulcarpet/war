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
	SetTargetFPS(30);

	struct Deck *deck = NULL;
	struct Deck *player = NULL;
	struct Deck *cpu = NULL;

	deck = fill(deck);
	assert(get_length(deck) == 52);

	deck = shuffle(deck);

	deck = deal(deck, &player, &cpu);
	assert(get_length(player) == get_length(cpu));

	player->card.pos = (Vector2) { 0, 0 };

	Vector2 player_deck = {
		WIDTH - 80,
		HEIGHT - 110,
	};

	Vector2 cpu_deck = {
		WIDTH - 80,
		0,
	};

	move_deck(cpu, cpu_deck);
	move_deck(player, player_deck);
	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(GREEN);


			update_deck(cpu);
			update_deck(player);

			draw_deck(cpu);
			draw_deck(player);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
