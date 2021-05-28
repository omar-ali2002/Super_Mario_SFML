#include "../Header/Menu.h"


Menu::Menu()
{
	// Set initial values
	openMainMenu();
	selectedOption = activeOptionsMenu = 0;
	selectedDifficulty = 2;
	muteMusic = handControlled = false;
	newPlayer.lifes = 3;

	// Set Menu Sound Properties
	if (!menuBuffer.loadFromFile(MENU_SOUND)) { std::cout << "Can't load MENU_SOUND\n"; }
	menuSound.setBuffer(menuBuffer);
	menuSound.play();

	// Load fonts from file
	if (!menuFont.loadFromFile(MAIN_MENU_FONT)) { std::cout << "Can't load MAIN_MENU_FONT\n"; }
	if (!playerNameFont.loadFromFile(PLAYER_NAME_FONT)) { std::cout << "Can't load PLAYER_NAME_FONT\n"; }

	// Load backgrounds
	if(!backGroundTexture.loadFromFile(MAIN_MENU_BACKGROUND)) { std::cout << "Can't load MAIN_MENU_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);

	if (!playerNameTexture.loadFromFile(PLAYER_NAME_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	playerNameSprite.setTexture(playerNameTexture);

	if (!howToPlayTexture.loadFromFile(HOW_TO_PLAY_BACKGROUND)) { std::cout << "Can't load HOW_TO_PLAY_BACKGROUND\n"; }
	howToPlaySprite.setTexture(howToPlayTexture);

	if (!highScoreTexture.loadFromFile(HIGH_SCORE_BACKGROUND)) { std::cout << "Can't load HIGH_SCORE_BACKGROUND\n"; }
	highScoreSprite.setTexture(highScoreTexture);

	if (!optionsTexture.loadFromFile(OPTIONS_BACKGROUND)) { std::cout << "Can't load OPTIONS_BACKGROUND\n"; }
	optionsSprite.setTexture(optionsTexture);

	if (!creditsTexture.loadFromFile(CREDITS_BACKGROUND)) { std::cout << "Can't load CREDITS_BACKGROUND\n"; }
	creditsSprite.setTexture(creditsTexture);


	// Set OptionShadow Properties
	if(!optionShadowTexture.loadFromFile(MENU_SHADOW)) { std::cout << "Can't load MENU_SHADOW\n"; }
	optionShadowSprite.setTexture(optionShadowTexture);
	optionShadowSprite.setColor(Color(255, 255, 255, 100));

	// Set Music Ball Properties
	if (!musicBallTexture.loadFromFile(MUSIC_BALL)) { std::cout << "Can't load MUSIC_BALL\n"; }
	musicBallSprite.setTexture(musicBallTexture);
	musicBallSprite.setPosition(482, 410);

	// Set Difficulty Ball Properties
	if (!difficultyBallTexture.loadFromFile(DIFFICULTY_BALL)) { std::cout << "Can't load DIFFICULTY_BALL\n"; }
	difficultyBallSprite.setTexture(difficultyBallTexture);
	difficultyBallSprite.setPosition(1377, 363);

	// Set Control Ball Properties
	if (!controlBallTexture.loadFromFile(CONTROL_BALL)) { std::cout << "Can't load CONTROL_BALL\n"; }
	controlBallSprite.setTexture(controlBallTexture);
	controlBallSprite.setPosition(966, 255);

	// Set Back Text Properties
	backText.setString("press esc to back");
	backText.setFont(playerNameFont);
	backText.setCharacterSize(30);
	backText.setPosition(1350, 855);

	// Set Player Name Text Properties
	playerNameText.setFont(playerNameFont);
	playerNameText.setCharacterSize(70);
	playerNameText.setStyle(Text::Style::Bold);
	playerNameText.setPosition(447, 411);

	// Set High Score Text Properties
	highScoresPos.x = 440;
	highScoresPos.y = 185;
	for (int i = 0; i < 10; i++) {
		highScoreText[i][0].setFont(playerNameFont);
		highScoreText[i][1].setFont(playerNameFont);

		highScoreText[i][0].setCharacterSize(40);
		highScoreText[i][1].setCharacterSize(40);

		highScoreText[i][0].setPosition(highScoresPos.x, highScoresPos.y);
		highScoreText[i][1].setPosition(highScoresPos.x + 600, highScoresPos.y);
		highScoresPos.y += 56.5;
	}
	

	// Helper varibles
	float width = 628;
	float hight = 225;
	std::string OptionsTemp[6] = {
		"	  START",
		"HOW TO PLAY",
		"HIGH  SCORES",
		"    OPTIONS",
		"    CREDITS",
		"       EXIT"};

	for (int i = 0; i < 6; i++) {
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

		for (int i = 0; i < 6; i++) {
			window.draw(menuOptions[i]);
		}
	}
	else if (playerNameDisplay) {
		window.draw(playerNameSprite);
		window.draw(playerNameText);
		window.draw(backText);
	}
	else if (howToPlayDisplay) {
		window.draw(howToPlaySprite);
		window.draw(backText);
	}
	else if (highScoreDisplay) {
		window.draw(highScoreSprite);
		for (int i = 0; i < 10; i++) {
			window.draw(highScoreText[i][0]);
			window.draw(highScoreText[i][1]);
		}
		window.draw(backText);
	}
	else if (optionsDisplay) {
		window.draw(optionsSprite);
		window.draw(optionShadowSprite);
		window.draw(backText);
		window.draw(musicBallSprite);
		window.draw(controlBallSprite);
		window.draw(difficultyBallSprite);
	}
	else if (creditsDisplay) {
		window.draw(creditsSprite);
		window.draw(backText);
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


void Menu::catchEvents(Event& event) {
	if (mainMenuDisplay) {
		handleMenuEvents(event);
	}
	else if (playerNameDisplay) {
		handlePlayerNameEvents(event);
	}
	else if ((howToPlayDisplay || highScoreDisplay) || creditsDisplay) {
		handleBackEvent(event);
	}
	else if (optionsDisplay) {
		handleOptionsEvents(event);
	}
}


void Menu::handleMenuEvents(Event event) {
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
			mainMenuHandleSelection();
			break;
		}
		break;
	}
}


void Menu::handlePlayerNameEvents(Event event) {
	switch (event.type)
	{
	case Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Backspace:
			// Erase last character form string
			playerNameStr = playerNameStr.substring(0, playerNameStr.getSize() - 1);
			playerNameText.setString(playerNameStr);
			break;
		case sf::Keyboard::Enter:
			if (!playerNameStr.isEmpty()) {
				playerNameDisplay = false;

				// Convert sfml String to std String
				newPlayer.name = std::string(playerNameStr);
			}
			break;
		case Keyboard::Escape:
			openMainMenu();
			break;
		}
		break;

	case Event::TextEntered:
		bool notForbidinKeys = (!Keyboard::isKeyPressed(Keyboard::Enter) && !Keyboard::isKeyPressed(Keyboard::BackSpace)) && (!Keyboard::isKeyPressed(Keyboard::Escape) && !Keyboard::isKeyPressed(Keyboard::Space));
		if (playerNameStr.getSize() <= 20 && notForbidinKeys) {
			playerNameStr += event.text.unicode;
			playerNameText.setString(playerNameStr);
		}
		break;
	}
}


void Menu::handleOptionsEvents(Event event) {
	switch (event.type)
	{
	case Event::KeyReleased:
		switch (event.key.code)
		{
		case Keyboard::Right:
			changeOptionsMenu(true);
			break;

		case Keyboard::Left:
			changeOptionsMenu(false);
			break;

		case Keyboard::Up:
			moveOptionsUpDown(false);
			break;

		case Keyboard::Down:
			moveOptionsUpDown(true);
			break;

		case Keyboard::Escape:
			openMainMenu();
			break;
		}
		break;
	}
}


void Menu::handleBackEvent(Event event) {
	switch (event.type)
	{
	case Event::KeyReleased:
		switch (event.key.code)
		{
		case Keyboard::Escape:
			openMainMenu();
			break;
		}
		break;
	}
}

void Menu::moveOptionsUpDown(bool down) {
	switch (activeOptionsMenu) {
	case 0:
		changeActiveMusicOption();
		break;
	case 1:
		changeActiveControlOption();
		break;
	case 2:
		changeActiveDifficultyOption(down);
		break;
	}
}


void Menu::openMainMenu() {
	mainMenuDisplay = true;
	playerNameDisplay = highScoreDisplay = howToPlayDisplay = optionsDisplay = creditsDisplay = false;

	// Set shadow properties
	optionShadowSprite.setPosition(620, 295 + selectedOption * 70);
	optionShadowSprite.setScale(1, 1);
}


void Menu::openPlayerName() {
	playerNameDisplay = true;
	mainMenuDisplay = false;
}


void Menu::openHighScore() {
	highScoreDisplay = true;
	mainMenuDisplay = false;
	fillHighScore();
}


void Menu::openHowToPlay() {
	howToPlayDisplay = true;
	mainMenuDisplay = false;
}


void Menu::openOptions() {
	optionsDisplay = true;
	mainMenuDisplay = false;

	// Set shadow properties
	optionShadowSprite.setPosition(185, 140);
	optionShadowSprite.setScale(0.9, 1);
}


void Menu::openCredits() {
	creditsDisplay = true;
	mainMenuDisplay = false;
}


void Menu::mainMenuHandleSelection() {
	// Check current selected option
	switch (selectedOption)
	{
	case 0:
		openPlayerName();
		break;
	case 1:
		openHowToPlay();
		break;
	case 2:
		openHighScore();
		break;
	case 3:
		openOptions();
		break;
	case 4:
		openCredits();
		break;
	case 5:
		exit(0);
		break;
	}
}


int Menu::getNumberOfLines() {
	// Open the file to read 
	playersFile.open(PLAYERS_FILE);

	// Count how many lines in the file
	int cnt = 0;
	string temp;
	while (getline(playersFile, temp)) cnt++;

	playersFile.close();
	playersFile.clear();

	return cnt;
}


void Menu::arrangePlayersInfo() {
	int lines = getNumberOfLines();

	playersFile.open(PLAYERS_FILE);

	// Add players information to vector
	for (int i = 0; i < lines; i++) {
		playersFile >> newPlayer.name >> newPlayer.score >> newPlayer.level;
		players.push_back({ atoi(newPlayer.score.c_str()), {atoi(newPlayer.level.c_str()), newPlayer.name} });
	}

	playersFile.close();
	playersFile.clear();
}


void Menu::sortPlayersFile() {
	// Clear all players from vector
	players.clear();

	// get data from players file
	arrangePlayersInfo();

	// sort scores
	sort(players.rbegin(), players.rend());


	playersFile.open(PLAYERS_FILE);

	for (int i = 0; i < players.size(); i++) {
		playersFile << players[i].second.second << ' ' << players[i].first << ' ' << players[i].second.first << '\n';
	}
	playersFile.close();
	playersFile.clear();
}


void Menu::fillHighScore() {
	sortPlayersFile();

	for (int i = 0; i < 10; i++) {
		highScoreText[i][0].setString(players[i].second.second);
		highScoreText[i][1].setString(to_string(players[i].first));
	}
}


void Menu::changeOptionsMenu(bool Right) {
	if (Right) {
		// if box in Difficulty postion set to Music 
		if (optionShadowSprite.getPosition().x == 1105)
		{
			optionShadowSprite.setPosition(185, 140);
			activeOptionsMenu = 0;
		}
		else {
			optionShadowSprite.move(460, 0);
			activeOptionsMenu++;
		}
	}
	else {
		// if box in Music postion set to Difficulty 
		if (optionShadowSprite.getPosition().x == 185)
		{
			optionShadowSprite.setPosition(1105, 140);
			activeOptionsMenu = 2;
		}
		else {
			optionShadowSprite.move(-460, 0);
			activeOptionsMenu--;
		}
	}
}


void Menu::changeActiveMusicOption() {
	if (muteMusic) {
		musicBallSprite.setPosition(482, 410);
	}
	else {
		musicBallSprite.setPosition(482, 468);
	}
	muteMusic = !muteMusic;
	updateMusicSettings();
}


void Menu::updateMusicSettings() {
	if (muteMusic) {
		menuSound.pause();
	}
	else {
		menuSound.play();
	}
}

void Menu::changeActiveControlOption() {
	handControlled = !handControlled;
	if (handControlled) {
		controlBallSprite.setPosition(966, 450);
	}
	else {
		controlBallSprite.setPosition(966, 255);
	}
	updateControlSettings();
}


void Menu::updateControlSettings() {
	if (handControlled) {
		//system("python \"../Super Mario/HandControler/HandControl.py\"");
	}
	else {
		
	}
}


void Menu::changeActiveDifficultyOption(bool Down) {
	if (Down) {
		if (selectedDifficulty == 3) {
			difficultyBallSprite.setPosition(1377, 275);
			selectedDifficulty = 1;
		}
		else {
			difficultyBallSprite.move(0, 88);
			selectedDifficulty++;
		}
	}
	else {
		if (selectedDifficulty == 1) {
			difficultyBallSprite.setPosition(1377, 451);
			selectedDifficulty = 3;
		}
		else {
			difficultyBallSprite.move(0, -88);
			selectedDifficulty--;
		}
	}
	updateDifficultySettings();
}


void Menu::updateDifficultySettings() {
	switch (selectedDifficulty)
	{
	case 1:
		newPlayer.lifes = 5;
		break;
	case 2:
		newPlayer.lifes = 3;
		break;
	case 3:
		newPlayer.lifes = 1;
		break;
	default:
		break;
	}
}


