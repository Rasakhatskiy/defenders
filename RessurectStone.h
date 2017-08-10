#pragma once
#include "globals.h"
class RessurectStone {
public:
	Sprite sprite;
	short health;
	float coef;
	float hurtTimer;
	Vector2f pos;
	RessurectStone(Vector2f p) {
		health = 2000;
		hurtTimer = 0;

		pos = p;
		coef = 100.f / health;

		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(100, 100, 100, 100));
		sprite.setPosition(pos);
		//sprite.setOrigin(50, 50);

		map[25][25][1] = 1024;
		map[25][26][1] = 1025;
		map[26][25][1] = 1025;
		map[26][26][1] = 1025;

		
	}
	void update(float time) {
		hurtTimer += time;
		if (hurtTimer >= 10000)hurtTimer = 10000;
		if (health <= 0)health = 0;
	}
	void draw(RenderWindow &window) {
		if (entityOnTheScreen(window, pos)) {
			window.draw(sprite);
			RectangleShape shape;
			shape.setFillColor(Color::Green);
			shape.setPosition(pos.x - 50, pos.y + 45);
			shape.setSize(Vector2f(health*coef, 2));
			window.draw(shape);
		}
	}
};