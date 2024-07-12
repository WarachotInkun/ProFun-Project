#pragma once
#ifndef ITEM_H
#define ITEM_H


#include "stdafx.h"
class item
{
private:
	sf::Sprite sprite;
	sf::Texture shape;
	unsigned type;
	unsigned points;
	void initVariables();
	void initShape();
public:
	item(float pos_x, float pos_y, int point);
	
	virtual ~item();
	const sf::FloatRect getBounds() const;
	const int& getType() const;
	const int& getPositionY() const;
	void update();
	void render(sf::RenderTarget* target);
};

#endif