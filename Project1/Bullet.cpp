#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	
}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed,int Type)
{
	this->type = Type;
	if(type != 10)
	{
		this->shape.setTexture(*texture);
		//this->shape.setTextureRect(sf::IntRect(0, 0, 15, 31));
		this->shape.setScale(2.f, 2.f);
	}
	else if (type == 10) {
		this->shape.setTexture(*texture);
		this->shape.setScale(4.f, 4.f);
		this->shape.setTextureRect(sf::IntRect(0, 0, 48, 48));
		currentFrame = sf::IntRect(0, 0, 48, 48);
	}
	this->shape.setPosition(pos_x,pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
	frame = 0;
	
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();

}

const int& Bullet::getType() const
{
	return type;
}

const int& Bullet::getFrame() const
{
	return frame;
}

void Bullet::update()
{

	if (type == 10) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.07f)
		{
			this->currentFrame.left += 49.f;
			if (this->currentFrame.left >= 384.f)
				this->currentFrame.left = 0;
			this->animationTimer.restart();
			frame = frame + 1;
			this->shape.setTextureRect(this->currentFrame);
		}
	}
	this->shape.move(this->movementSpeed * -this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
