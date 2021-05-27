#include "../Header/Menu.h"


Menu::Menu()
{
	// Set initial values
	selectedOption = 0;
	mainMenuDisplay = true, playerNameDisplay = false, levelsListDisplay = false;

	// Load fonts from file
	if (!menuFont.loadFromFile(MAIN_MENU_FONT)) { std::cout << "Can't load MAIN_MENU_FONT\n"; }
	if (!playerNameFont.loadFromFile(PLAYER_NAME_FONT)) { std::cout << "Can't load PLAYER_NAME_FONT\n"; }

	// Load backgrounds
	if(!backGroundTexture.loadFromFile(MAIN_MENU_BACKGROUND)) { std::cout << "Can't load MAIN_MENU_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);

	if (!playerNameTexture.loadFromFile(PLAYER_NAME_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	playerNameSprite.setTexture(playerNameTexture);

	// Set OptionShadow properties
	if(!optionShadowTexture.loadFromFile(MENU_SHADOW)) { std::cout << "Can't load MENU_SHADOW\n"; }
	optionShadowSprite.setTexture(optionShadowTexture);
	optionShadowSprite.setPosition(620, 295); // Start position 

	// Set Player Name Text Properties
	playerNameText.setFont(playerNameFont);
	playerNameText.setStyle(Text::Style::Bold);
	playerNameText.setCharacterSize(70);
	playerNameText.setPosition(445, 411);

	// Helper varibles
	float width = 628;
	float hight = 225;
	std::string OptionsTemp[NUM_OF_OPTIONS] = {
		"	  START",
		"HOW TO PLAY",
		"HIGH  SCORES",
		"    OPTIONS",
		"    CREDITS",
		"       EXIT"};

	for (int i = 0; i < NUM_OF_OPTIONS; i++) {
		menuOptions[i].setFont(menuFont);
		menuOptions[i].setFillColor(sf::Color::White);
		menuOptions[i].setCharacterSize(43);
		menuOptions[i].setStyle(sf::Text::Bold);
		menuOptions[i].setString(OptionsTemp[i]);
		
		hight += 70;
		menuOptions[i].setPosition(width, hight);
	}
}


void Menu::draw(RenderWindow& window)
{
	if (mainMenuDisplay) {
		window.draw(backGroundSprite);
		window.draw(optionShadowSprite);

		for (int i = 0; i < NUM_OF_OPTIONS; i++) {
			window.draw(menuOptions[i]);
		}
	}
	else if (playerNameDisplay) {
		window.draw(playerNameSprite);
		window.draw(playerNameText);
	}
	
}


void Menu::moveDown()
{
	// if box in Exit postion set to Start 
	if (optionShadowSprite.getPosition().y == 645)
	{
		optionShadowSprite.setPosition(620, 295);
		selectedOption = 0;
	}
	else {
		optionShadowSprite.move(0, 70);
		selectedOption++;
	}
}


void Menu::moveUp()
{
	// if box in Start postion set to Exit 
	if (optionShadowSprite.getPosition().y == 295)
	{
		optionShadowSprite.setPosition(620, 645);
		selectedOption = 5;
	}
	else {
		optionShadowSprite.move(0, -70);
		selectedOption--;
	}
}


void Menu::catchEvents(Event& event, RenderWindow& window) {
	if (mainMenuDisplay) {
		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Up:
				this->moveUp();
				break;
			case Keyboard::Down:
				this->moveDown();
				break;
			case Keyboard::Enter:
				// Check current selected option
				switch (selectedOption)
				{
				case 0:
					openPlayerName();
					break;
				}
				break;
			}
			break;
		}
	}
	else if (playerNameDisplay) {
		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::BackSpace:
				// Erase last character form string
				playerNameStr = playerNameStr.substring(0, playerNameStr.getSize() - 1);
				break;
			case sf::Keyboard::Enter:
				if (playerNameStr.getSize() > 0) {
					playerNameDisplay = false;

					// Convert sfml String to std String
					std::wstring pnameTemp = playerNameStr.toWideString();
					playerName = std::string(pnameTemp.begin(), pnameTemp.end());
				}
				break;
			}
			break;

		case Event::TextEntered:
			if (playerNameStr.getSize() <= 20) {
				playerNameStr += event.text.unicode;
				playerNameText.setString(playerNameStr);
			}
			break;
		}
	}
}


void Menu::openPlayerName() {
	playerNameDisplay = true;
	mainMenuDisplay = false;
}