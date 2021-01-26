/*
 *  SettingsState.h
 *
 *      Create on : 12/03/2020
 *             by : bettal_j
 *
 */

#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Gui.h"

class SettingsState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	//Fonctions d'initialisation
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();

public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	//Accessoires

	//Fonctions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif /* SETTINGSSTATE_H */