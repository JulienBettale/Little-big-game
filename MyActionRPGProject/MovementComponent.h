/*
 *  MouvementComponent.h
 *
 *      Create on : 23/02/2020
 *             by : bettal_j
 *
 */

#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

public:
	MovementComponent(sf::Sprite& sprite,
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessoires
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	//Fonctions
	const bool getState(const short unsigned state) const;
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
};

#endif /* MOUVEMENTCOMPONENT_H */