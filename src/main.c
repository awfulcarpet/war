#include <stdio.h>
#include <assert.h>

#include <raylib.h>

#include "deck.h"

enum {
	WIDTH = 800,
	HEIGHT = 650,
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

	Vector2 cpu_play = {
		WIDTH / 2.0 - 75.0 / 2.0,
		140,
	};

	Vector2 player_play = {
		WIDTH / 2.0 - 75.0 / 2.0,
		HEIGHT - 140 - 105,
	};

	move_deck(cpu, cpu_deck);
	move_deck(player, player_deck);

	int update = 0;
	int state = 0;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GREEN);

		if (update) {
			printf("%d\n", state);
			switch (state++) {
				case 0:
				cpu->card.pos = cpu_play;
				player->card.pos = player_play;
				break;
				case 1:
					cpu->card.isfaceup = true;
					player->card.isfaceup = true;
				break;
				case 2:
					player->card.pos = player_deck;
					cpu->card.pos = cpu_deck;
					player->card.isfaceup = false;
					cpu->card.isfaceup = false;

					if (cpu->card.num > player->card.num) {
						player = transfer(player, &cpu);
						cpu = send_to_bottom(cpu);
						cpu = send_to_bottom(cpu);
						print_deck(cpu);
					}
					if (cpu->card.num < player->card.num) {
						cpu = transfer(cpu, &player);
						player = send_to_bottom(player);
						player = send_to_bottom(player);
						print_deck(player);
					}
					player = player->next;
					cpu = cpu->next;

					state = 0;
				break;
			}
			update = 0;
		}


		if (IsMouseButtonPressed(0)) {
			update = 1;
		}

		draw_deck(cpu);
		draw_deck(player);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
