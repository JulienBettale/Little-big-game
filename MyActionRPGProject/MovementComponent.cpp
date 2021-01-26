/*
 *  MouvementComponent.cpp
 *
 *      Create on : 23/02/2020
 *             by : bettal_j
 *
 */

#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite),
	maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

//Accessoires
const float & MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}

//Fonctions
const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;

		break;

	case MOVING:

		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;

		break;

	case MOVING_LEFT:

		if (this->velocity.x < 0.f)
			return true;

		break;

	case MOVING_RIGHT:

		if (this->velocity.x > 0.f)
			return true;

		break;

	case MOVING_UP:

		if (this->velocity.y < 0.f)
			return true;

		break;

	case MOVING_DOWN:

		if (this->velocity.y > 0.f)
			return true;

		break;
	}

	return false;
}

void MovementComponent::stopVelocity()
{
	/* Reset la vitesse à 0.*/

	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	/* Reset la vitesse x à 0.*/

	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	/* Reset la vitesse y à 0.*/

	this->velocity.y = 0.f;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/* Acceleration du sprite jusqu'à atteindre sa vitesse max. */

	this->velocity.x += this->acceleration * dir_x * dt;
	this->velocity.y += this->acceleration * dir_y * dt;
}

void MovementComponent::update(const float & dt)
{
	/*
	 * Décélération du sprite et contrôle de la vitesse max.
	 * Déplacement du sprite.
	 */

	if (this->velocity.x > 0.f) //Check positif x
	{
		//Check vitesse max
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Décélération
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) //Check négatif x
	{
		//Check vitesse max
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Décélération
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) //Check positif y
	{
		//Check vitesse max
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Décélération
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) //Check négatif y
	{
		//Check vitesse max
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Décélération
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity * dt); //Utilisation de la vitesse
}
