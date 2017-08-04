#include<SFML\Graphics.hpp>
#include "globals.h";
#include "Enemies.h"
#include "Bullets.h"
using namespace sf;

Texture tilesetTexture, arbaletTex, platformTex, playerTexture, enemyTexture, grassTex;
Sprite grassSpr, tower1Spr, platformSpr, playerSpr, enemySpr, heartStoneSpr, wallSpr;
Font font;
View view;
Text fpsText;


unsigned short map[100][100][2];

void loadTextures() {
	view.reset(sf::FloatRect(100, 100, 1280, 720));
	tilesetTexture.loadFromFile("res/defenders-tiles.png");

	grassTex.loadFromFile("res/grass.png");
	grassSpr.setTexture(grassTex);
	//grassSpr.setTextureRect(IntRect(0, 0, 16, 16));

	arbaletTex.loadFromFile("res/arbalet.png");

	platformTex.loadFromFile("res/platform.png");
	platformSpr.setTexture(platformTex);
	platformSpr.setOrigin(50, 50);

	tower1Spr.setTexture(arbaletTex);
	tower1Spr.setOrigin(16, 27);
	tower1Spr.setPosition(200, 200);

	
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
}