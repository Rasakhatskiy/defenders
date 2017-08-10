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

class circleMenu {
public:
	bool isOpen;
	short chosen;
	float angle;
	circleMenu() {
		isOpen = false;
		chosen = 0;
		angle = 0;
	}
	void choose(RenderWindow &window, Vector2f mouse) {
		Vector2f center = window.getView().getCenter();
		float dX = mouse.x - center.x;
		float dY = mouse.y - center.y;
		angle = (atan2(dY, dX)) * 180 / 3.14159265f;
		cout << center.x - mouse.x << " " << center.y - mouse.y << endl;
		menuSpr.setPosition(center);
		window.draw(menuSpr);

		axeSprite.setPosition(center.x + 232, center.y - 201);
		axeSprite.setRotation(45);
		axeSprite.setScale(2, 2);
		window.draw(axeSprite);
		axeSprite.setScale(1, 1);

		pickaxeSprite.setPosition(center.x + 307, center.y - 4);
		pickaxeSprite.setRotation(65);
		pickaxeSprite.setScale(2, 2);
		window.draw(pickaxeSprite);
		pickaxeSprite.setScale(1, 1);

		weaponSprite.setPosition(center.x + 201, center.y + 246);
		weaponSprite.setRotation(135);
		weaponSprite.setScale(2, 2);
		window.draw(weaponSprite);
		weaponSprite.setScale(1, 1);

		{
			if (angle > -113 && angle < -68) {
				chosen = 1;
			}
			if (angle > -68 && angle < -23) {
				chosen = 2;
			}
			if (angle > -23 && angle < 22) {
				chosen = 3;
			}
			if (angle > 22 && angle < 67) {
				chosen = 4;
			}
			if (angle > 67 && angle < 112) {
				chosen = 5;
			}
			if (angle > 112 && angle < 157) {
				chosen = 6;
			}
			if ((angle > 157 && angle < 180) || (angle > -180 && angle < -158)) {
				chosen = 7;
			}
			if (angle > -158 && angle < -113) {
				chosen = 8;
			}
		}

		Sprite t;
		
		if(chosen == 2){
			t = axeSprite;
		}
		if (chosen == 3) {
			t = pickaxeSprite;
		}
		if (chosen == 4) {
			t = weaponSprite;
		}
		t.setOrigin(35, 23);
		t.setPosition(center);
		t.setScale(3, 3);
		t.setRotation(45);
		window.draw(t);
		
		//angle += 180;
	}
};

/*class Rectangle {
private:
	Vector2f p1, p2, p3, p4;
public:
	Rectangle(float a, float b, float w, float h, float an) {
		p1 = Vector2f(a, b);
		p2 = Vector2f(a+w, b);
		p3 = Vector2f(a+w, b+h);
		p4 = Vector2f(a, b+h);
	}
};*/