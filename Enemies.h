#pragma once
#include <SFML\Graphics.hpp>
#include "globals.h"
using namespace sf;

class Enemy {
public:
	unsigned short health;
	unsigned short damage;
	float angle;
	float attacTimer, hurtTimer;
	float coef;
	Vector2f pos;
	Texture texture;
	Sprite sprite;
	IntRect rect;
	bool isMove;

	Enemy(Vector2f p, unsigned short hp, unsigned short dmg) {
		attacTimer = 0;
		hurtTimer = 0;
		health = hp;
		coef = 50.0/health;
		pos = p;
		damage = dmg;
		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(17,17,34,34));
		sprite.setOrigin(17, 17);
		angle = 0;
		isMove = true;
		rect = IntRect(pos.x-17, pos.y-17, 34, 34);
	}
	void move(Vector2f tar, float time) {
		attacTimer += time;
		if (attacTimer > 500) attacTimer = 500;
		hurtTimer += time;
		if (hurtTimer > 500) hurtTimer = 500;

		if (isMove) {
			float distance = sqrt((tar.x - pos.x)*(tar.x - pos.x)
				+ (tar.y - pos.y)*(tar.y - pos.y));

			if (distance > 2) {
				float coefX = (tar.x - pos.x) / distance;
				float coefY = (tar.y - pos.y) / distance;
				if (coefX > 0) {
					if (map[(int)((pos.x + 17) / 50)][(int)(pos.y / 50)][1] == 0)
						pos.x += 0.05*time*(tar.x - pos.x) / distance;
				}
				else {
					if (map[(int)((pos.x - 17) / 50)][(int)(pos.y / 50)][1] == 0)
						pos.x += 0.05*time*(tar.x - pos.x) / distance;
				}
				if (coefY > 0) {
					if (map[(int)(pos.x / 50)][(int)((pos.y + 17) / 50)][1] == 0)
						pos.y += 0.05*time*(tar.y - pos.y) / distance;
				}
				else {
					if (map[(int)(pos.x / 50)][(int)((pos.y - 17) / 50)][1] == 0)
						pos.y += 0.05*time*(tar.y - pos.y) / distance;
				}	
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
		if (entityOnTheScreen(window, pos)) {
			window.draw(sprite);
			RectangleShape shape;
			shape.setFillColor(Color::Green);
			shape.setPosition(pos.x-17, pos.y + 10);
			shape.setSize(Vector2f(health*coef, 2));
			window.draw(shape);
		}
	}
};