#include "stdafx.h"
#include "Game.h"


void Game::initWindow()
{
	this->window.create(sf::VideoMode(512,960),"game 4",sf::Style::Close |  sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initTexture()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("texture/bullet.png");
	this->textures["BOLT"] = new sf::Texture();
	this->textures["BOLT"]->loadFromFile("texture/bolt.png");
	this->textures["ROCKET"] = new sf::Texture();
	this->textures["ROCKET"]->loadFromFile("texture/Holy.png");

	
}

void Game::initGUI()
{
	//loadfont
	if (!font.loadFromFile("font/NicoPaint.ttf"))
		std::cout << "ERROR::GAME::fail load font"<<"\n";
	//Pixeboy-z8XGD
	pointText.setFont(font);
	pointText.setCharacterSize(25);
	pointText.setFillColor(sf::Color::White);
	pointText.setOutlineThickness(2.f);
	pointText.setOutlineColor(sf::Color::Black);
	pointText.setLetterSpacing(1.0f);
	pointText.setPosition(0,0);

	//HP
	shapeHP.loadFromFile("texture/04.png");
	spriteHP.setTexture(shapeHP);

	shapeMana.loadFromFile("texture/mana.png");
	spriteMana.setTexture(shapeMana);
}

void Game::initEnemies()
{    

	this->spawnTimer = this->spawnTimerMax;
	this->boltTimer = this->boltTimerMax;
}
/*
void Game::updateBoom()
{
	unsigned counter = 0;
	for (auto* boom : this->booms) {
		boom->update();

		if (boom->getFrame()>5) {
			
			delete this->booms.at(counter);
			this->booms.erase(this->booms.begin() + counter);
			--counter;
		}

	}
	++counter;

}*/
void Game::updateBoom()
{
	auto it = this->booms.begin();
	while (it != this->booms.end()) {
		boom* b = *it;
		b->update();

		if (b->getFrame() > 5) {
			delete b;
			it = this->booms.erase(it);
		}
		else {
			++it;
		}
	}
}

void Game::updateItem()
{
	unsigned counter = 0;
	for (auto*item: items) {
		item->update();
		if (item->getBounds().intersects(player->getBounds())) {
			if (item->getType()==1) {
				playerHP = playerHP+2;
				if (playerHP>=6) {
					playerHP = 6;
				}
			}
			else if (item->getType() == 2) {
				mana = maxMana;
			}
			else if (item->getType() == 3) {
				maxMana = maxMana + 10;
			}
			else if (item->getType() == 4) {
				way += 1;
				if (way>3) {
					way = 3;
				}
			}

			delete this->items.at(counter);
			this->items.erase(this->items.begin() + counter);
			--counter;

			
		}
		else if (item->getBounds().top > window.getSize().y) {
			delete this->items.at(counter);
			this->items.erase(this->items.begin() + counter);
			--counter;
		}
		++counter;
	}
}



void Game::updateEnemies()
{ 
	int spawn=25;

	if (points <4400) {
		spawnTimerMax = rand() % 20 + (spawn - (points / 100));
		spawnTimer += 0.5;
	}
	else if (points >= 4400) {
		spawnTimerMax = 1;
		spawnTimer += 0.5-(points/100000);
	}
	//spawn
	
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		float offscreen = 50;
		float pos_spawn = rand() % window.getSize().x - offscreen;
		if (pos_spawn < offscreen) { pos_spawn = offscreen; }
		this->enemies.push_back(new Enemy(pos_spawn, -100));
		this->spawnTimer = 0.f;
		
		
	}
	
	//update
	unsigned counter = 0;
	boltTimerMax = 20;
	boltTimer += 0.5;
	for (auto* enemy : this->enemies)
	{
		enemy->update();
		

		if (enemies.at(counter)->getType()==2 && this->boltTimer >= this->boltTimerMax && enemies.at(counter)->getPositionY()<=180) {
			int shoot = rand()%10;
			if (shoot  >= 7) {
				float ranbolt = rand() % 5;
				if (ranbolt ==0) {
					ranbolt = 0.01;
				}
				else if (ranbolt == 1) {
					ranbolt = 0.005;
				}
				else if (ranbolt == 2) {
					ranbolt = 0.0;
				}
				else if (ranbolt == 3) {
					ranbolt = -0.005;
				}
				else if (ranbolt == 4) {
					ranbolt = -0.01;
				}
				this->bullets.push_back(new Bullet(this->textures["BOLT"], this->enemies.at(counter)->getPos().x + this->enemies.at(counter)->getBounds().width / 8.f,
					this->enemies.at(counter)->getPos().y + 40,
					ranbolt, -0.1f, 50.f,2));
			}
			this->boltTimer = 0;
		}

		//Bullet culling top screeen
		if (enemy->getBounds().top   > window.getSize().y)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
		else if(enemy->getBounds().intersects(player->getBounds()))
		{
			playerHP = playerHP - enemies.at(counter)->getType();
			this->booms.push_back(new boom(enemies.at(counter)->getPositionX(), enemies.at(counter)->getPositionY(), enemies.at(counter)->getType()));
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);

			--counter;
		}

		++counter;
	}

}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initSystems()
{
	points = 0;
	maxMana = 100;
	mana = maxMana;
	playerHP = 6;
	way = 1;

	easy = 300;
	medium = 500;
	hard = 1000;
	fuckinghard = 1500;
}


