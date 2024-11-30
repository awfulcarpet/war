enum SUIT {
	HEART,
	DIAMOND,
	SPADE,
	CLUB,
};


struct Card {
	enum SUIT suit;
	int num; // 1-13 11, 12, 13 are jack, queen, king
};

void draw_card(struct Card *card, int x, int y, float scale);
