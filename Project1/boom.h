#ifndef BOOM_H
#define BOOM_H


#include "stdafx.h"
class boom
{
private:
	sf::Sprite sprite;
	sf::Texture shape;

	
	sf::Clock animationTimer;
	sf::IntRect currentFrame;

	unsigned frame;
	unsigned count, maxcount, Type;

public:
	boom(float pos_x, float pos_y, float type);
	
	virtual ~boom();
	void initVariables();
	void initShape();
	const int& getFrame() const;


	void update();
	void render(sf::RenderTarget* target);
};
#endif // BOOM_H
