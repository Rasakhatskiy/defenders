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
	float bonus_angle;
	FloatRect rect;
	Player(Vector2f p) {
		damage = 10;
		hurtTimer = 0;
		attacTimer = 0;
		health = 200;
		pos = p;
		isFight = false;
		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(117, 0, 50, 50));
		sprite.setOrigin(25, 25);
		bonus_angle = 0;
	}
	void move(float time) {
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
		angle += 180;
		
		rect = sprite.getGlobalBounds();
	}
	void update(float time, Vector2f mouse) {
		move(time);
		rotation(mouse);
		attacTimer += time;
		if (attacTimer > 7000) attacTimer = 7000;
		hurtTimer += time;
		if (hurtTimer > 500) hurtTimer = 500;
		if (health <= 0) {
			health = 200;
			pos = ressurectPosition;
		}
		
		if (attacTimer > 250 && attacTimer < 500) {
			if(bonus_angle <= 90)
				bonus_angle +=5;
		}
		if (attacTimer > 0 && attacTimer < 250) {
			if (bonus_angle >= 0)
				bonus_angle -=5;
		}
		angle += bonus_angle;
		sprite.setRotation(angle);
	}
	void attac() {
		if (attacTimer > 500) {
			attacTimer = 0;
		}
		
	}
};