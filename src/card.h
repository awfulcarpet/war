#include <raylib.h>
enum SUIT {
	HEART,
	DIAMOND,
	SPADE,
	CLUB,
};


struct Card {
	enum SUIT suit;
	int num; // 1-13 11, 12, 13 are jack, queen, king
	bool isfaceup;
	Vector2 pos;
	Vector2 new;
	Vector2 vel;
	bool is_moving;
};

void draw_card(struct Card *card);
void animate_card(struct Card *card);
void set_move(struct Card *card, Vector2 new, float sec);
