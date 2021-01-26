/*
 *  PauseMenu.cpp
 *
 *      Create on : 10/03/2020
 *             by : bettal_j
 *
 */

#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
	: font(font)
{
	//Initialisation background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Initialisation container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) / 4.f,
			static_cast<float>(vm.height) - gui::p2pY(46.2f, vm)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
		400.f
	);

	//Initialisation texte
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(gui::calcCharSize(vm));
	this->menuText.setString("PAUSE");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width /2.f,
		this->container.getPosition().y + gui::p2pY(1.8f, vm)
	);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Fonctions
const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(
	const std::string key,
	const float y,
	const float width,
	const float height,
	const unsigned char_size,
	const std::string text)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, char_size,
		sf::Color(255, 255, 255, 200), sf::Color(90, 90, 90, 200), sf::Color(50, 50, 50, 200), //Background du bouton idle / hover / active
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent
	);
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void PauseMenu::render(sf::RenderTarget & target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}