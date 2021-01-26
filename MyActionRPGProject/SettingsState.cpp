/*
 *  SettingsState.cpp
 *
 *      Create on : 12/03/2020
 *             by : bettal_j
 *
 */

#include "stdafx.h"
#include "SettingsState.h"

//Fonctions d'initialisation
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Jupiter_Pro_Regular.otf"))
	{
		throw("ERREUR::MAINMENUSTATE::FONT NON CHARGEE!");
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainmemustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void SettingsState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Initialisation background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg.png"))
	{
		throw("ERROR::MAINMENUSTATE::BACKGROUND NON CHARGE !");
	}
	this->background.setTexture(&this->backgroundTexture);

	//Initialisation boutons
	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(30.0f, vm), gui::p2pY(42.5f, vm),
		gui::p2pX(10.3f, vm), gui::p2pY(3.4f, vm),
		&this->font, "Retour", gui::calcCharSize(vm, 100),
		sf::Color(20, 20, 20, 200), sf::Color(90, 90, 90, 200), sf::Color(0, 0, 0, 200),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(30.0f, vm), gui::p2pY(47.5f, vm),
		gui::p2pX(10.3f, vm), gui::p2pY(3.4f, vm),
		&this->font, "Appliquer", gui::calcCharSize(vm, 100),
		sf::Color(20, 20, 20, 200), sf::Color(90, 90, 90, 200), sf::Color(0, 0, 0, 200),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

	//Initialisation mode
	std::vector<std::string> modes_str;
	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	
	//Initialisation Drop Down List
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(
		gui::p2pX(19.0f, vm), gui::p2pY(42.5f, vm),
		gui::p2pX(6.2f, vm), gui::p2pY(2.3f, vm),
		font, modes_str.data(), modes_str.size());

	//Initialisation Texte
	this->optionsText.setFont(font);

	this->optionsText.setPosition(sf::Vector2f(gui::p2pX(2.0f, vm), gui::p2pY(42.5f, vm)));

	this->optionsText.setCharacterSize(gui::calcCharSize(vm, 100));
	this->optionsText.setFillColor(sf::Color(0, 0, 0, 200));

	this->optionsText.setString(
		"Résolution \n\nFullscreen \n\nVysync \n\nAntialiasing \n\n"
	);
}

void SettingsState::resetGui()
{
	/*
	 * Efface les GUI et les réinitialises.
	 * @return void
	 */

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropDownLists.clear();

	this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

//Accessoires

//Fonctions
void SettingsState::updateInput(const float & dt)
{

}

void SettingsState::updateGui(const float & dt)
{
	//Mise à jour de tous les éléments de l'interface graphique
	//Boutons
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//Boutons de fonctionnalité
	//Quitte la fenêtre
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	//Applique les réglages
	if (this->buttons["APPLY"]->isPressed())
	{
		//TEST SUPPRIMER PLUS TARD
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);

		this->resetGui();
	}

	//Dropdown lists
	for (auto &it : this->dropDownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}

	//Fonctionalité Dropdown lists
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto &it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	//SUPPRIMER PLUS TARD!!!
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/
}
