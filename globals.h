/*
░░░░██░░████████░░██░░░░░░░░░░░░░░░░░░░░░░░░
░░██▒▒██▒▒▒▒▒▒▒▒██▒▒██░░░░░░░░░░░░░░░░░░░░░░
░░██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██░░░░░░░░░░░░░░░░░░░░░░
░░██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██░░░░░░░░░░░░░░░░░░░░
██▒▒▒▒██▒▒▒▒██▒▒▒▒▒▒▒▒▒▒██░░░░░░░░░░░░░░░░░░
██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████░░░░░░░░░░░░░░
██▒▒▒▒▒▒████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████████████░░
██▒▒██▒▒██▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██
██▒▒▒▒████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████░░
██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██░░░░░
ONLY "EXTERN" "CONST" & PROTOTYPES
*/
#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

const VideoMode _Mode1600x900_(1600, 900, 32);
const VideoMode _Mode1280x720_(1280, 720, 32);
const short _MapSize_ = 100;

extern Texture tilesetTexture, arbaletTex, platformTex, playerTexture, enemyTexture;
extern Sprite grassSpr, tower1Spr, platformSpr, playerSpr, enemySpr, heartStoneSpr;

extern unsigned short map[_MapSize_][_MapSize_];

void menu();
void loadTextures();
