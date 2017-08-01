#pragma once
#include <SFML\Graphics.hpp>
#include "globals.h"
using namespace sf;

class Enemy {
public:
	unsigned short life;
	unsigned short damage;
	float angle;
	Vector2f pos;
	Texture texture;
	Sprite sprite;
	IntRect rect;
	bool isMove;

	Enemy(Vector2f p, unsigned short hp, unsigned short dmg) {
		life = hp;
		pos = p;
		damage = dmg;
		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(17,17,34,34));
		sprite.setOrigin(25, 25);
		angle = 0;
		isMove = true;
		rect = IntRect(pos.x, pos.y, 34, 34);
	}
	void move(Vector2f tar, float time) {
		if (isMove) {
			float distance = sqrt((tar.x - pos.x)*(tar.x - pos.x)
				+ (tar.y - pos.y)*(tar.y - pos.y));

			if (distance > 2) {

				pos.x += 0.05*time*(tar.x - pos.x) / distance;
				pos.y += 0.05*time*(tar.y - pos.y) / distance;
			}
		}
		rect = IntRect(pos.x, pos.y, 34, 34);
		sprite.setPosition(pos);
	}
	void rotation(Vector2f tar) {
		float dX = tar.x - sprite.getPosition().x;
		float dY = tar.y - sprite.getPosition().y;
		float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
		sprite.setRotation(rotation - 90);
	}
	void draw(RenderWindow &window) {
		window.draw(sprite);
	}
};