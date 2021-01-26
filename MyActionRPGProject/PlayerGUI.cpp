/*
*  PlayerGUI.cpp
*
*      Create on : 27/03/2020
*             by : bettal_j
*
*/

#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	if (!this->font.loadFromFile("Fonts/Miedinger-Regular.otf"))
	{
		throw("ERREUR::PLAYERGUIDAMAGE::FONT NON CHARGEE!");
	}
}

void PlayerGUI::initLevelBar()
{
	float width = gui::p2pX(2.8f, this->vm);
	float height = gui::p2pY(4.1f, this->vm);
	float x = gui::p2pX(0.5f, this->vm);
	float y = gui::p2pY(0.9f, this->vm);

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 0));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 120));
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + gui::p2pX(0.2f, this->vm),
		this->levelBarBack.getPosition().y + gui::p2pY(0.2f, this->vm)
	);
}

void PlayerGUI::initEXPBar()
{

	this->expBar = new gui::ProgressBar(
		4.1f, 3.7f, 20.8f, 1.3f,
		this->player->getAttributeComponent()->expNext,
		sf::Color::Yellow, 280,
		this->vm, &this->font
	);
}

void PlayerGUI::initHPBar()
{
	this->hpBar = new gui::ProgressBar(
		4.1f, 0.9f, 20.8f, 2.8f,
		this->player->getAttributeComponent()->hpMax,
		sf::Color::Red, 150,
		this->vm, &this->font
	);
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
	: vm(vm)
{
	this->player = player;

	this->initFont();
	this->initLevelBar();
	this->initEXPBar();
	this->initHPBar();
}

PlayerGUI::~PlayerGUI()
{
	delete this->hpBar;
	delete this->expBar;
}

//Fonctions
void PlayerGUI::updateLevelBar()
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::updateEXPBar()
{
	this->expBar->update(this->player->getAttributeComponent()->exp);
}

void PlayerGUI::updateHPBar()
{
	this->hpBar->update(this->player->getAttributeComponent()->hp);
}

void PlayerGUI::update(const float & dt)
{
	this->updateLevelBar();
	this->updateEXPBar();
	this->updateHPBar();
}


void PlayerGUI::renderLevelBar(sf::RenderTarget & target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::renderEXPBar(sf::RenderTarget & target)
{
	this->expBar->render(target);
}

void PlayerGUI::renderHPBar(sf::RenderTarget & target)
{
	this->hpBar->render(target);
}

void PlayerGUI::render(sf::RenderTarget & target)
{
	this->renderLevelBar(target);
	this->renderEXPBar(target);
	this->renderHPBar(target);
}