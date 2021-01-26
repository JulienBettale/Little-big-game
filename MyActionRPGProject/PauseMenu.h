/*
 *  PauseMenu.h
 *
 *      Create on : 10/03/2020
 *             by : bettal_j
 *
 */

#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include"Gui.h"

class Gui;

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

public:
	PauseMenu(sf::VideoMode& vm, sf::Font& font);
	virtual ~PauseMenu();

	//Accessoires
	std::map<std::string, gui::Button*>& getButtons();

	//Fonctions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key,
		const float y,
		const float width,
		const float height,
		const unsigned char_size,
		const std::string text);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

#endif /* PAUSEMENU_H */