#pragma once
#include "globals.h"




class healthBar {
public:
	int max;

	Text text;
	string str;
	RectangleShape shape;
	healthBar(int m) {
		shape.setSize(Vector2f((float)m, (float)20));
		shape.setFillColor(Color::Red);
		
		max = m;
		text.setFont(font);
		text.setCharacterSize(8);
		text.setColor(Color::Black);
		
	}

	void draw(RenderWindow &window, int h) {
		str = std::to_string(h) + "/" + std::to_string(max);
		text.setString(str);
		//-_-_-_-__-text position
		Vector2f tpos(view.getCenter().x - 550, view.getCenter().y + 250);
		shape.setPosition(tpos);
		shape.setSize(Vector2f((float)h, (float)20));
		window.draw(shape);
	}
};

bool entityOnTheScreen(RenderWindow &window, Vector2f pos) {
	Vector2f center = window.getView().getCenter();
	float p1 = (center.x - window.getSize().x / 2)-50,
		p2 = (center.y - window.getSize().y / 2)-50,
		p3 = (center.x + window.getSize().x / 2)+50,
		p4 = (center.y + window.getSize().y / 2)+50;
	if (pos.x > p1 && pos.x < p3 && pos.y > p2 && pos.y < p4)
		return true;
	else return false;
}

short getWheelPosition(float angle) {
	if (angle > 246 && angle < 291) {
		return 1;
	}
	if (angle > 291 && angle < 336) {
		return 2;
	}
	if ((angle > 336 && angle < 360) || (angle > 0 && angle < 22)) {
		return 3;
	}
	if (angle > 22 && angle < 67) {
		return 4;
	}
	if (angle > 67 && angle < 112) {
		return 5;
	}
	if (angle > 112 && angle < 157) {
		return 6;
	}
	if (angle > 157 && angle < 201) {
		return 7;
	}
	if (angle > 201 && angle < 246) {
		return 8;
	}
	return -1;
}

class circleMenu {
public:
	bool isOpen;
	short chosen;
	float angle;
	Sprite axeOnWheel, pickAxeOnWheel, weaponOnWheel;
	circleMenu() {
		isOpen = false;
		chosen = 0;
		angle = 0;
	}
	void choose(RenderWindow &window, Vector2f mouse) {
		Vector2f center = window.getView().getCenter();
		angle = getAngle(center, mouse);
		chosen = getWheelPosition(angle);
		//cout << center.x - mouse.x << " " << center.y - mouse.y << endl;
		menuSpr.setPosition(center);
		//position of elements on wheel
		axeOnWheel = axeSprite;
		axeOnWheel.setPosition(center.x + 232, center.y - 201);
		axeOnWheel.setRotation(45);
		axeOnWheel.setScale(2, 2);
		axeOnWheel.setOrigin(47, -22);
		
		pickAxeOnWheel = pickaxeSprite;
		pickAxeOnWheel.setPosition(center.x + 307, center.y - 4);
		pickAxeOnWheel.setRotation(65);
		pickAxeOnWheel.setScale(2, 2);
		pickAxeOnWheel.setOrigin(40, -18);
	
		weaponOnWheel = weaponSprite;
		weaponOnWheel.setPosition(center.x + 201, center.y + 246);
		weaponOnWheel.setRotation(135);
		weaponOnWheel.setScale(2, 2);
		weaponOnWheel.setOrigin(54, -30);
		
		//what in center
		Sprite centerSprite;
		if(chosen == 2){
			centerSprite = axeSprite;
		}
		if (chosen == 3) {
			centerSprite = pickaxeSprite;
		}
		if (chosen == 4) {
			centerSprite = weaponSprite;
		}
		centerSprite.setOrigin(35, 23);
		centerSprite.setPosition(center);
		centerSprite.setScale(3, 3);
		centerSprite.setRotation(45);

		window.draw(menuSpr);
		window.draw(axeOnWheel);
		window.draw(pickAxeOnWheel);
		window.draw(weaponOnWheel);
		window.draw(centerSprite);
	}
};