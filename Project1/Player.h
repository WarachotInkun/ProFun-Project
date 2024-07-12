#pragma once


class Player
{

private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	//Animation
	sf::IntRect currentFrame;
	bool moving;
	bool movingFast;
	sf::Clock animationTimer;
	//Movement

	float attackCooldown;
	float attackCooldownMax;

	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();

public:

	Player();
	virtual ~Player();


	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;


	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x,const float y);

	//Funtion
	
	void updateMovement();
	void updateAnimation();
	void updateAttack();
	const bool canattack();
	void update();
	void render(sf::RenderTarget&target);
};

