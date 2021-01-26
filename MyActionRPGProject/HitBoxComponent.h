/*
*  HitBoxComponent.h
*
*      Create on : 27/02/2020
*             by : bettal_j
*
*/

#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	virtual ~HitboxComponent();

	//Accessoires
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Modificateurs
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	//Fonctions
	bool intersects(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};
#endif /* HITBOXCOMPONENT_H */