/*
*  Enemy.cpp
*
*      Create on : 29/03/2020
*             by : bettal_j
*
*/

#include "stdafx.h"
#include "Enemy.h"

//Fonctions d'initialisation
void Enemy::initVariables()
{
	this->gainExp = 100;
}

void Enemy::initAnimations()
{

}

//Constructeur / Destructeur
Enemy::Enemy()
{
	this->initVariables();
	this->initAnimations();
}

Enemy::~Enemy()
{

}

const unsigned & Enemy::getGainExp() const
{
	return this->gainExp;
}

void Enemy::generateAttributes(const unsigned level)
{
	this->gainExp = level * (rand() % 10 + 20);
}

void Enemy::loseHP(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
}

const bool Enemy::isDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
	}

	return false;
}

const AttributeComponent * Enemy::getAttributeComp() const
{
	if (this->attributeComponent)
		return this->attributeComponent;
	else
	{
		std::cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT N'EST PAS INITIALISER" << "\n";
		return nullptr;
	}
}