void Game::updateBackground(float deltaTime) {
	float backgroundY = backgroundSprite.getPosition().y;
	int backgroundHeight = static_cast<int>(backgroundTexture.getSize().y);

	backgroundY += backgroundScrollSpeed * deltaTime;

	// If the background has scrolled entirely off the bottom, move it back to the top
	if (backgroundY > 0) {
		backgroundY = -static_cast<float>(backgroundHeight) + 960;
		//backgroundY += 960;
	}

	backgroundSprite.setPosition(0.0f, backgroundY);
}


void Game::drawBackground() {
	window.draw(backgroundSprite);
}



void Game::initBackground()
{
	if (!backgroundTexture.loadFromFile("bg/bgloop.png")) {
		std::cout << "ERROR::GAME::fail load Background" << "\n";
	}
	backgroundSprite.setTexture(backgroundTexture);
	float backgroundHeight = static_cast<float>(backgroundTexture.getSize().y);
	backgroundSprite.setPosition(0.0f, static_cast<float>(window.getSize().y) - backgroundHeight);

	
}

Game::Game()
{
	currentState = GameState::MainMenu;
	this->initWindow();
	this->initTexture();
	this->initGUI();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
	this->initBackground();
}
Game:: ~Game()
{
	delete this->player;

	for (auto &i : this->textures) 
	{
		delete i.second;
	}
	for (auto& i : this->bullets)
	{
		delete i; 
	}
	for (auto& i : this->enemies)
	{
		delete i;
	}
	for (auto& i : this->booms)
	{
		delete i;
	}

}

void Game::Delete()
{
	delete this->player;

	for (auto& i : this->textures)
	{
		delete i.second;
	}
	for (auto& i : this->bullets)
	{
		delete i;
	}
	for (auto& i : this->enemies)
	{
		delete i;
	}

}

void Game::run()
{
	sf::Clock clock;
	while (getWindow().isOpen()) {

		sf::RectangleShape playButton(sf::Vector2f(150, 50));
		playButton.setPosition(325, 250);
		playButton.setFillColor(sf::Color::Green);
		sf::Event event;
		while (window.pollEvent(event)|| getWindow().isOpen()) {
			sf::Time deltaTime = clock.restart();
			float dtSeconds = deltaTime.asSeconds();
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (playButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
			{
				playButton.setFillColor(sf::Color::Red);
			}
			else
			{
				playButton.setFillColor(sf::Color::Green);
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					if (playButton.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
						//  playButton
						currentState = GameState::Gameplay;
						while (getWindow().isOpen())
						{

							sf::Time deltaTime = clock.restart();
							float dtSeconds = deltaTime.asSeconds();
							update(dtSeconds);
							render();
						}
					}
				}
			}
			updateBackground(dtSeconds);
			window.clear();
			drawBackground();
			window.draw(playButton);
			window.display();

		}

		//update(dtSeconds);
		//render();
	}
}

void Game::updatePollEvents()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();
	}

}

