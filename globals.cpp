#include <SFML\Graphics.hpp>
#include "globals.h";
#include "Enemies.h"
#include "Bullets.h"
using namespace sf;

Texture tilesetTexture, arbaletTex, menuTex;
Sprite grassSpr, platformSpr, playerSpr, enemySpr, heartStoneSpr, wallSpr, menuSpr,
axeSprite, pickaxeSprite, weaponSprite;
Font font;
View view;
Text fpsText;


unsigned short map[100][100][2];

void loadTextures() {
	view.reset(sf::FloatRect(100, 100, 1280, 720));
	tilesetTexture.loadFromFile("res/defenders-tiles.png");
	arbaletTex.loadFromFile("res/arbalet.png");

	grassSpr.setTexture(tilesetTexture);
	grassSpr.setTextureRect(IntRect(50, 200, 50, 50));

	

	platformSpr.setTexture(tilesetTexture);
	platformSpr.setTextureRect(IntRect(0, 100, 100, 100));
	platformSpr.setOrigin(50, 50);

	heartStoneSpr.setTexture(tilesetTexture);
	heartStoneSpr.setTextureRect(IntRect(100, 100, 100, 100));
	heartStoneSpr.setPosition(500, 500);
	heartStoneSpr.setOrigin(32, 32);

	font.loadFromFile("Trebuchet.ttf");

	wallSpr.setTexture(tilesetTexture);
	wallSpr.setTextureRect(IntRect(0, 200, 50, 50));

	fpsText.setFont(font);
	fpsText.setCharacterSize(16);
	fpsText.setColor(Color::White);

	axeSprite.setTexture(tilesetTexture);
	axeSprite.setTextureRect(IntRect(167, 12, 69, 15));
	axeSprite.setOrigin(50, +24);
	axeSprite.setScale(-1, -1);

	pickaxeSprite.setTexture(tilesetTexture);
	pickaxeSprite.setTextureRect(IntRect(178, 27, 60, 20));
	pickaxeSprite.setOrigin(40, +17);
	pickaxeSprite.setScale(-1, 1);

	weaponSprite.setTexture(tilesetTexture);
	weaponSprite.setTextureRect(IntRect(167, 0, 71, 12));
	weaponSprite.setOrigin(50, +24);
	weaponSprite.setScale(-1, 1);

	menuTex.loadFromFile("res/menu.png");
	menuSpr.setTexture(menuTex);
	menuSpr.setOrigin(300, 300);
}
void setView(RenderWindow &window, Vector2f pos) {
	Vector2f viewPos = pos;
	//left side
	if (pos.x <= window.getSize().x / 2) {
		viewPos.x = (float)window.getSize().x / 2;
	}
	//top side
	if (pos.y <= window.getSize().y / 2) {
		viewPos.y = (float)window.getSize().y / 2;
	}
	//right side
	if (pos.x >= _MapSize_ * mapTile - window.getSize().x / 2) {
		viewPos.x = _MapSize_ * mapTile - (float)window.getSize().x / 2;
	}
	//bottom side
	if (pos.y >= _MapSize_ * mapTile - window.getSize().y / 2) {
		viewPos.y = _MapSize_ * mapTile - (float)window.getSize().y / 2;
	}
	view.setCenter(viewPos);
	//accept the view
	window.setView(view);
}
void setMap() {
	for (int i = 0; i < _MapSize_; i++) {
		for (int j = 0; j < _MapSize_; j++) {
			map[i][j][0] = 0;
			map[i][j][1] = 0;
		}
	}

}
void drawMap(RenderWindow &window) {
	long counter = 0;
	Sprite t, empty;
	Vector2f center = window.getView().getCenter();
	int p1 = (int)((center.x - window.getSize().x / 2) / 50) - 1,
		p2 = (int)((center.y - window.getSize().y / 2) / 50) - 1,
		p3 = (int)((center.x + window.getSize().x / 2) / 50) + 1,
		p4 = (int)((center.y + window.getSize().y / 2) / 50) + 1;
	if (p1 < 0)p1 = 0;
	if (p2 < 0)p2 = 0;
	if (p3 > _MapSize_) p3 = _MapSize_;
	if (p4 > _MapSize_) p4 = _MapSize_;

	for (int i = p1; i < p3; i++) {
		for (int j = p2; j < p4; j++) {
			if (map[i][j][0] == 0) {
				t = grassSpr;
			}
			else {
				t = empty;
			}
			t.setPosition((float)(i * 50), (float)( j * 50));
			window.draw(t);
			if (map[i][j][1] == 1) {
				t = wallSpr;
			}
			else {
				t = empty;
			}
			t.setPosition((float)(i * 50), (float)(j * 50));
			window.draw(t);
		}
	}
}
float getAngle(Vector2f position, Vector2f target) {
	float dX = target.x - position.x;
	float dY = target.y - position.y;
	float angle = (atan2(dY, dX)) * 180 / 3.14159265f;
	if (angle < 0) {
		angle = 360 + angle;
	}
	return angle;
}