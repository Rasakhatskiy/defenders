#pragma once
#include "globals.h"
class RessurectStone {
public:
	Sprite sprite;
	short health;
	RessurectStone() {
		health = 2000;
		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(100, 100, 100, 100));
		map[25][25][1] = 1024;
		map[25][26][1] = 1025;
		map[26][25][1] = 1025;
		map[26][26][1] = 1025;
		sprite.setPosition(25 * 50, 25 * 50);
	}
	void draw(RenderWindow &window) {
		window.draw(sprite);
	}
};