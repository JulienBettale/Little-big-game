/*
*  Item.cpp
*
*      Create on : 29/03/2020
*             by : bettal_j
*
*/

#include "stdafx.h"
#include "Item.h"

void Item::initVariables()
{

}

Item::Item(unsigned level, unsigned value)
{
	this->initVariables();

	this->level = level;
	this->value = value;
	this->type = ItemTypes::IT_DEFAULT;
}

Item::~Item()
{

}