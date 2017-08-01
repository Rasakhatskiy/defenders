#include<SFML\Graphics.hpp>
#include "globals.h";
using namespace sf;

Texture tilesetTexture, arbaletTex, platformTex, playerTexture, enemyTexture;
Sprite grassSpr, tower1Spr, platformSpr, playerSpr, enemySpr, heartStoneSpr;

unsigned short map[100][100];

void loadTextures() {
	tilesetTexture.loadFromFile("res/defenders-tiles.png");
	grassSpr.setTexture(tilesetTexture);
	grassSpr.setTextureRect(IntRect(0, 0, 16, 16));

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

	playerSpr.setTexture(tilesetTexture);
	playerSpr.setTextureRect(IntRect(117, 0, 50, 50));
	playerSpr.setPosition(500, 500);
	playerSpr.setOrigin(32, 32);

}