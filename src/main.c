#include "raylib.h"
#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

#include "card.h"

enum {
	WIDTH = 800,
	HEIGHT = 450,
};

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

void UpdateDrawFrame(void);

int
main(void) {
	InitWindow(WIDTH, HEIGHT, "war card game");

	#if defined(PLATFORM_WEB)
		emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
	#else
		SetTargetFPS(60);
		while (!WindowShouldClose()) {
			UpdateDrawFrame();
		}
	#endif
	CloseWindow();
	return 0;
}

void UpdateDrawFrame(void) {
			BeginDrawing();
			ClearBackground(GREEN);
				draw_card(&card, 0, 0, 4);
				draw_card(&card_2,120, 0, 4);
				draw_card(&card_3,240, 0, 4);
				draw_card(&card_4,360, 0, 4);
			EndDrawing();
}
