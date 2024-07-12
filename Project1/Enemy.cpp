#include "stdafx.h"
#include "Enemy.h"




void Enemy::initVariables()
{
	type = rand() % 100;
	if (type <= 60 ) {
		type = 1;
	}
	else if (type > 60 && type<=90) {
		type = 2;
	}
	else {
		type = 3;
	}
	
	switch (type)
	{
	case 1:
		pointCount = rand() % 2 + 4;
		hpMax = 1;
		hp = hpMax;
		damage = 1;
		point = pointCount;
		speed = 5.f;
		break;
	case 2:
		pointCount = rand() % 2 + 9;
		hpMax = 3;
		hp = hpMax;
		damage = 1;
		point = pointCount;
		speed = 3.f;
		break;
	case 3:
		pointCount = rand() % 2 + 14;
		hpMax = 5;
		hp = hpMax;
		damage = 1;
		point = pointCount;
		speed = 2.f;
		break;
	default:
		break;
	}


}

void Enemy::initShape()
{
	if (type == 1)
	{	
		if (!shape.loadFromFile("texture/s.png"))
		{
			std::cout << "ERROR::PAYER::Could not load the player sheet!!!" << "\n";
		}
		
		sprite.setTexture(shape);
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 15));
		sprite.setScale(2.5f, 2.5f);
		currentFrame = sf::IntRect(0, 0, 16, 15);

	}
	else if (type == 2)
	{
			if (!shape.loadFromFile("texture/m.png"))
			{
				std::cout << "ERROR::PAYER::Could not load the player sheet!!!" << "\n";
			}
			
			sprite.setTexture(shape);
			sprite.setTextureRect(sf::IntRect(0, 0, 32, 15));
			sprite.setScale(2.5f, 2.5f);
			currentFrame = sf::IntRect(0, 0, 32, 15);

	}
	else if (type == 3)
	{
		if (!shape.loadFromFile("texture/l.png"))
		{
			std::cout << "ERROR::PAYER::Could not load the player sheet!!!" << "\n";
		}
		
		sprite.setTexture(shape);
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 31));
		sprite.setScale(3.5f, 3.5f);
		currentFrame = sf::IntRect(0, 0, 32, 31);
	}


}

Enemy::Enemy(float pos_x,float pos_y)
{
		
	initVariables();

	initShape();

	sprite.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const
{
	return sprite.getGlobalBounds();
}

const sf::Vector2f& Enemy::getPos() const
{
	return this->sprite.getPosition();
}

const int& Enemy::getPositionX() const
{
	return sprite.getPosition().x;
}

const int& Enemy::getPositionY() const
{
	return sprite.getPosition().y;
}

const int& Enemy::getPoints() const
{
	return point;
}

const int& Enemy::getType() const
{
	return type;
}

const int& Enemy::getHP() const
{
	return hp;
}

void Enemy::lostHP(int x)
{
	hp = hp - x;
}





void Enemy::update()
{
	if (type == 1)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
				this->currentFrame.left += 16.f;
				if (this->currentFrame.left >= 31.f)
					this->currentFrame.left = 0;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (type == 2)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 63.f)
				this->currentFrame.left = 0;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (type == 3)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 63.f)
				this->currentFrame.left = 0;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

	} 
	 this->sprite.move(0.f, speed); 


	



}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}


