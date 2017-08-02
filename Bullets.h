#pragma once
#include "globals.h"

class Arrow {
public:
	Vector2f pos, tar, coef;
	IntRect rect;
	float speed, lifetimer;
	Sprite sprite;
	bool done;
	Arrow(Vector2f p, Vector2f t, float r) {
		pos = p;
		tar = t;
		speed = 0.5;
		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(0, 17, 11, 26));
		sprite.setOrigin(4, 21);
		sprite.setRotation(r);
		done = false;
		rect = IntRect(pos.x, pos.y, 11, 26);
		lifetimer = 5000;

		float distance = sqrt((tar.x - pos.x)*(tar.x - pos.x) + (tar.y - pos.y)*(tar.y - pos.y));
		coef.x = (tar.x - pos.x) / distance;
		coef.y = (tar.y - pos.y) / distance;
	}
	void move(float time) {
		lifetimer -= time / 0.5;
		
		pos.x += speed*time*coef.x;
		pos.y += speed*time*coef.y;	
		if (lifetimer <= 0) {
			done = true;
		}
		rect = IntRect(pos.x, pos.y, 8, 21);
		sprite.setPosition(pos);
	}
	void draw(RenderWindow &window) {
		window.draw(sprite);
	}
};
