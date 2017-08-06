#include "globals.h"
#include "Towers.h"
#include "Enemies.h"
#include "Player.h"
#include "RessurectStone.h"
#include "Gui.h"

void game(RenderWindow &window) {
	
	Clock clock;
	float angle = 0;
	float clickTimer = 0;

	loadTextures();
	setMap();
	RessurectStone ResStone;
	Player player(Vector2f(ResStone.sprite.getPosition().x + 100, ResStone.sprite.getPosition().y + 100));
	healthBar bar(1000);

	vector<Enemy> enemiesVector;
	vector<Arrow> arrowsVector;
	vector<Tower> towersVector;
	vector<Wall> wallsVector;

	

	float lastTime = 0;
	float fpsTimer = 0;
	while (window.isOpen()) {
		
		float time = clock.getElapsedTime().asMicroseconds();
		//clock.restart();

		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / (currentTime);
		lastTime = currentTime;
		time = time / 900;



		Vector2f fpsPos(view.getCenter().x - 300, view.getCenter().y + 200);
		if (fpsTimer > 100) {
			fpsText.setString("FPS: " + std::to_string(fps));
			fpsTimer = 0;
		}
		fpsText.setPosition(fpsPos);

		
		clickTimer += time;
		fpsTimer += time;

		if (fpsTimer > 1000) fpsTimer = 1000;
		if (clickTimer > 1000) clickTimer = 1000;

		Vector2i pixelPos = Mouse::getPosition(window);
		//cursor
		Vector2f pos = window.mapPixelToCoords(pixelPos);

		//view
		{
			Vector2f viewPos = player.pos;
			//left side
			if (player.pos.x <= window.getSize().x / 2) {
				viewPos.x = window.getSize().x / 2;
			}
			//top side
			if (player.pos.y <= window.getSize().y / 2) {
				viewPos.y = window.getSize().y / 2;
			}
			//right side
			if (player.pos.x >= _MapSize_ * 50 - window.getSize().x / 2) {
				viewPos.x = _MapSize_ * 50 - window.getSize().x / 2;
			}
			//bottom side
			if (player.pos.y >= _MapSize_ * 50 - window.getSize().y / 2) {
				viewPos.y = _MapSize_ * 50 - window.getSize().y / 2;
			}
			view.setCenter(viewPos);
			//accept the view
			window.setView(view);
		}
		window.clear();
		drawMap(window);

		if (clickTimer > 200) {
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				wallsVector.push_back(Wall(Vector2f(pos.x, pos.y), 1000));
				clickTimer = 0;
			}


			if (Keyboard::isKeyPressed(Keyboard::P)) {
				player.health+=5;
			}
			if (Keyboard::isKeyPressed(Keyboard::O)) {
				player.health -= 5;
			}
			if (Keyboard::isKeyPressed(Keyboard::T)) {
				int tx = pos.x / 50;
				int ty = pos.y / 50;
				if (map[tx][ty][1] == 0 && map[tx + 1][ty][1] == 0 && map[tx][ty + 1][1] == 0 && map[tx + 1][ty + 1][1] == 0)
					towersVector.push_back(Tower(Vector2f(tx * 50, ty * 50), 1000, 10));
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
			//Arrows
			for (auto j = arrowsVector.begin(); j != arrowsVector.end(); j++) {
				if (i->rect.intersects(j->rect)) {
					i->health -= 10;
					j->done = true;
				}
			}
			//player
			if (i->rect.intersects(player.rect) && player.hurtTimer > 100 && i->attacTimer >100) {
				player.health -= i->damage;
				player.hurtTimer = 0;
				i->attacTimer = 0;
			}
			//towers
			for (auto j = towersVector.begin(); j != towersVector.end(); j++) {
				if (i->rect.intersects(j->rect) && j->hurtTimer > 300 && i->attacTimer > 100) {
					j->health -= i->damage;
					j->hurtTimer = 0;
				}
			}
			//walls
			for (auto j = wallsVector.begin(); j != wallsVector.end(); j++) {
				if (i->rect.intersects(j->rect)  && i->attacTimer > 100) {
					j->health -= i->damage;
					j->draw(window);
					i->attacTimer = 0;
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
		//deleting monsters
		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			if (i->health <= 0 || i->health >1000) {
				enemiesVector.erase(i);
				break;
			}
		}
		//deleting towers
		for (auto i = towersVector.begin(); i != towersVector.end(); i++) {
			if (i->health <= 0) {
				i->clearMap();
				towersVector.erase(i);
				break;
			}
		}
		//deleting walls
		for (auto i = wallsVector.begin(); i != wallsVector.end(); i++) {
			if (i->health <= 0) {
				i->clearMap();
				wallsVector.erase(i);
				break;
			}
		}
		
		player.update(time, pos);
		//VIEW
		
		
		
		
		

		//to do
		ResStone.draw(window);
		/////////////////////////////////////////////////////////////////////////
		//update & draw towers
		for (auto i = towersVector.begin(); i != towersVector.end(); i++) {
			i->update(window, time, enemiesVector, arrowsVector);
		}
		//////////////////////////////////////////////////////////////////////////
		//update & draw monsters
		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			for (auto j = enemiesVector.begin(); j != enemiesVector.end(); j++) {
				//the same monster
				if (i == j)continue;
				if (i->rect.intersects(j->rect)) {
					//collision with other monsters
					j->collisionWithMobs(i->pos, time);
				}
			}
			//collision with player
			i->collisionWithMobs(player.pos, time);
			//TO DO
			Vector2f tar(Vector2f(ResStone.sprite.getPosition().x + 50, ResStone.sprite.getPosition().y + 50));
			i->update(window, tar, time);
		}
		///////////////////////////////////////////////////////////////////////////////////
		//draw walls
		/*for (auto i = wallsVector.begin(); i != wallsVector.end(); i++) {
			i->draw(window);
		}*/
		///////////////////////////////////////////////////////////////////////////////////////
		//draw arrows
		for (auto i = arrowsVector.begin(); i != arrowsVector.end(); i++) {
			i->draw(window);
		}
		////////////////////////////////////////////////////////////////////////////////////////
		//FPS text
		window.draw(fpsText);
		//Player
		window.draw(player.sprite);
		bar.draw(window, player.health);

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
	long counter = 0;
	Sprite t, empty;
	Vector2f center = window.getView().getCenter();
	int p1 = ((center.x - window.getSize().x / 2) / 50) - 1,
		p2 = ((center.y - window.getSize().y / 2) / 50) - 1,
		p3 = ((center.x + window.getSize().x / 2) / 50) + 1,
		p4 = ((center.y + window.getSize().y / 2) / 50) + 1;
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
			t.setPosition(i * 50, j * 50);
			window.draw(t);
			if (map[i][j][1] == 1) {
				t = wallSpr;
			}
			else {
				t = empty;
			}
			t.setPosition(i * 50, j * 50);
			window.draw(t);
		}
	}
}