void Game::updateInput()
{
	this->updatePlayer();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canattack()&&mana>=1)
	{
		if (way==1) {
			this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 3.f,
				this->player->getPos().y - 50,
				0.0f, 0.1f, 80.f, 1));
			mana -= 2;
		}
		else if (way == 2) {
			this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 3.f-10,
				this->player->getPos().y - 50,
				0.0f, 0.1f, 80.f, 1));
			this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 3.f+10,
				this->player->getPos().y - 50,
				0.f, 0.1f, 80.f, 1));


			mana -= 2;
		}
		else if (way >= 3) {
			this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 3.f,
				this->player->getPos().y - 50,
				0.025f, 0.1f, 80.f, 1));
			this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 3.f,
				this->player->getPos().y - 50,
				0.f, 0.1f, 80.f, 1));
			this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 3.f,
				this->player->getPos().y - 50,
				-0.025f, 0.1f, 80.f, 1));
			mana -= 2;
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->player->canattack() && mana > 50) {
		this->bullets.push_back(new Bullet(this->textures["ROCKET"], this->player->getPos().x -62 ,
			this->player->getPos().y - 210,
			0.f, 0.0f, 80.f, 10));
		mana -= 49;
	}
}
void Game::updateHP()
{
	switch (playerHP)
	{
	case 6:
		spriteHP.setTextureRect(sf::IntRect(51, 5, 42, 10));
		spriteHP.setPosition(-18, -6);
		spriteHP.setScale(6, 6);
		break;
	case 5:
		spriteHP.setTextureRect(sf::IntRect(99, 5, 42, 10));
		spriteHP.setPosition(-18, -6);
		spriteHP.setScale(6, 6);
		break;
	case 4:
		spriteHP.setTextureRect(sf::IntRect(147, 5, 42, 10));
		spriteHP.setPosition(-18, -6);
		spriteHP.setScale(6, 6);
		break;
	case 3:
		spriteHP.setTextureRect(sf::IntRect(195, 5, 42, 10));
		spriteHP.setPosition(-18, -6);
		spriteHP.setScale(6, 6);
		break;
	case 2:
		spriteHP.setTextureRect(sf::IntRect(243, 5, 42, 10));
		spriteHP.setPosition(-18, -6);
		spriteHP.setScale(6, 6);
		break;
	case 1:
		spriteHP.setTextureRect(sf::IntRect(291, 5, 42, 10));
		spriteHP.setPosition(-18, -6);
		spriteHP.setScale(6, 6);
		break;
	default:
		spriteHP.setTextureRect(sf::IntRect(51, 21, 42, 10));
		spriteHP.setPosition(-18, -6);
		spriteHP.setScale(6, 6);
		break;
	}


		
}
void Game::updateMana()
{
	std::cout << points << "+++ mama " << mana << "\n";
	manaTimerMax = 35.0f;
	manaTimer += 0.5f;
	if (mana >= preMana && manaTimer >= manaTimerMax) {
		preMana = mana;
		mana += 1;
		manaTimer = manaTimerMax;
		
	}
	else if (mana < preMana) {
		preMana = mana;
		manaTimer = 0;
	}

	if (mana >= maxMana) {
		mana = maxMana;
	}
	if (mana < 0) {
		mana = 0;
		manaTimer = -15.0f;
	}
	if (mana >=75) {
		spriteMana.setTextureRect(sf::IntRect(0, 0, 42, 7));
		spriteMana.setPosition(-18, 20);
		spriteMana.setScale(3, 3);
	}
	else if (mana >= 50 && mana<75) {
		spriteMana.setTextureRect(sf::IntRect(48, 0, 42, 7));
		spriteMana.setPosition(-18, 20);
		spriteMana.setScale(3, 3);
	}
	else if (mana >= 25 && mana < 50) {
		spriteMana.setTextureRect(sf::IntRect(96, 0, 42, 7));
		spriteMana.setPosition(-18, 20);
		spriteMana.setScale(3, 3);
	}
	else if (mana > 0 && mana < 25) {
		spriteMana.setTextureRect(sf::IntRect(144, 0, 42, 7));
		spriteMana.setPosition(-18, 20);
		spriteMana.setScale(3, 3);
	}
	else if (mana <= 0) {
		spriteMana.setTextureRect(sf::IntRect(192, 0, 42, 7));
		spriteMana.setPosition(-18, 20);
		spriteMana.setScale(3, 3);
	}
}
void Game::updateGUI()
{
	updateMana();
	updateHP();
	std::stringstream ss;
	ss << "Point:" << points;
	pointText.setString(ss.str());
	pointText.setPosition(0, 50);
}
const int& Game::getHp() const
{
	return playerHP;
}
const int& Game::getPoint() const
{
	return points;
}
void Game::updateCollision()
{
	//Left Right
	if (player->getBounds().left<0.f)
	{
		player->setPosition(0,player->getBounds().top);
	}
	else if (player->getBounds().left+player->getBounds().width >= window.getSize().x)
	{
		player->setPosition(window.getSize().x- player->getBounds().width , player->getBounds().top);
	}
	//Top Bottom
	if (player->getBounds().top < 0.f)
	{
		player->setPosition( player->getBounds().left, 0);
	}
	else if (player->getBounds().top + player->getBounds().height >= window.getSize().y)
	{
		player->setPosition( player->getBounds().left, window.getSize().y - player->getBounds().height);
	}


}
void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();


		//Bullet culling top screeen
		if (bullet->getBounds().top + bullet->getBounds().height <= 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin()+counter);
			--counter;

			
		}
		if (bullet->getBounds().top + bullet->getBounds().height >= window.getSize().y) {
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;
	}

}
void Game::updateCombat()
{
	
	for (int i = 0; i < enemies.size(); ++i) {
		bool enemy_delete = false;
		for (size_t k = 0; k < bullets.size()&&enemy_delete==false; k++)
		{
			if (enemies[i]->getBounds().intersects(bullets[k]->getBounds()) && bullets[k]->getType() == 1)
			{
				enemies[i]->lostHP(1);

				if(enemies[i]->getHP()<= 0 )
				{
					if (enemies[i]->getType()==3) {
						unsigned ran = rand() % 100;
						if (ran>50) {
							this->items.push_back(new item(enemies[i]->getPositionX(), enemies[i]->getPositionY(), points));
						}
						
					}
					
					this->booms.push_back(new boom(enemies[i]->getPositionX(), enemies[i]->getPositionY(), enemies[i]->getType()));
					points += enemies[i]->getPoints();
					delete enemies[i];
					enemies.erase(enemies.begin() + i);
					delete bullets[k];
					bullets.erase(bullets.begin() + k);
					
					


					enemy_delete = true;
				}
				else {
					delete bullets[k];
					bullets.erase(bullets.begin() + k);

				}


			}
			else if (bullets[k]->getBounds().intersects(player->getBounds())&& bullets[k]->getType() == 2) {
				playerHP = playerHP - 1;

				delete bullets[k];
				bullets.erase(bullets.begin() + k);
			}
			else if (enemies[i]->getBounds().intersects(bullets[k]->getBounds()) && bullets[k]->getType() == 10) {
				enemies[i]->lostHP(5);

				if (enemies[i]->getHP() <= 0)
				{
					if (enemies[i]->getType() == 3) {
						unsigned ran = rand() % 100;
						if (ran > 10) {
							this->items.push_back(new item(enemies[i]->getPositionX(), enemies[i]->getPositionY(), points));
						}

					}
					this->booms.push_back(new boom(enemies[i]->getPositionX(), enemies[i]->getPositionY(), enemies[i]->getType()));
					points += enemies[i]->getPoints();
					delete enemies[i];
					enemies.erase(enemies.begin() + i);

					enemy_delete = true;
				}
			}
			else if (bullets[k]->getType() == 10&& bullets[k]->getFrame() >= 7 ) {
				delete bullets[k];
				bullets.erase(bullets.begin() + k);
			}


		}
	}
}
void Game::updatePlayer()
{
	this->player->update();
}
void Game::update(float dtSeconds)
{
	updateBackground(dtSeconds);
	this->updateBullets();
	this->updatePollEvents();
	this->updateInput();
	updateCollision();
	updateItem();
	this->updatePlayer();
	updateBoom();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();


}
void Game::renderGUI()
{
	window.draw(pointText);
	window.draw(spriteHP);
	window.draw(spriteMana);
}
void Game::renderPlayer()
{
	this->player->render(this->window);
}
void Game::render()
{
	if (currentState == GameState::Gameplay) {
		this->window.clear();
		drawBackground();
		this->renderPlayer();
		for (auto* bullet : this->bullets)
		{
			bullet->render(&window);
		}
		for (auto* enemy : this->enemies) {
			enemy->render(&window);
		}
		for (auto* boom : this->booms) {
			boom->render(&window);
		}
		for (auto* item : this->items) {
			item->render(&window);
		}
		renderGUI();
		this->window.display();
	}
}
const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}