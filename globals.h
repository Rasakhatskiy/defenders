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
using std::vector;

const VideoMode _Mode1600x900_(1600, 900, 32);
const VideoMode _Mode1280x720_(1280, 720, 32);
const short _MapSize_ = 100;
const short mapTile = 50;
const int MAX = 60000;

extern Texture tilesetTexture, arbaletTex, menuTex;
extern Sprite grassSpr, platformSpr, heartStoneSpr, wallSpr, menuSpr, gridSpr,
playerSpr, enemySpr,
axeSprite, pickaxeSprite, weaponSprite;
extern Font font;
extern View view;

extern Text fpsText;

extern unsigned short map[_MapSize_][_MapSize_][2];

void menu(RenderWindow &window);
void loadTextures();
void game(RenderWindow &window);
void drawMap(RenderWindow &window, bool isGrid);
void setMap();
void setView(RenderWindow &window, Vector2f pos);
bool entityOnTheScreen(RenderWindow &window, Vector2f pos);
float getAngle(Vector2f position, Vector2f target);
void setOriginsOfSprite(Sprite &sprite, float &clickTimer);
void day_nightCircle(RenderWindow &window, float gameTime);