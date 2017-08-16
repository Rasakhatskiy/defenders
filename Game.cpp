#include "globals.h"
#include "Towers.h"
#include "Enemies.h"
#include "Player.h"
#include "RessurectStone.h"
#include "Gui.h"

void game(RenderWindow &window) {
	loadTextures();
	setMap();

	Clock clock;
	RessurectStone ResStone(Vector2f(25*50,25*50));
	Player player(Vector2f(ResStone.sprite.getPosition().x + 100, ResStone.sprite.getPosition().y + 100));
	healthBar bar(1000);
	
	/*vector<Tower> towersVector;
	vector<Wall> wallsVector;
	vector<Arrow> arrowsVector;
	vector<Enemy> enemiesVector;*/

	list<Tower> towersVector;
	list<Wall> wallsVector;
	list<Arrow> arrowsVector;
	list<Enemy> enemiesVector;

	circleMenu cMenu;

	float clickTimer = 0;
	float spawnMonsterTimer = 0;
	float lastTime = 0;
	float fpsTimer = 0;
	float gameTime = 0;
	float timeSpeed = 1.f;

	unsigned long amountOfStone = 0,
		amountOfWood = 0,
		amountOfFood = 0,
		amountOfIron = 0;

	bool isGrid = false;
	bool toNight = true;
	///////////////////////////////////////////////////////////////
	RectangleShape DebugShape;
	DebugShape.setFillColor(Color::Red);
	DebugShape.setOrigin(-28, 45);
	DebugShape.setSize(Vector2f(20, 20));
	//////////////////////////////////////////////////////////////

	while (window.isOpen()) {
		float time = (float)clock.getElapsedTime().asMicroseconds();
		//clock.restart();
		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / (currentTime);

		lastTime = currentTime;
		time = time / 900;
		
		time *= timeSpeed;
		timeSpeed = 1.f;

		Vector2f fpsPos(view.getCenter().x - 300, view.getCenter().y + 200);
		if (fpsTimer > 100) {
			fpsText.setString("FPS: " + std::to_string(fps));
			fpsTimer = 0;
		}
		fpsText.setPosition(fpsPos);

		
		clickTimer += time;
		fpsTimer += time;
		spawnMonsterTimer += time;
		if (toNight) {
			gameTime += time;
		}
		else {
			gameTime -= time;
		}
		if (gameTime > 360000)
			toNight = false;
		if (gameTime <= 1)
			toNight = true;
		

		
		if (fpsTimer > 1000) fpsTimer = 1000;
		if (clickTimer > 1000) clickTimer = 1000;
		if (spawnMonsterTimer > 5000) spawnMonsterTimer = 5000;

		//cursor
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

	
		window.clear();
		setView(window, player.pos);
		drawMap(window, isGrid);

		if (Keyboard::isKeyPressed(Keyboard::K)) {
			timeSpeed = 2.f;
		}

		if (clickTimer > 200) {
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				wallsVector.push_back(Wall(Vector2f(pos.x, pos.y), 1000));
				clickTimer = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::G)) {
				isGrid = !isGrid;
				clickTimer = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				player.rotation(pos);
			}
			if (Keyboard::isKeyPressed(Keyboard::P)) {
				player.health+=5;
			}
			if (Keyboard::isKeyPressed(Keyboard::O)) {
				player.health -= 5;
			}
			if (Keyboard::isKeyPressed(Keyboard::T)) {
				int tx = (int)(pos.x / 50);
				int ty = (int)(pos.y / 50);
				if (map[tx][ty][1] == 0 && map[tx + 1][ty][1] == 0 && map[tx][ty + 1][1] == 0 && map[tx + 1][ty + 1][1] == 0)
					towersVector.push_back(Tower(Vector2f((float)(tx * 50), (float)(ty * 50)), 1000, 10));
				clickTimer = 0;
			}
			if (Mouse::isButtonPressed(Mouse::Right)) {
				enemiesVector.push_back(Enemy(pos, 100, 10));
				clickTimer = 0;
			}
			if (Mouse::isButtonPressed(Mouse::Left)) {
				player.attac();
				clickTimer = 0;
			}
		}

		if (spawnMonsterTimer > 4000) {
			int tx, ty;
			tx = rand() % 1000 - 500;
			ty = rand() % 1000 - 500;
			if (gameTime > 300000) {
				if (map[(int)((tx + player.pos.x) / 50)][(int)((ty + player.pos.y) / 50)][1] == 0) {
					enemiesVector.push_back(Enemy(Vector2f(tx + player.pos.x, ty + player.pos.y), 100, 10));
					spawnMonsterTimer = 0;
				}
			}
		}

		sf::Event Event;
		while (window.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				window.close();
		}

		player.setAmmo();
		////////////////////////////////////////////////////////////////////////////////////////
		
		DebugShape.setRotation(player.sprite.getRotation());
		DebugShape.setPosition(axeSprite.getPosition().x, axeSprite.getPosition().y);
		////////////////////////////////////////////////////////////////////////////////////////

		//intersects with enemies
		for (auto i = enemiesVector.begin(); i != enemiesVector.end(); i++) {
			//deleting
			if (i->health <= 0 || i->health >1000) {
				enemiesVector.erase(i);
				break;
			}
			//Monsters
			/*for (auto j = enemiesVector.begin(); j != enemiesVector.end(); j++) {
				//the same monster
				if (i == j)continue;
				if (i->rect.intersects(j->rect)) {
					//collision with other monsters
					j->collisionWithMobs(i->pos, time);
				}
			}*/
			//Arrows
			for (auto j = arrowsVector.begin(); j != arrowsVector.end(); j++) {
				if (i->rect.intersects(j->rect)) {
					i->health -= 10;
					j->done = true;
				}
			}
			//weapon
			if (i->rect.intersects(DebugShape.getGlobalBounds())) {
				if (i->hurtTimer > 100 && player.attacTimer < 500) {
					i->health -= player.damage;
					i->hurtTimer = 0;
				}
			}
			//player
			if (i->rect.contains(player.pos)) {
				i->collisionWithMobs(player.pos, time);
				if (player.hurtTimer > 100 && i->attacTimer > 100) {
					player.health -= i->damage;
					player.hurtTimer = 0;
					i->attacTimer = 0;
				}
			}
			//towers
			for (auto j = towersVector.begin(); j != towersVector.end(); j++) {
				if (i->rect.intersects(j->rect) && j->hurtTimer > 300 && i->attacTimer > 100) {
					j->health -= i->damage;
					j->hurtTimer = 0;
				}
				if (j->health <= 0) {
					j->clearMap();
					towersVector.erase(j);
					break;
				}
			}
			//walls
			for (auto j = wallsVector.begin(); j != wallsVector.end(); j++) {
				if (i->rect.intersects(j->rect)  && i->attacTimer > 100) {
					j->health -= i->damage;
					j->draw(window);
					i->attacTimer = 0;
				}
				if (j->health <= 0) {
					j->clearMap();
					wallsVector.erase(j);
					break;
				}
			}
			//ressurect stone
			if (i->rect.intersects(ResStone.sprite.getGlobalBounds()) ){
				if (ResStone.hurtTimer > 200) {
					ResStone.health -= i->damage;
					ResStone.hurtTimer = 0;
				}
				
				if (ResStone.health <= 0) {
					//todo
				}
			}
			//updating
			Vector2f tar(Vector2f(ResStone.sprite.getPosition().x + 50, ResStone.sprite.getPosition().y + 50));
			i->update(window, tar, time);
		}

		//to do
		ResStone.update(time);
		ResStone.draw(window);
		//update & draw towers
		for (auto i = towersVector.begin(); i != towersVector.end(); i++) {
			i->update(window, time, enemiesVector, arrowsVector);
		}
		//update & draw arrows
		for (auto i = arrowsVector.begin(); i != arrowsVector.end(); i++) {
			i->move(time);
			if (i->done) {
				arrowsVector.erase(i);
				break;
			}
			i->draw(window);
		}
		//FPS text
		window.draw(fpsText);
		//Player
		player.update(time, pos);
		window.draw(player.sprite);
		//27x15
		if (cMenu.chosen == 2) {
			window.draw(axeSprite);
			player.damageBonus = 1;
		}
		else
			if (cMenu.chosen == 3) {
				window.draw(pickaxeSprite);
				player.damageBonus = 0.5;
			}
				
		if (cMenu.chosen == 4)
			window.draw(weaponSprite);

		
		//window.draw(DebugShape);
		//Bar
		bar.draw(window, player.health);
		if (Keyboard::isKeyPressed(Keyboard::Tab)) {
			cMenu.choose(window, pos);
		}
		day_nightCircle(window, gameTime);
		window.display();
	}
}

