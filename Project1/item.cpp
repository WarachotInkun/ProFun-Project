#include "stdafx.h"
#include "item.h"



void item::initVariables()
{
	type = 0;
	int ran = rand() % 100;
	if (ran >20) {
		type = rand() % 3 + 1;
	}
	else {
		type = rand() % 4 + 1; 
	}
	
	
	/*
	1 heal
	2 mana
	3 +maxmana
	4 x2
	5 fire rate
	6 1.5 dmg
	7 โล่ 
	*/
}

void item::initShape()
{

	if (type == 1) {
		if (!shape.loadFromFile("item/heal.png"))
		{
			std::cout << "ERROR::PAYER::Could not load the player sheet!!!" << "\n";
		}
		sprite.setTexture(shape);
		sprite.setScale(2.0f, 2.0f);
	}
	else if (type ==2) {
		if (!shape.loadFromFile("item/mana.png"))
		{
			std::cout << "ERROR::PAYER::Could not load the player sheet!!!" << "\n";
		}
		sprite.setTexture(shape);
		sprite.setScale(2.0f, 2.0f);
	}
	else if (type == 3) {
		if (!shape.loadFromFile("item/maxmana.png"))
		{
			std::cout << "ERROR::PAYER::Could not load the player sheet!!!" << "\n";
		}
		sprite.setTexture(shape);
		sprite.setScale(2.0f, 2.0f);
	}
	else if (type == 4) {
		if (!shape.loadFromFile("item/x2.png"))
		{
			std::cout << "ERROR::PAYER::Could not load the player sheet!!!" << "\n";
		}
		sprite.setTexture(shape);
		sprite.setScale(2.0f, 2.0f);
	}

}

item::item(float pos_x, float pos_y,int point)
{
	points = point;
	initVariables();
	initShape();
	
	sprite.setPosition(pos_x,pos_y);
}

item::~item()
{
}

const sf::FloatRect item::getBounds() const
{
	return sprite.getGlobalBounds(); 
}

const int& item::getType() const
{
	return type;
}

const int& item::getPositionY() const
{
	return sprite.getPosition().y;
}



void item::update()
{
	this->sprite.move(0.f, 5);
}

void item::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
