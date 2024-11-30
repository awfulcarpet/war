#include <raylib.h>
#include <assert.h>
#include "card.h"

void
draw_card(struct Card *card, int x, int y, float scale) {
	assert(card->num <= 13 && card->num >= 1);
	Rectangle card_outline = {
		x,
		y,
		25 * scale,
		35 * scale,
	};
	Vector2 card_center = {
		card_outline.x + card_outline.width/2,
		card_outline.y + card_outline.height/2,
	};
	DrawRectangleRec(card_outline, WHITE);

	switch (card->suit) {
		case HEART: {
			Vector2 left_circle = {
				card_center.x - 4*scale,
				card_center.y - scale * 3
			};

			Vector2 right_circle = {
				card_center.x + 4*scale,
				card_center.y - scale * 3
			};

			DrawCircleSector(left_circle, 5 * scale, -180, 0, 20, RED);
			DrawCircleSector(right_circle, 5 * scale, -180, 0, 20, RED);

			Vector2 left_corner = {
				card_center.x+4*scale + 5*scale,
				card_center.y - scale * 3
			};
			Vector2 right_corner = {
				card_center.x-4*scale - 5*scale,
				card_center.y - scale * 3
			};

			Vector2 bottom_corner = {
				card_center.x,
				card_center.y + scale * 10,
			};

			DrawTriangle(left_corner, right_corner, bottom_corner, RED);
			break;
		}
		case DIAMOND:
			DrawPoly(card_center, 4, card_outline.width / 3, 0, RED);
			break;
		case SPADE: {
			Vector2 left_circle = {
				card_center.x - 4*scale,
				card_center.y
			};

			Vector2 right_circle = {
				card_center.x + 4*scale,
				card_center.y
			};

			DrawCircleSector(left_circle, 5 * scale, 0, 180, 20, BLACK);
			DrawCircleSector(right_circle, 5 * scale, 0, 180, 20, BLACK);

			Vector2 left_corner = {
				card_center.x - 4*scale - 5 * scale,
				card_center.y,
			};
			Vector2 right_corner = {
				card_center.x + 4*scale + 5 * scale,
				card_center.y,
			};

			Vector2 top_corner = {
				card_center.x,
				card_center.y - scale * 10,
			};

			DrawTriangle(left_corner, right_corner, top_corner, BLACK);

			DrawRectangle(card_center.x - 5 * scale / 2, card_center.y, 5 * scale, 10* scale, BLACK);
			break;
		}
		case CLUB:
			DrawCircle(card_center.x, card_center.y - 5 * scale, 5 * scale, BLACK);
			DrawCircle(card_center.x - 5*scale, card_center.y, 5 * scale, BLACK);
			DrawCircle(card_center.x + 5*scale, card_center.y, 5 * scale, BLACK);
			DrawRectangle(card_center.x - 5 * scale / 2, card_center.y, 5 * scale, 10* scale, BLACK);
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

	float fontsize = 4 * scale * 1.5;
	Vector2 text_dim = MeasureTextEx(GetFontDefault(), text, fontsize, 1);
	DrawText(text, card_center.x - text_dim.x / 2, card_center.y - text_dim.y / 2, fontsize, text_color);
}
