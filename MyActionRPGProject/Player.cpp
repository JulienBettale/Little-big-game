/*
*  Player.cpp
*
*      Create on : 22/02/2020
*             by : bettal_j
*
*/

#include "stdafx.h"
#include "Player.h"

//Fonctions d'initialisation
void Player::initVariables()
{
	this->attacking = false;
	this->sword = new Sword(1, 2, 5, 60, 20, "Resources/Images/Sprites/Player/sword.png");
	this->sword->generate(1, 3);
}

void Player::initComponents()
{

}

void Player::initAnimations()
{
	this->animationComponent->addAnimation("WALK_DOWN", 12.f, 0, 1, 7, 1, 106, 206);
	this->animationComponent->addAnimation("WALK", 11.f, 0, 2, 7, 2, 106, 206);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 7, 4, 106, 206);
	this->animationComponent->addAnimation("ATTACK", 11.f, 0, 5, 6, 5, 209, 206);
	this->animationComponent->addAnimation("IDLE", 0.f, 0, 0, 0, 0, 106, 206);
}

void Player::initInventory()
{
	this->inventory = new Inventory(100);
}

//Constructeurs / Destructeurs
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 10.f, 100.f, 86.f, 86.f); //Position x, position y, largeur, hauteur
	this->createMovementComponent(350.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();

	this->setPosition(x, y);

	this->initAnimations();
}

Player::~Player()
{
	delete this->inventory;
	delete this->sword;
}

//Accessoires
AttributeComponent * Player::getAttributeComponent()
{
	return this->attributeComponent;
}

Weapon * Player::getWeapon() const
{
	return this->sword;
}

//Fonctions
void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player::updateAnimation(const float & dt)
{
	if (this->movementComponent->getState(attacking))
	{
		this->animationComponent->play("ATTACK", dt);
	}
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x < 0.f)
			{
				this->sprite.setOrigin(0.f, 0.f);
				this->sprite.setScale(1.f, 1.f);
			}
		this->animationComponent->play("WALK", dt,
			this->movementComponent->getVelocity().x,
			this->movementComponent->getMaxVelocity()
		);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{

		if (this->sprite.getScale().x > 0.f)
			{
			this->sprite.setOrigin(106.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
			}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float & dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->sword->update(mouse_pos_view, this->getCenter());
}

void Player::render(sf::RenderTarget & target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("light", light_position);
		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("light", light_position);
		this->sword->render(target, shader);
	}
	else
	{
		target.draw(this->sprite);
		this->sword->render(target);
	}

	if (!show_hitbox)
		this->hitboxComponent->render(target);
}