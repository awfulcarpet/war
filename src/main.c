#include <raylib.h>
#include "card.h"

enum {
	WIDTH = 800,
	HEIGHT = 450,
};

int
main(void) {
	InitWindow(WIDTH, HEIGHT, "war card game");
	SetTargetFPS(60);
	struct Card card = {
		HEART,
		1
	};
	struct Card card_2 = {
		DIAMOND,
		2
	};
	struct Card card_3 = {
		CLUB,
		10
	};
	struct Card card_4 = {
		SPADE,
		12
	};

	while (!WindowShouldClose()) {
		BeginDrawing();
			draw_card(&card, 0, 0, 4);
			draw_card(&card_2,120, 0, 4);
			draw_card(&card_3,240, 0, 4);
			draw_card(&card_4,360, 0, 4);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
