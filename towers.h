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
	FloatRect rect;
	float angle;
	float timer;
	float coef;
	float hurtTimer;
	bool isAttac;
	int posOnMapX, posOnMapY;
	Tower(Vector2f p, short hp, short dmg) {
		timer = 0;
		hurtTimer = 0;
		pos = p;
		pos.x += 50;
		pos.y += 50;

		health = hp;
		coef = 100.f/health;
		damage = dmg;

		sprite.setTexture(arbaletTex);
		sprite.setPosition(pos);
		sprite.setOrigin(60, 60);
		rect = sprite.getGlobalBounds();
		
		posOnMapX = (int)((pos.x-50) / 50);
		posOnMapY = (int)((pos.y-50) / 50);
		map[posOnMapX][posOnMapY][1] = 10;
		map[posOnMapX + 1][posOnMapY][1] = 11;
		map[posOnMapX][posOnMapY + 1][1] = 11;
		map[posOnMapX + 1][posOnMapY + 1][1] = 11;
	}
		void clearMap() {
		map[posOnMapX][posOnMapY][1] = 0;
		map[posOnMapX + 1][posOnMapY][1] = 0;
		map[posOnMapX][posOnMapY + 1][1] = 0;
		map[posOnMapX + 1][posOnMapY + 1][1] = 0;
	}
	void rotation(Vector2f en) {
		float dX = en.x - pos.x;
		float dY = en.y - pos.y;
		angle = (atan2(dY, dX)) * 180 / 3.14159265f;
		angle += 90;//kostil`
		sprite.setRotation(angle);
	}
	void draw(RenderWindow &window) {
		
		platformSpr.setPosition(pos);
		if (entityOnTheScreen(window, pos)) {
			window.draw(platformSpr);
			window.draw(sprite);
			RectangleShape shape;
			shape.setFillColor(Color::Green);
			shape.setPosition(pos.x-50, pos.y + 45);
			shape.setSize(Vector2f(coef*health, 2));
			window.draw(shape);
		}
		
	}
	void fire(std::list<Enemy>& vectorEnemies, std::list<Arrow>& vectorArrows) {
		float minDist = 66666666.f;//PATAMUCHTA
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
	void update(RenderWindow &window, float time, std::list<Enemy>& vectorEnemies, std::list<Arrow>& vectorArrows) {
		timer += time / 10;
		if (timer > 100)isAttac = true;
		else isAttac = false;
		hurtTimer += time;
		if (hurtTimer > 500) hurtTimer = 500;
		if (timer > 105)timer = 105;
		fire(vectorEnemies, vectorArrows);
		draw(window);
	}
};

class Wall {
public:
	short health;
	Vector2f pos;
	Vector2i posOnMap;
	FloatRect rect;
	float coef;
	Wall(Vector2f p, short h/*, short typo*/) {
		health = h;
		pos = p;
		posOnMap = Vector2i((int)(pos.x / 50), (int)(pos.y / 50));
		pos = Vector2f((float)(posOnMap.x * 50), (float)(posOnMap.y * 50));
		map[posOnMap.x][posOnMap.y][1] = 1;
		rect = FloatRect(pos.x, pos.y, 50, 50);
		coef = 45.0f / health;
	}
	void clearMap() {
		map[posOnMap.x][posOnMap.y][1] = 0;
	}
	void draw(RenderWindow &window) {
		if (entityOnTheScreen(window, pos)) {
			//wallSpr.setPosition(pos);
			//window.draw(wallSpr);
			RectangleShape shape;
			shape.setFillColor(Color::Green);
			shape.setPosition(pos.x, pos.y + 45);
			shape.setSize(Vector2f(coef*health, 2));
			window.draw(shape);
		}
	}
};

//extern vector<Tower> towersVector;
//extern vector<Wall> wallsVector;


extern list<Tower> towersVector;
extern list<Wall> wallsVector;