/*
 *  Game.h
 *
 *      Create on : 18/02/2020
 *             by : bettal_j
 *
 */

#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	//Initialisation
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();

public:
	//Construceurs / Destructeurs
	Game();
	virtual ~Game();

	//Fonctions

	void endApplication();

	void updateDt();
	void updateSFMLEvents();
	void update();

	void render();

	void run();
};

#endif /* GAME_H  */
