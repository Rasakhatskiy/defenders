#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "globals.h"
using namespace sf;

class Tower {
public:
	short health;
	short damage;
	Sprite sprite;
	Vector2f pos;
	float angle;
	float timer;
	bool isAttac;
	Tower(Vector2f p, short hp, short dmg) {
		pos = p;
		health = hp;
		damage = dmg;
		sprite.setTexture(arbaletTex);
		sprite.setPosition(pos);
		sprite.setOrigin(60, 60);
		angle = 0;
		timer = 0;
	}
	void rotation(Vector2f en, float time) {
		float dX = en.x - pos.x;
		float dY = en.y - pos.y;
		angle = (atan2(dY, dX)) * 180 / 3.14159265;
		timer += time / 10;
		if (timer > 100)isAttac = true;
		if (timer > 105)timer = 105;
		angle += 90;
		sprite.setRotation(angle);
	}
	void draw(RenderWindow &window) {
		
		platformSpr.setPosition(pos);
		window.draw(platformSpr);
		window.draw(sprite);
	}
};

class Arrow {
public:
	Vector2f pos, tar;
	IntRect rect;
	float speed;
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
	}
	void move(float time) {
		//distance to target
		float distance = sqrt((tar.x - pos.x)*(tar.x - pos.x) + (tar.y - pos.y)*(tar.y - pos.y));
	
		if (distance > 35) {
			//moving
			pos.x += speed*time*(tar.x - pos.x) / distance;
			pos.y += speed*time*(tar.y - pos.y) / distance;
		}
		else {
			done = true;
		}
		rect = IntRect(pos.x, pos.y, 8, 21);
		sprite.setPosition(pos);
	}
	void draw(RenderWindow &window) {
		window.draw(sprite);
	}
};
