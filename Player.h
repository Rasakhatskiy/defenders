#pragma once
#include "globals.h"

Vector2f ressurectPosition(100, 100);

class Player {
public:
	short health;
	Vector2f pos;
	bool isFight;
	Sprite sprite;
	float angle;
	float damage;
	float hurtTimer, attacTimer;
	float speed = 0.4;
	IntRect rect;
	Player(Vector2f p) {
		hurtTimer = 0;
		attacTimer = 0;
		health = 200;
		pos = p;
		isFight = false;
		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(117, 0, 50, 50));
		sprite.setOrigin(25, 25);
	}
	void move(float time) {
		attacTimer += time;
		if (attacTimer > 500) attacTimer = 500;
		hurtTimer += time;
		if (hurtTimer > 500) hurtTimer = 500;
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			if(map[(int)(pos.x/50)][(int)((pos.y - 25) / 50)][1] == 0)
				pos.y -= speed*time;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			if (map[(int)(pos.x / 50)][(int)((pos.y + 25) / 50)][1] == 0)
				pos.y += speed*time;
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			if (map[(int)((pos.x -25)/ 50)][(int)(pos.y / 50)][1] == 0)
				pos.x -= speed*time;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			if (map[(int)((pos.x +25) / 50)][(int)(pos.y / 50)][1] == 0)
			pos.x += speed*time;
		}
		sprite.setPosition(pos);
	}
	void rotation(Vector2f mouse) {
		float dX = mouse.x - pos.x;
		float dY = mouse.y - pos.y;
		angle = (atan2(dY, dX)) * 180 / 3.14159265;
		angle -= 90;
		sprite.setRotation(angle);
		rect = IntRect(pos.x, pos.y, 25, 25);
	}
	void update(float time, Vector2f mouse) {
		move(time);
		rotation(mouse);
		if (health <= 0) {
			health = 200;
			pos = ressurectPosition;
		}
	}
};