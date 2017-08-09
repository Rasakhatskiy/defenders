#pragma once
#include "globals.h"




class healthBar {
public:
	int max;

	Text text;
	string str;
	RectangleShape shape;
	healthBar(int m) {
		shape.setSize(Vector2f(m, 20));
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
		shape.setSize(Vector2f(h, 20));
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