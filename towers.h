#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "globals.h"
#include "Bullets.h"
#include "Enemies.h"
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
	void rotation(Vector2f en) {
		float dX = en.x - pos.x;
		float dY = en.y - pos.y;
		angle = (atan2(dY, dX)) * 180 / 3.14159265;
		angle += 90;//kostil`
		sprite.setRotation(angle);
	}
	void draw(RenderWindow &window) {
		
		platformSpr.setPosition(pos);
		window.draw(platformSpr);
		window.draw(sprite);
	}
	void fire(std::vector<Enemy>& vectorEnemies, std::vector<Arrow>& vectorArrows) {
		float minDist = 66666666;//PATAMUCHTA
		Vector2f temp(pos);
		for (auto i = vectorEnemies.begin(); i != vectorEnemies.end(); i++) {
			float distance = sqrt((i->pos.x - pos.x)*(i->pos.x - pos.x) + (i->pos.y - pos.y)*(i->pos.y - pos.y));
			if (distance < minDist) {
				minDist = distance;
				temp = i->pos;
			}
		}
		if (isAttac) {
			rotation(temp);
			Arrow temp(pos, temp, angle);
			vectorArrows.push_back(temp);
			timer = 0;
		}
	}
	void update(RenderWindow &window, float time, std::vector<Enemy>& vectorEnemies, std::vector<Arrow>& vectorArrows) {
		timer += time / 10;
		if (timer > 100)isAttac = true;
		else isAttac = false;
		if (timer > 105)timer = 105;
		fire(vectorEnemies, vectorArrows);
		draw(window);
	}
};

