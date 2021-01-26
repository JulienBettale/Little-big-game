/*
*  Rat.h
*
*      Create on : 31/03/2020
*             by : bettal_j
*
*/

#ifndef RAT_H
#define RAT_H

#include "Enemy.h"

class Rat :
	public Enemy
{
private:
	void initVariables();
	void initAnimations();
	void initGUI();

	sf::RectangleShape hpBar;

public:
	Rat(float x, float y, sf::Texture& texture_sheet);
	virtual ~Rat();

	//Fonctions
	void updateAnimation(const float & dt);
	void update(const float & dt, sf::Vector2f& mouse_pos_view);

	void render(sf::RenderTarget & target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox);
};

#endif /* RAT_H */