#include <stdio.h>
#include <assert.h>

#include <raylib.h>

#include "deck.h"

enum {
	WIDTH = 800,
	HEIGHT = 650,
};

struct Deck *deck = NULL;
struct Deck *player = NULL;
struct Deck *cpu = NULL;

struct Deck *cpu_next = NULL;
struct Deck *player_next = NULL;

Vector2 player_deck = {
	WIDTH - 80,
	HEIGHT - 110,
};

Vector2 cpu_deck = {
	WIDTH - 80,
	5,
};

Vector2 cpu_play = {
	WIDTH / 2.0 - 75.0 / 2.0,
	140,
};

Vector2 player_play = {
	WIDTH / 2.0 - 75.0 / 2.0,
	HEIGHT - 140 - 105,
};

Vector2 cpu_war = {
	WIDTH / 2.0 - ((75.0 / 2.0 + 5) * 5),
	10,
};

Vector2 player_war = {
	WIDTH / 2.0 - ((75.0 / 2.0 + 5) * 5),
	HEIGHT - 105 - 10,
};



void
reset(void)
{
	deck = fill(deck);

	assert(get_length(deck) == 52);

	deck = shuffle(deck);
	deck = deal(deck, &player, &cpu);

	assert(get_length(player) == get_length(cpu));
	assert(get_length(player) == 26);
	assert(deck == NULL);

	move_deck(cpu, cpu_deck);
	move_deck(player, player_deck);
}

int
main(void) {
	InitWindow(WIDTH, HEIGHT, "war card game");
	SetTargetFPS(30);

	reset();

	cpu->card.num = 5;
	player->card.num = 5;

	player->next->card.num = 9;

	int update = 0;
	int state = 0;
	int offset = 0;
	int game_set = 0;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GREEN);

		if (update) {
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
					if (cpu->card.num == player->card.num) {
						offset++;
						goto war;
					}

					player->card.pos = player_deck;
					cpu->card.pos = cpu_deck;
					player->card.isfaceup = false;
					cpu->card.isfaceup = false;

					if (cpu->card.num > player->card.num) {
						player = transfer(player, &cpu);
						cpu = send_to_bottom(cpu);
						cpu = send_to_bottom(cpu);
						state = 0;
						break;
					}

					if (cpu->card.num < player->card.num) {
						cpu = transfer(cpu, &player);
						player = send_to_bottom(player);
						player = send_to_bottom(player);
						state = 0;
						break;
					}
				break;

				// war
				war:
					if (cpu == NULL)
						break;
					if (player == NULL)
						break;

					cpu_next = cpu;
					player_next = player;
					int i = 0;
					for (i = 0; i < offset; i++) {
						cpu_next = cpu_next->next;
						player_next = player_next->next;

						if (cpu_next == NULL)
							break;
						if (player_next == NULL)
							break;

						cpu_next->card.pos = cpu_war;
						cpu_next->card.pos.x += i * 5;

						player_next->card.pos = player_war;
						player_next->card.pos.x += i * 3;
					}
				break;
				case 3:
					if (cpu_next == NULL || player_next == NULL) {
						goto end;
					}

					cpu_next->card.isfaceup = true;

					player_next->card.isfaceup = true;

					if (player_next->card.num != cpu_next->card.num) {
						state = 4;
						break;
					}
					state = 2;
					break;
				case 4: {
					if (cpu_next == NULL || player_next == NULL)
						goto end;

					if (cpu_next->card.num > player_next->card.num) {
						do {
							player->card.pos = cpu_deck;
							player->card.isfaceup = false;
							cpu->card.pos = cpu_deck;
							cpu->card.isfaceup = false;
							player = transfer(player, &cpu);
						} while (player != NULL && player != player_next);
						if (player == NULL)
							goto end;

						player->card.pos = cpu_deck;
						player->card.isfaceup = false;
						player = transfer(player, &cpu);

						do {
							cpu->card.pos = cpu_deck;
							cpu->card.isfaceup = false;
							cpu = send_to_bottom(cpu);
						} while (cpu != cpu_next);
						if (cpu == NULL)
							goto end;

						cpu->card.pos = cpu_deck;
						cpu->card.isfaceup = false;
						cpu = send_to_bottom(cpu);
					}

					if (cpu_next->card.num < player_next->card.num) {
						do {
							cpu->card.pos = player_deck;
							cpu->card.isfaceup = false;
							player->card.pos = player_deck;
							player->card.isfaceup = false;
							cpu = transfer(cpu, &player);
						} while (cpu != NULL && cpu != cpu_next);
						if (cpu == NULL)
							goto end;

						cpu->card.pos = player_deck;
						cpu->card.isfaceup = false;
						cpu = transfer(cpu, &player);

						do {
							player->card.pos = player_deck;
							player->card.isfaceup = false;
							player = send_to_bottom(player);
						} while (player != NULL && player != player_next);
						if (player == NULL)
							goto end;

						player->card.pos = player_deck;
						player->card.isfaceup = false;
						player = send_to_bottom(player);
					}

					cpu_next = player_next = NULL;
					offset = 0;
					state = 0;
					break;
				}
				default:
					state = 0;
					break;
			}
			update = 0;
		}


		if (cpu == NULL || player == NULL || game_set) {
			end:
			game_set = 1;
			if (cpu == NULL || cpu_next == NULL)
				DrawText("Player Wins", WIDTH / 2 - MeasureText("Player Wins", 20) / 2, HEIGHT / 2, 20, BLACK);
			else if (player == NULL || player_next == NULL)
				DrawText("CPU Wins", WIDTH / 2 - MeasureText("CPU Wins", 20) / 2, HEIGHT / 2, 20, BLACK);

			DrawText("Right Click To Play Again", WIDTH / 2 - MeasureText("Right Click To Play Again", 10) / 2, HEIGHT / 2 + 30, 10, BLACK);

			if (IsMouseButtonPressed(1)) {
				free_deck(cpu);
				free_deck(player);
				free_deck(deck);

				cpu = player = deck = NULL;

				reset();

				state = 0;
				game_set = 0;
			}
		} else if (IsMouseButtonPressed(0)) {
			update = 1;
		}

		draw_deck(player);
		draw_deck(cpu);
		DrawText(TextFormat("%d\n", get_length(player)), player_deck.x + 10, player_deck.y + 10, 30, WHITE);
		DrawText("Player", player_deck.x, player_deck.y - 30, 20, BLACK);

		DrawText("CPU", cpu_deck.x, cpu_deck.y + 105 + 10, 20, BLACK);
		DrawText(TextFormat("%d\n", get_length(cpu)), cpu_deck.x + 10, cpu_deck.y + 10, 30, WHITE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
