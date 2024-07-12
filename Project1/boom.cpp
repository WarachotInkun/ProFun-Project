
#include "stdafx.h"
#include "boom.h"

boom::boom(float pos_x, float pos_y, float type)
{
	initVariables();
	count = type - 1;
	initShape();
	count = type -2;
	sprite.setPosition(pos_x, pos_y);

	
}

boom::~boom()
{
}

void boom::initVariables()
{
	frame = 0;
	maxcount = 5;
	this->animationTimer.restart();
}


void boom::initShape()
{

		if (!shape.loadFromFile("texture/explosion.png"))
		{
			std::cout << "ERROR::PAYER::Could not load the player sheet!!!" << "\n";
		}
		sprite.setTexture(shape);
		sprite.setScale(2.5 + count, 2.5 + count);
		sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
		currentFrame = sf::IntRect(0, 0, 15, 15);

}

const int& boom::getFrame() const
{
	return frame;
}

void boom::update()
{


		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f) {
			this->currentFrame.left += 16.f;
			if (this->currentFrame.left >= 79.f)
				this->currentFrame.left = 0;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			frame = frame + 1;
			this->animationTimer.restart();
		}

}

void boom::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
