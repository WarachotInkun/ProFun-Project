#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "boom.h"
#include "item.h"
enum class GameState {
	MainMenu,
	Gameplay,
	GameOver,
	LeaderBoard
};
class Game
{
private:
	
	sf::Event ev;
	GameState currentState;
	std::map<std::string, sf::Texture*>textures;
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<boom*> booms;
	std::vector<item*>items;

	float spawnTimer;
	float spawnTimerMax;

	float manaTimer;
	float manaTimerMax;
	unsigned preMana;


	float boltTimer;
	float boltTimerMax;

	sf::Font font;
	sf::Text pointText;

	sf::Sprite spriteHP;
	sf::Texture shapeHP;

	sf::Sprite spriteMana;
	sf::Texture shapeMana;

	int easy;
	int medium;
	int hard;
	int fuckinghard;



	unsigned points;
	int mana;
	int maxMana;
	int playerHP;
	int way;
	Player* player;
	
	void initTexture();
	void initGUI();
	void initEnemies();
	void initPlayer();
	void initSystems();


	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	float backgroundScrollSpeed = 50.0f; // Adjust scrolling speed as needed
	float backgroundY = 0.0f;

	void updateBackground(float deltaTime);
	void drawBackground();
	void initBackground();

public:
	// Function
	Game();
	virtual ~Game();
	void Delete();
	// Function
	sf::RenderWindow window;
	void initWindow();
	void run();
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	const int& getHp() const;
	const int& getPoint() const;
	void updateHP();
	void updateMana();
	void updateCollision();
	void updateBullets();

	void updateBoom();
	void updateItem();
	void updateEnemies();
	void updateCombat();
	void updatePlayer();
	void update(float dtSeconds);
	void renderGUI();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;
};

