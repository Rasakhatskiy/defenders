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
	FloatRect rect;
	bool isMove;

	Enemy(Vector2f p, unsigned short hp, unsigned short dmg) {
		attacTimer = 0;
		hurtTimer = 0;
		angle = 0;
		health = hp;
		pos = p;
		damage = dmg;

		coef = 50.f / health;

		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(17,17,34,34));
		sprite.setOrigin(17, 17);

		
		isMove = true;
		rect = sprite.getGlobalBounds();
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
						pos.x += 0.05f*time*(tar.x - pos.x) / distance;
				}
				else {
					if (map[(int)((pos.x - 17) / 50)][(int)(pos.y / 50)][1] == 0)
						pos.x += 0.05f*time*(tar.x - pos.x) / distance;
				}
				if (coefY > 0) {
					if (map[(int)(pos.x / 50)][(int)((pos.y + 17) / 50)][1] == 0)
						pos.y += 0.05f*time*(tar.y - pos.y) / distance;
				}
				else {
					if (map[(int)(pos.x / 50)][(int)((pos.y - 17) / 50)][1] == 0)
						pos.y += 0.05f*time*(tar.y - pos.y) / distance;
				}	
			}
		}
		rect = sprite.getGlobalBounds();

		sprite.setPosition(pos);
	}
	void rotation(Vector2f tar) {
		sprite.setRotation(getAngle(pos, tar)+90);
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
	void update(RenderWindow &window, Vector2f tar, float time) {
		move(tar, time);
		rotation(tar);
		draw(window);
	}
	void collisionWithMobs(Vector2f mob,float time) {
		float distance = sqrt((mob.x - pos.x)*(mob.x - pos.x)
			+ (mob.y - pos.y)*(mob.y - pos.y));
		if (distance < 34) {//enemy diameter
			float coefX = (mob.x - pos.x) / distance;
			float coefY = (mob.y - pos.y) / distance;

			if (coefX < 0) {
				if (map[(int)((pos.x + 17) / mapTile)][(int)(pos.y / mapTile)][1] == 0)
					pos.x -= 0.09f*time*(mob.x - pos.x) / distance;
			}
			else {
				if (map[(int)((pos.x - 17) / mapTile)][(int)(pos.y / mapTile)][1] == 0)
					pos.x -= 0.09f*time*(mob.x - pos.x) / distance;
			}
			if (coefY < 0) {
				if (map[(int)(pos.x / mapTile)][(int)((pos.y + 17) / mapTile)][1] == 0)
					pos.y -= 0.09f*time*(mob.y - pos.y) / distance;
			}
			else {
				if (map[(int)(pos.x / mapTile)][(int)((pos.y - 17) / mapTile)][1] == 0)
					pos.y -= 0.09f*time*(mob.y - pos.y) / distance;
			}
		}
	}
};

//extern vector<Enemy> enemiesVector;
extern list<Enemy> enemiesVector;