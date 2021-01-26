/*
 *  GameState.cpp
 *
 *      Create on : 19/02/2020
 *             by : bettal_j
 *
 */

#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
}

//Fonctions d'initialisation
void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

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

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Jupiter_Pro_Regular.otf"))
	{
		throw("ERREUR::MAINMENUSTATE::FONT NON CHARGEE!");
	}
}

void GameState::initMusic()
{
	if (!music.openFromFile("Resources/Musiques/game_state_theme.ogg"))
		throw("ERREUR");

	// Volume / Play et Répétition
	this->music.setVolume(1);
	this->music.play();
	this->music.setLoop(true);
}

//Initiation des fonctions
void GameState::initTextures()
{
	//sf::IntRect(0, 0, 85, 150) //Gestion du sprite
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/M_Rune_Knight_sheet.png"))
	{
		throw("ERREUR::GAMESTATE::TEXTURE PLAYER NON CHARGEE !");
	}

	if (!this->textures["RAT1_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/rat1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::TEXTURE RAT1 NON CHARGEE";
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(67.1f, vm), gui::p2pX(13.1f, vm), gui::p2pY(6.1f, vm), gui::calcCharSize(vm, 110), "Quitter");
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_sharder.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::SHADER NON CHARGEE" << "\n";
	}
}

void GameState::initPlayers()
{
	this->player = new Player(1650, 500, this->textures["PLAYER_SHEET"]); //Position d'apparition sur la map x et y + sprite
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap("text.slmp");
}

void GameState::initSystems()
{
	this->tts = new TextTagSystem("Fonts/Miedinger-Regular.otf");
}

//Constructeurs / Destructeurs
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initMusic();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();

	this->initPlayers();
	this->initPlayerGUI();
	this->initEnemySystem();
	this->initTileMap();
	this->initSystems();

	//this->activeEnemies.push_back(new Rat(1500.f, 600.f, this->textures["RAT1_SHEET"]));
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGUI;
	delete this->enemySystem;
	delete this->tileMap;
	delete this->tts;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}

//Fonctions
void GameState::updateView(const float & dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (
			static_cast<float>(this->mousePosWindow.x) -
			static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f),
		std::floor(this->player->getPosition().y + (
			static_cast<float>(this->mousePosWindow.y) -
			static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
	);

	if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float & dt)
{
	//Mise à jour déplacement du joueur
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
	}
}

void GameState::updatePlayerGUI(const float & dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
		this->music.stop();
	}
}

void GameState::updateTileMap(const float & dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);
}

void GameState::updatePlayer(const float & dt)
{

}

void GameState::updateCombatAndEnemies(const float & dt)
{
	unsigned index = 0;
	for (auto *enemy : this->activeEnemies)
	{
		enemy->update(dt, this->mousePosView);

		this->tileMap->updateWorldBoundsCollision(enemy, dt);
		this->tileMap->updateTileCollision(enemy, dt);

		this->updateCombat(enemy, index, dt);

		if (enemy->isDead())
		{
			this->player->gainEXP(enemy->getGainExp());
			this->tts->addTextTag(EXPERIENCE_TAG, this->player->getPosition().x, this->player->getPosition().y, static_cast<int>(enemy->getGainExp()), "", "+EXP");

			this->activeEnemies.erase(this->activeEnemies.begin() + index);
			--index;
		}
		++index;
	}
}

void GameState::updateCombat(Enemy* enemy, const int index, const float & dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->player->getWeapon()->getAttackTimer()
			&& enemy->getGlobalBounds().contains(this->mousePosView)
			&& enemy->getDistance(*this->player) < this->player->getWeapon()->getRange())
		{
			int dmg = static_cast<int>(this->player->getWeapon()->getDamage());
			enemy->loseHP(dmg);
			this->tts->addTextTag(NEGATIVE_TAG, enemy->getPosition().x, enemy->getPosition().y, dmg, "", "-HP");
			std::cout << "Attaque!" << "\n";
		}
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Mise à jour fin de pause
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->player->update(dt, this->mousePosView);

		this->playerGUI->update(dt);

		//Mise à jour de tous les ennemies
		this->updateCombatAndEnemies(dt);

		//Mise à jour system
		this->tts->update(dt);
	}
	else //Mise à jour pause
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(
		this->renderTexture,
		this->viewGridPosition,
		&this->core_shader,
		this->player->getCenter(),
		false
	);

	for (auto *enemy : this->activeEnemies)
	{
		enemy->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	}

	this->player->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);

	this->tileMap->renderDeferred(this->renderTexture, &this->core_shader, this->player->getCenter());

	this->tts->render(this->renderTexture);

	//Rendu GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused) //Rendu menu pause
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//Rendu final
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}