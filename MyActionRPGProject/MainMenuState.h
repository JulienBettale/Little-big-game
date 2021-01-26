/*
 *  MainMenuState.h
 *
 *      Create on : 20/02/2020
 *             by : bettal_j
 *
 */

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Music music;

	sf::RectangleShape btnBackground;
	std::map<std::string, gui::Button*> buttons;

	//Fonctions d'initialisation
	void initVariables();
	void initFonts();
	void initMusic();
	void initKeybinds();
	void initGui();
	void resetGui();

public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	//Fonctions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif /* MAINMENUSTATE_H */