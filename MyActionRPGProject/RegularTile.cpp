/*
*  RegularTile.cpp
*
*      Create on : 31/03/2020
*             by : bettal_j
*
*/

#include "stdafx.h"
#include "RegularTile.h"

RegularTile::RegularTile(short type, int grid_x, int grid_y, float gridSizeF,
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	bool collision)
	: Tile(type, grid_x, grid_y, gridSizeF, texture, texture_rect, collision)
{

}

RegularTile::~RegularTile()
{

}

//Fonctions
const std::string RegularTile::getAsString() const
{
	std::stringstream ss;

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision;

	//std::cout << ss.str() << "\n";

	return ss.str();
}

void RegularTile::update()
{

}

void RegularTile::render(sf::RenderTarget & target, sf::Shader * shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("light", player_position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}
