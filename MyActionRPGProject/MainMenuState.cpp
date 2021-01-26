/*
 *  MainMenuState.cpp
 *
 *      Create on : 20/02/2020
 *             by : bettal_j
 *
 */

#include "stdafx.h"
#include "MainMenuState.h"

 //Fonctions d'initialisation
void MainMenuState::initVariables()
{

}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Jupiter_Pro_Regular.otf"))
		throw("ERROR::MAINMENUSTATE::FONT NON CHARGEE!");
}

void MainMenuState::initMusic()
{
	if (!music.openFromFile("Resources/Musiques/main_menu_theme.ogg"))
		throw("ERREUR");

	//Volume / Play et Répétition
	this->music.setVolume(1);
	this->music.setLoop(true);
	this->music.play();
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg.png"))
	{
		throw("ERROR::MAINMENUSTATE:: BACKGROUND NON CHARGEE!");
	}

	this->background.setTexture(&this->backgroundTexture);

	//Boutons init
	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(10.4f, vm), gui::p2pY(55.0f, vm), //Position du bouton : x / y
		gui::p2pX(14.3f, vm), gui::p2pY(3.4f, vm), //taille du bouton : / width / height
		&this->font, "Nouvelle Partie", gui::calcCharSize(vm, 110),
		sf::Color(20, 20, 20, 200), sf::Color(90, 90, 90, 200), sf::Color(0, 0, 0, 200), //Background du bouton idle / hover / active
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent
	); 

	this->buttons["CONTINUE_GAME_STATE"] = new gui::Button(
		gui::p2pX(10.4f, vm), gui::p2pY(60.0f, vm),
		gui::p2pX(14.3f, vm), gui::p2pY(3.4f, vm),
		&this->font, "Continuer", gui::calcCharSize(vm, 110),
		sf::Color(20, 20, 20, 200), sf::Color(90, 90, 90, 200), sf::Color(0, 0, 0, 200),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		gui::p2pX(10.4f, vm), gui::p2pY(65.0f, vm),
		gui::p2pX(14.3f, vm), gui::p2pY(3.4f, vm),
		&this->font, "Réglages", gui::calcCharSize(vm, 110),
		sf::Color(20, 20, 20, 200), sf::Color(90, 90, 90, 200), sf::Color(0, 0, 0, 200),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

	this->buttons["EDITOR_STATE"] = new gui::Button(
		gui::p2pX(10.4f, vm), gui::p2pY(70.0f, vm),
		gui::p2pX(14.3f, vm), gui::p2pY(3.4f, vm),
		&this->font, "Éditeur", gui::calcCharSize(vm, 110),
		sf::Color(20, 20, 20, 200), sf::Color(90, 90, 90, 200), sf::Color(0, 0, 0, 200),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(10.4f, vm), gui::p2pY(75.0f, vm),
		gui::p2pX(14.3f, vm), gui::p2pY(3.4f, vm),
		&this->font, "Quitter", gui::calcCharSize(vm, 110),
		sf::Color(20, 20, 20, 200), sf::Color(90, 90, 90, 200), sf::Color(0, 0, 0, 200),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
}

void MainMenuState::resetGui()
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

	this->initGui();
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initMusic();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::updateInput(const float & dt)
{

}

void MainMenuState::updateButtons()
{
	//Mise à jour de tous les boutons

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//Nouvelles partie
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
		this->music.stop();
	}

	//Réglages
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	//Editeur
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
		this->music.stop();
	}

	//Quitter
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();

	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	target->draw(this->btnBackground);

	this->renderButtons(*target);
}