#pragma once
#include "globals.h"
class Player {
public:
	float health;
	Vector2f pos;
	bool isFight;
	Sprite sprite;
	float angle;
	float damage;
	Player(Vector2f p) {
		health = 200;
		pos = p;
		isFight = false;
		sprite.setTexture(tilesetTexture);
		sprite.setTextureRect(IntRect(117, 0, 50, 50));
		sprite.setOrigin(25, 25);
	}
	void move(float time) {
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			if(map[(int)(pos.x/50)][(int)((pos.y - 1) / 50)][1] == 0)
				pos.y -= time / 10;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			if (map[(int)(pos.x / 50)][(int)((pos.y + 1) / 50)][1] == 0)
				pos.y += time / 10;
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			if (map[(int)((pos.x -1)/ 50)][(int)(pos.y / 50)][1] == 0)
			pos.x -= time / 10;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			if (map[(int)((pos.x - 1) / 50)][(int)(pos.y / 50)][1] == 0)
			pos.x += time / 10;
		}
		sprite.setPosition(pos);
	}
	void rotation(Vector2f mouse) {
		float dX = mouse.x - pos.x;
		float dY = mouse.y - pos.y;
		angle = (atan2(dY, dX)) * 180 / 3.14159265;
		angle -= 90;
		sprite.setRotation(angle);
	}
};