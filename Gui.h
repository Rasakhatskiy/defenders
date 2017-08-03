#pragma once
#include "globals.h"

class healthBar {
public:
	int max;
	Sprite sprite;
	Text text;
	string string;
	healthBar(int m) {
		max = m;
		text.setFont(font);
		text.setCharacterSize(8);
		text.setColor(Color::Black);
		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(167, 0, 1, 40));
	}

	void draw(RenderWindow &window, int h) {
		string = std::to_string(h) + "/" + std::to_string(max);
		text.setString(string);
		//-_-_-_-__-text position
		for (int i = 0; i < h; i++) {
			Vector2f tpos(view.getCenter().x-550, view.getCenter().y + 250);
			sprite.setPosition(tpos.x + 1*i, tpos.y);
			window.draw(sprite);
		}
	}
};