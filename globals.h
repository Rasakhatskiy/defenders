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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;
using std::cout;
using std::cin;
using std::endl;
using std::string;

const VideoMode _Mode1600x900_(1600, 900, 32);
const VideoMode _Mode1280x720_(1280, 720, 32);
const short _MapSize_ = 100;

extern Texture tilesetTexture, arbaletTex, platformTex, playerTexture, enemyTexture;
extern Sprite grassSpr, tower1Spr, platformSpr, playerSpr, enemySpr, heartStoneSpr;
extern Font font;
extern View view;


extern unsigned short map[_MapSize_][_MapSize_][2];

void menu(RenderWindow &window);
void loadTextures();
void game(RenderWindow &window);
void drawMap(RenderWindow &window);
void setMap();
