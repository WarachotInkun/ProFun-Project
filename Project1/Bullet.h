#ifndef BULLET_H
#define BULLET_H

#include "stdafx.h"

class Bullet
{

private:
	sf::Sprite shape;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;
	sf::Vector2f direction;
	float movementSpeed;
	unsigned type;
	unsigned frame;

public:
	Bullet();
	Bullet(sf::Texture* texture ,float pos_x, float pos_y,float dir_x,float dir_y,float movement_speed,int type);
	virtual ~Bullet();


	const sf::FloatRect getBounds() const;
	const int& getType() const;
	const int& getFrame() const;
	void update();
	void render(sf::RenderTarget* target);
};


#endif
