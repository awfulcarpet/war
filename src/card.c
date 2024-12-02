#include <raylib.h>
#include <assert.h>
#include <math.h>
#include "card.h"

static double
VectorDist(Vector2 start, Vector2 end) {
	return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
}

static Vector2
VectorAdd(Vector2 a, Vector2 b) {
	return (Vector2) {
		a.x + b.x,
		a.y + b.y,
	};
}

void
set_move(struct Card *card, Vector2 new, float sec) {
	if (card->is_moving)
		return;

	card->vel.x = (new.x - card->pos.x) / sec;
	card->vel.y = (new.y - card->pos.y) / sec;


	card->new = new;

	card->is_moving = true;
}

void
animate_card(struct Card *card) {
	double dt = GetFrameTime();
	Vector2 vel = {
		card->vel.x * dt,
		card->vel.y * dt,
	};
	if (card->is_moving == false)
		return;

	double curr_dist = VectorDist(card->pos, card->new);
	double next_dist = VectorDist(VectorAdd(card->pos, vel), card->new);

	if (VectorDist(card->pos, card->new) <= 15 || curr_dist < next_dist) {
		card->pos.x = card->new.x;
		card->pos.y = card->new.y;
		card->is_moving = false;
		return;
	}

	card->pos = VectorAdd(card->pos, vel);
}

void
draw_card(struct Card *card) {
	assert(card->num <= 13 && card->num >= 1);
	Rectangle card_outline = {
		card->pos.x,
		card->pos.y,
		75,
		105,
	};
	Vector2 card_center = {
		card_outline.x + card_outline.width/2,
		card_outline.y + card_outline.height/2,
	};



	if (card->isfaceup == false) {
		DrawRectangleRec(card_outline, BLACK);
		BeginScissorMode(card_outline.x, card_outline.y, card_outline.width, card_outline.height);
		for (int i = 0; i < 5; i++) {
			Vector2 start = {
				card_outline.x + i * card_outline.width / 5,
				card_outline.y
			};
			Vector2 end = {
				card_outline.x,
				card_outline.y + i * card_outline.height / 5,
			};
			DrawLineEx(start, end, 5, RED);
			end = (Vector2) {
				card_outline.x + i * card_outline.width / 5,
				card_outline.y + card_outline.height
			};
			start = (Vector2) {
				card_outline.x + card_outline.width,
				card_outline.y + i * card_outline.height / 5,
			};
			DrawLineEx(start, end, 5, BLUE);
		}
		EndScissorMode();
		DrawRectangleLinesEx(card_outline, 2, WHITE);
		return;
	}
	DrawRectangleRec(card_outline, WHITE);

	switch (card->suit) {
		case HEART: {
			Vector2 left_circle = {
				card_center.x - 12,
				card_center.y - 9
			};

			Vector2 right_circle = {
				card_center.x + 12,
				card_center.y - 9
			};

			DrawCircleSector(left_circle, 15, -180, 0, 20, RED);
			DrawCircleSector(right_circle, 15, -180, 0, 20, RED);

			Vector2 left_corner = {
				card_center.x+12 + 15,
				card_center.y -  9
			};
			Vector2 right_corner = {
				card_center.x-12 - 15,
				card_center.y - 9
			};

			Vector2 bottom_corner = {
				card_center.x,
				card_center.y +  30,
			};

			DrawTriangle(left_corner, right_corner, bottom_corner, RED);
			break;
		}
		case DIAMOND:
			DrawPoly(card_center, 4, card_outline.width / 3, 0, RED);
			break;
		case SPADE: {
			Vector2 left_circle = {
				card_center.x - 12,
				card_center.y
			};

			Vector2 right_circle = {
				card_center.x + 12,
				card_center.y
			};

			DrawCircleSector(left_circle, 15, 0, 180, 20, BLACK);
			DrawCircleSector(right_circle, 15, 0, 180, 20, BLACK);

			Vector2 left_corner = {
				card_center.x - 12 - 15,
				card_center.y,
			};
			Vector2 right_corner = {
				card_center.x + 12 + 15,
				card_center.y,
			};

			Vector2 top_corner = {
				card_center.x,
				card_center.y -  30,
			};

			DrawTriangle(left_corner, right_corner, top_corner, BLACK);

			DrawRectangle(card_center.x - 5 * 1.5, card_center.y, 15 , 30 , BLACK);
			break;
		}
		case CLUB:
			DrawCircle(card_center.x, card_center.y - 15, 15, BLACK);
			DrawCircle(card_center.x - 15, card_center.y, 15, BLACK);
			DrawCircle(card_center.x + 15, card_center.y, 15, BLACK);
			DrawRectangle(card_center.x - 7.25, card_center.y, 15 , 30 , BLACK);
			break;
		default:
			break;
	}

	const char card_logo[][3] = {
		"A",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"10",
		"J",
		"Q",
		"K",
	};

	Color text_color = (card->suit == HEART || card->suit == DIAMOND) ? BLACK : RED;

	const char *text = card_logo[card->num - 1];

	float fontsize = card_outline.width / 4;
	Vector2 text_dim = MeasureTextEx(GetFontDefault(), text, fontsize, 1);
	DrawText(text, card_center.x - text_dim.x / 2, card_center.y - text_dim.y / 2, fontsize, text_color);
}
