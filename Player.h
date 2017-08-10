#pragma once
#include "globals.h"

Vector2f ressurectPosition(100, 100);

class Player {
public:
	short health;
	short damage;
	short damageBasic;
	short damageBonus;

	float angle;
	float angleBonus;
	float hurtTimer, attacTimer;
	float speed;

	bool isFight;

	Vector2f pos;
	Sprite sprite;
	FloatRect rect;

	Player(Vector2f p) {
		pos = p;

		hurtTimer = 0;
		attacTimer = 0;
		angleBonus = 0;

		damageBasic = 10;
		damageBonus = 1;
		
		health = 200;

		speed = 0.4f;

		isFight = false;

		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(117, 0, 50, 50));
		sprite.setOrigin(25, 25);
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
		angle = getAngle(pos, mouse);
		rect = sprite.getGlobalBounds();

		if (attacTimer > 0 && attacTimer < 250) {
			if (angleBonus <= 90)
				angleBonus += 5;
		}
		if (attacTimer > 250 && attacTimer < 500) {
			if (angleBonus >= 0)
				angleBonus -= 5;
		}
		angle += angleBonus;
		sprite.setRotation(angle);
	}
	void update(float time, Vector2f mouse) {
		move(time);
		rotation(mouse);

		attacTimer += time;
		hurtTimer += time;

		if (attacTimer > MAX) attacTimer = MAX;
		if (hurtTimer > MAX) hurtTimer = MAX;

		damage = damageBasic * damageBonus;
		
		if (health <= 0) {
			health = 200;
			pos = ressurectPosition;
		}
	}
	void setAmmo() {
		axeSprite.setPosition(pos);
		axeSprite.setRotation(angle);

		pickaxeSprite.setPosition(pos);
		pickaxeSprite.setRotation(angle);

		weaponSprite.setPosition(pos);
		weaponSprite.setRotation(angle);
	}
	void attac() {
		if (attacTimer > 500) {
			attacTimer = 0;
		}
	}
};