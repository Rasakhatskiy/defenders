#include "globals.h"
#include "Towers.h"
#include "Enemies.h"
#include "Player.h"
#include "RessurectStone.h"

void game(RenderWindow &window) {
	View view;
	view.reset(sf::FloatRect(100, 100, 1280, 720));
	Clock clock;
	RessurectStone ResStone;
	Player player(ResStone.sprite.getPosition());
	float angle = 0;
	float clickTimer = 0;

	loadTextures();
	setMap();

	std::vector<Enemy> enemiesVector;
	std::vector<Arrow> arrowsVector;
	std::vector<Tower> towersVector;
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

		if (clickTimer > 200) {
			if (Keyboard::isKeyPressed(Keyboard::T)) {
				int tx = pos.x / 50;
				int ty = pos.y / 50;
				if (map[tx][ty][1] == 0 && map[tx + 1][ty][1] == 0 && map[tx][ty + 1][1] == 0 && map[tx + 1][ty + 1][1] == 0) {
					map[tx][ty][1] = 10;
					map[tx + 1][ty][1] = 11;
					map[tx][ty + 1][1] = 11;
					map[tx + 1][ty + 1][1] = 11;
					towersVector.push_back(Tower(Vector2f(tx * 50, ty * 50), 100, 10));
				}

				clickTimer = 0;
			}
			if (Mouse::isButtonPressed(Mouse::Right)) {
				enemiesVector.push_back(Enemy(pos, 100, 10));
				clickTimer = 0;
			}
		}


		sf::Event Event;
		while (window.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				window.close();
		}


		//intersects with bullets
		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			for (auto j = arrowsVector.begin(); j != arrowsVector.end(); j++) {
				if (i->rect.intersects(j->rect)) {
					i->life -= 10;
					cout << i->life << endl;
					j->done = true;
				}
			}
		}



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


		//moving & rotating monsters
		//ya vas na origine vertel
		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			i->move(Vector2f(ResStone.sprite.getPosition().x + 50, ResStone.sprite.getPosition().y + 50), time);
			i->rotation(ResStone.sprite.getPosition());
		}
		//deleting monsters
		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			if (i->life <= 0 || i->life >1000) {
				enemiesVector.erase(i);
				break;
			}
		}


		player.move(time);
		player.rotation(pos);
		//VIEW
		if (player.pos.x <= 640 && player.pos.y <= 360) {
			view.setCenter(640, 360);
		}
		else {
			if (player.pos.x <= 640) {
				view.setCenter(640, player.pos.y);
			}
			else
				if (player.pos.y <= 360) {
					view.setCenter(player.pos.x, 360);
				}
				else {
					view.setCenter(player.pos);
				}
		}

		window.setView(view);

		drawMap(window);

		//update & draw towers
		for (auto i = towersVector.begin(); i != towersVector.end(); i++) {
			i->update(window, time, enemiesVector, arrowsVector);
		}

		ResStone.draw(window);

		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			i->draw(window);
		}
		for (auto i = arrowsVector.begin(); i != arrowsVector.end(); i++) {
			i->draw(window);
		}

		window.draw(player.sprite);
		window.display();
	}
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
	Sprite t;
	for (int i = 0; i < _MapSize_; i++) {
		for (int j = 0; j < _MapSize_; j++) {
			if (map[i][j][0] == 0) {
				t = grassSpr;
			}
			t.setPosition(i * 50, j * 50);
			window.draw(t);
		}
	}
}