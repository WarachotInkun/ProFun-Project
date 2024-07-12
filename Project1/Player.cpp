#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->moving = false;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("texture/ship.png"))
	{
		std::cout << "ERROR::PAYER::Could not load the player sheet!!!" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->sprite.setScale(2.5f,2.5f);
	this->currentFrame = sf::IntRect(0, 0, 16, 23);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setPosition(256.f,800.f);
}

void Player::initAnimation()
{
	this->animationTimer.restart();

}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	sprite.setPosition(x,y);
}

void Player::updateMovement()
{
	this->moving = false;
	this->movingFast = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		this->sprite.move(-2.3f, 0.f);
		this->moving = true;
		this->movingFast = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		this->sprite.move(2.3f, 0.f);
		this->moving = true;
		this->movingFast = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->sprite.move(-1.3f, 0.f);
		this->moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->sprite.move(1.3f, 0.f);
		this->moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		this->sprite.move(0.f, -2.3f);
		this->moving = true;
		this->movingFast = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		this->sprite.move(0.f, 2.3f);
		this->movingFast = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		this->sprite.move(0.f, -1.3f);
		this->moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		this->sprite.move(0.f, 1.3f);

	}

}

void Player::updateAnimation()
{
	if(this->animationTimer.getElapsedTime().asSeconds()>=0.1f)
	{ 
		//ship animetion
		if (this->moving==true) 
		{
			this->currentFrame.left += 16.f;
			if (this->currentFrame.left >= 64.f)
				this->currentFrame.left = 0;
		}
		else {
			this->currentFrame.left = 32;
		}
		this->currentFrame.top += 24.f;
		if (this->currentFrame.top >= 48.f)
			this->currentFrame.top = 0;
		


		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}
}

void Player::updateAttack()
{
	if(this->attackCooldown<this->attackCooldownMax)
		this->attackCooldown += 0.4f;
}

const bool Player::canattack()
{
	if (this->attackCooldown >= this->attackCooldownMax && !movingFast)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}



void Player::update()
{
	this->updateAttack();
	this->updateMovement();
	this->updateAnimation();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
