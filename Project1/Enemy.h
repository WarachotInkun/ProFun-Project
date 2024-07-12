#ifndef ENEMY_H
#define ENEMY_H
#include "stdafx.h"
#include "Player.h"

class Enemy
{
private:
	unsigned pointCount;
	sf::Sprite sprite;
	sf::Texture shape;
	
	
	unsigned type;
	int hp;
	int hpMax;
	int damage;
	int point;
	float speed;
	
	sf::Clock animationTimer;
	sf::IntRect currentFrame;
	
	Player* players;
	void initVariables();
	void initShape();
public:
	Enemy(float pos_x, float pos_y);

	virtual ~Enemy();


	const sf::FloatRect getBounds() const;
	const sf::Vector2f& getPos() const;
	const int& getPositionX() const;
	const int& getPositionY() const;

	const int& getPoints() const;
	const int& getType() const;
	const int& getHP() const;

	void lostHP(int x);

	//Function
	void update();
	void render(sf::RenderTarget* target);


};

#endif