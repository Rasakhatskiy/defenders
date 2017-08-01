#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Enemies.h"
#include "globals.h"
#include "Towers.h"



using namespace sf;
using std::cout;
using std::cin;
using std::endl;
using std::string;

//todo

class Player {
public:
	float health;
	Vector2f pos;
};



void menu() {

}
void setMap() {
	for (int i = 0; i < _MapSize_; i++) {
		for (int j = 0; j < _MapSize_; j++) {
			map[i][j] = 0;
		}
	}
}
void drawMap(RenderWindow &window) {
	Sprite t;
	for (int i = 0; i < _MapSize_; i++) {
		for (int j = 0; j < _MapSize_; j++) {
			if (map[i][j] == 0) {
				t = grassSpr;
			}
			t.setPosition(i * 16, j * 16);
			window.draw(t);
		}
	}
}
int main() {
	RenderWindow window(_Mode1280x720_, "Defenders");
	Clock clock;
	loadTextures();
	setMap();
	float angle = 0;
	float clickTimer = 0;
	std::vector<Enemy> enemiesVector;
	std::vector<Arrow> arrowsVector;
	Tower tower(Vector2f(100, 100), 100, 10);
	
	while (window.isOpen()) {
		window.clear();
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 900;
		clickTimer += time;
		if (clickTimer > 1000) clickTimer = 1000;
		
		Vector2i pixelPos = Mouse::getPosition(window);
		//cursor
		Vector2f pos = window.mapPixelToCoords(pixelPos);

		
		sf::Event Event;
		while (window.pollEvent(Event)){
			if (Event.type == sf::Event::Closed)
				window.close();
		}
		//intersects with bullets
		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			for (auto j = arrowsVector.begin(); j != arrowsVector.end(); j++) {
				if (i->rect.intersects(j->rect) ){
					i->life -= 10;
					cout << i->life << endl;
					j->done = true;
				}
			}
		}

		tower.rotation(pos, time);

		//moving arrows
		for (auto i = arrowsVector.begin(); i != arrowsVector.end(); i++) {
			i->move(time);
		}
		//deleting arrows
		for (auto i = arrowsVector.begin(); i != arrowsVector.end(); i++) {
			if (i->done) {
				arrowsVector.erase(i);
				break;
			}
		}
		
		if (clickTimer > 100) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Arrow t(tower.pos, pos, tower.angle);
				arrowsVector.push_back(t);
				clickTimer = 0;
			}
			if (Mouse::isButtonPressed(Mouse::Right)) {
				Enemy t(pos, 100, 10);
				enemiesVector.push_back(t);
				clickTimer = 0;
			}
		}
		//moving & rotating monsters
		//ya vas na origine vertel
		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			i->move(heartStoneSpr.getPosition(), time);
			i->rotation(heartStoneSpr.getPosition());
		}
		//deleting monsters
		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			if (i->life <= 0 || i->life >1000) {
				enemiesVector.erase(i);
				break;
			}
		}



		drawMap(window);
		window.draw(heartStoneSpr);
		
		tower.draw(window);	
		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			i->draw(window);
		}
		for (auto i = arrowsVector.begin(); i != arrowsVector.end(); i++) {
			i->draw(window);
		}
		window.display();
	}
}
