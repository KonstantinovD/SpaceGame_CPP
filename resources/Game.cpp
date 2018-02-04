#include "../include/Game.h"


void loadLevelFromFile()//every new level (spawn cordinates for instance) should be loaded from file
{
    float newInterval;

    LOGIC_GAME::LG().finp >> newInterval;
    TIMING::timeBetweenSpawning = newInterval;
    
    int val = 0;
    LOGIC_GAME::LG().finp >> LOGIC_GAME::LG().numberOfSpawns;

    for (int i = 0; i < LOGIC_GAME::LG().numberOfSpawns; i++)
    {
        LOGIC_GAME::LG().finp >> LOGIC_GAME::LG().coordinatesOfSpawn[i].x;
    }
    for (int i = 0; i < LOGIC_GAME::LG().numberOfSpawns; i++)
    {
        LOGIC_GAME::LG().finp >> LOGIC_GAME::LG().coordinatesOfSpawn[i].y;
    }
    LOGIC_GAME::LG().clockForDelay.restart();

    LOGIC_GAME::armorLeft = 3;
}

void initializeGameInterface(std::vector<std::unique_ptr<Appliance>>& panelsArray)//set up the game by loading textures etc.
{
	int numberOfDevices = 2;
	for (int i = 1; i <= numberOfDevices; i++)
	{
		std::ostringstream streamTurnIntIntoString;               //working with streams
		streamTurnIntIntoString << i;                             //loading number to the stream
		std::string numberOfFile = streamTurnIntIntoString.str(); //loading number from stream to the string

		std::unique_ptr<Appliance> device(new Appliance("TextSources\\Appliance" + numberOfFile + ".txt", 0, TextureHolder::TH()));
		panelsArray.push_back(std::move(device));
	}
}



Game::Game(sf::RenderWindow &userWindow) : enemySpawn(), mPlayer(sf::Vector2f(300, 420)), spaceLandscape(TextureHolder::TH())
{
    mWindow = &userWindow;

	initializeGameInterface(panelsArray);
	currentGameContinies = true;

	LOGIC_GAME::killedEnemys = 0;
	LOGIC_GAME::escapedEnemys = 0;
	LOGIC_GAME::spawnedEnemies = 0;
	LOGIC_GAME::iterator = -1;
	LOGIC_GAME::numberOfLevels = 0;
	LOGIC_GAME::spawnWork = true;
	LOGIC_GAME::armorLeft = 3;

    LOGIC_GAME::LG().positionArray[0] = sf::Vector2f(100, 0);
    LOGIC_GAME::LG().positionArray[1] = sf::Vector2f(100, 100);
    LOGIC_GAME::LG().positionArray[2] = sf::Vector2f(0, 253);
    LOGIC_GAME::LG().positionArray[3] = sf::Vector2f(200, 406);
    LOGIC_GAME::LG().positionArray[4] = sf::Vector2f(100, 559);
    LOGIC_GAME::LG().positionArray[5] = sf::Vector2f(100, 590);
}

void Game::run()//start game
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow->isOpen() && true == currentGameContinies)//game loop
	{
		processEvents();//process game events such as shooting
		timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TIME_PER_FRAME)//if calculations were quite hard and it takes more time than it was expected
		{//we update game again and again before rendering
            timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents();
            update(TIME_PER_FRAME);//updating the game
		}
		render();
	}
}

void Game::update(sf::Time deltaTime)//updating the game using time
{
	spaceLandscape.update(deltaTime, LOGIC_GAME::killedEnemys);
    //changes such as creating a new level and loading new spawn coordinates, for instance
	gameLogic();
    //update spawns
	if (true == LOGIC_GAME::spawnWork)
	{
		enemySpawn.updateSpawn();
	}
    //update player
	mPlayer.playerUpdate(deltaTime);
	if (mPlayer.isFire){//if player has shooted
		//Player creates new bullet
		playerBullets.push_back(std::unique_ptr<Bullet>(new Bullet(mPlayer.mSprite.getPosition() + sf::Vector2f(0, -15), true, (int)HITPOINTS_ENTITY::ID::Bullet)));
		mPlayer.isFire = false;
	}
    //update enemies
	int i = 0;
	while (i < enemySpawn.evil.size())
	{
		if (!(enemySpawn.evil[i]->enemyUpdate(deltaTime)))//If enemy is under LOWER_Deadline
		{
			LOGIC_GAME::escapedEnemys++;//Increasing the counter of enemies which escaped from player
			LOGIC_GAME::armorLeft--;
			enemySpawn.isAlive[enemySpawn.evil[i]->numberOfSpawns] = false;//We are getting order to spawn to create a new enemy
			enemySpawn.evil.erase(enemySpawn.evil.begin() + i);//And deleting current enemy
			continue;
		}
		if (enemySpawn.evil[i]->isFire)//If enemy is shooting
		{
			//Enemy creates new bullet
			enemyBullets.push_back(std::unique_ptr<Bullet>(new Bullet(enemySpawn.evil[i]->mSprite.getPosition() + sf::Vector2f(0, 30), false, (int)HITPOINTS_ENTITY::ID::Bullet)));
		}
		i++;
	}
    //update enemy's bullets
	i = 0;
	while (i < enemyBullets.size())//If enemy's bullet is destroyed
	{
		if (enemyBullets[i]->bulletUpdate(deltaTime)){
			enemyBullets.erase(enemyBullets.begin() + i);
			continue;
		}
		i++;
	}
    //update player's bullets
	i = 0;
	while (i < playerBullets.size())//If player's bullet is destroyed
	{
		if (playerBullets[i]->bulletUpdate(deltaTime)){
			playerBullets.erase(playerBullets.begin() + i);
			continue;
		}
		i++;
	}
	checkCollusions();
    panelsArray[0]->update(mPlayer.hitPoints);//update life and armor of player
	panelsArray[1]->update(LOGIC_GAME::armorLeft);
}

void Game::checkCollusions()//check collusions to delete enemy/bullet from the game process or to decrease the health of player
{
	int i = 0;
	int j = 0;
	while (i < enemySpawn.evil.size())//IF Enemy and Player collide
	{
		bool nextLoopIteration = false;
		j = 0;
		if (enemySpawn.evil[i]->mSprite.getGlobalBounds().intersects(mPlayer.mSprite.getGlobalBounds())) 
		{
            decreaseHP(enemySpawn.evil[i]->hitPoints, mPlayer.hitPoints);

            if (enemySpawn.evil[i]->hitPoints <= 0)//Player has killed the enemy
			{
				LOGIC_GAME::killedEnemys++;//Increasing the counter of killed enemies

				enemySpawn.isAlive[enemySpawn.evil[i]->numberOfSpawns] = false;
				enemySpawn.evil.erase(enemySpawn.evil.begin() + i);
				continue;
			}	
		}
		while (j < playerBullets.size())//IF Enemy and PlayerBullet collide
		{
			if (enemySpawn.evil[i]->mSprite.getGlobalBounds().intersects(playerBullets[j]->mSprite.getGlobalBounds())) 
			{
                decreaseHP(enemySpawn.evil[i]->hitPoints, playerBullets[j]->hitPoints);

				playerBullets.erase(playerBullets.begin() + j);

                if (enemySpawn.evil[i]->hitPoints <= 0)//Player has killed the enemy
				{
					LOGIC_GAME::killedEnemys++;//Increasing the counter of killed enemies

					enemySpawn.isAlive[enemySpawn.evil[i]->numberOfSpawns] = false;
					enemySpawn.evil.erase(enemySpawn.evil.begin() + i);
					nextLoopIteration = true;
					break;//If enemy is dead, we just break the loop, because in that case another bullets don't bother us
				}		
				continue;//If these objects collide, we erase bullet at least, and we can't increment the bullet counter
			}
			j++;//If these objects don't collide, we do the next iteration
		}

		if (true != nextLoopIteration)
		{
			i++;
		}
	}
	j = 0;
	while (j < enemyBullets.size())//IF Player and EnemyBullet collide
	{
		
		if (mPlayer.mSprite.getGlobalBounds().intersects(enemyBullets[j]->mSprite.getGlobalBounds())) 
		{
            decreaseHP(mPlayer.hitPoints, enemyBullets[j]->hitPoints);
			enemyBullets.erase(enemyBullets.begin() + j);
			continue;
		}
		j++;
	}
}

void Game::render()//draw the game after all updations
{
	mWindow->clear();
    mWindow->draw(spaceLandscape);

	for (int i = 0; i < panelsArray.size(); i++)//Draw interface
	{
        mWindow->draw(*panelsArray[i]);
	}

    mWindow->draw(mPlayer);

	for (int i = 0; i < enemySpawn.evil.size(); i++)//Draw enemies
	{
        mWindow->draw(*enemySpawn.evil[i]);
	}
	for (int i = 0; i < playerBullets.size(); i++)//Draw player's bullets
	{
        mWindow->draw(*playerBullets[i]);
	}
	for (int i = 0; i < enemyBullets.size(); i++)//Draw enemy's bullets
	{
        mWindow->draw(*enemyBullets[i]);
	}
	

    mWindow->display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)//events on keyboard
{
	if (isPressed)//If key is pressed
	{
		if (key == sf::Keyboard::Key::Delete)
		{
			for (int i = enemySpawn.evil.size(); i > 0; i--)
			{
				enemySpawn.evil.erase(enemySpawn.evil.begin());
				enemySpawn.isAlive[i - 1] = false;
			}
		}

		if (key == sf::Keyboard::Key::A)
		{
			mPlayer.isMovingLeft = true;
		}
		if (key == sf::Keyboard::Key::D)
		{
			mPlayer.isMovingRight = true;
		}
		if (key == sf::Keyboard::Key::W)
		{
			mPlayer.isAttack = true;
		}
	}
	else  //If key is released
	{
		if (key == sf::Keyboard::Key::A)
		{
			mPlayer.isMovingLeft = false;
		}
		if (key == sf::Keyboard::Key::D)
		{
			mPlayer.isMovingRight = false;
		}
		if (key == sf::Keyboard::Key::W)
		{
			mPlayer.isAttack = false;
		}
	}
}

void Game::processEvents()//choosing from key pressing\releasing and closing the window
{
	sf::Event event;
    while (mWindow->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
            mWindow->close();
			break;
		}
	}
}

void Game::gameOver()
{
    LOGIC_GAME::LG().finp.close();
	currentGameContinies = false;

    showGameOverString(mWindow, LOGIC_GAME::killedEnemys);
}

void Game::decreaseHP(int &firstEntity, int &secondEntity)//if collusion appears each entity causes a damage equal to its own HP
{
	int temporaryVar = firstEntity;
	firstEntity -= secondEntity;
	secondEntity -= temporaryVar;
}

void Game::gameLogic()//after a defifinite number of killed\escaped enemies new level is loaded + processing game over
{
	int currentNumber = LOGIC_GAME::escapedEnemys + LOGIC_GAME::killedEnemys;

    //if no level is loaded
	if (0 == currentNumber&&-1 == LOGIC_GAME::iterator)
	{
		LOGIC_GAME::iterator = 0;
        LOGIC_GAME::LG().finp.open("TextSources\\Levels.txt");

        LOGIC_GAME::LG().finp >> LOGIC_GAME::numberOfLevels;

				for (int i = 0; i < (LOGIC_GAME::numberOfLevels - 1); i++)
		{
            LOGIC_GAME::LG().finp >> LOGIC_GAME::necessaryPointsToChangeLevel[i];
		}

        LOGIC_GAME::LG().finp >> LOGIC_GAME::LG().delay;

        loadLevelFromFile();
        enemySpawn.setNewSpawn(LOGIC_GAME::LG().coordinatesOfSpawn, LOGIC_GAME::LG().numberOfSpawns);
	}
    //if we need to load a new level, we update player's health and armor
	if (LOGIC_GAME::iterator < (LOGIC_GAME::numberOfLevels - 1) && currentNumber >= LOGIC_GAME::necessaryPointsToChangeLevel[LOGIC_GAME::iterator])
	{
		LOGIC_GAME::iterator++;
		loadLevelFromFile();
        enemySpawn.setNewSpawn(LOGIC_GAME::LG().coordinatesOfSpawn, LOGIC_GAME::LG().numberOfSpawns);
		mPlayer.hitPoints = HITPOINTS_ENTITY::ID::Player;
	}

	LOGIC_GAME::spawnWork = true;
    if (LOGIC_GAME::LG().clockForDelay.getElapsedTime().asSeconds() < LOGIC_GAME::LG().delay)
	{
		LOGIC_GAME::spawnWork = false;
	}

	if ((LOGIC_GAME::iterator+1) < LOGIC_GAME::numberOfLevels)
	{
		if (LOGIC_GAME::spawnedEnemies >= LOGIC_GAME::necessaryPointsToChangeLevel[LOGIC_GAME::iterator])
		{
			LOGIC_GAME::spawnWork = false;
		}
	}
    //when game is over
	if (mPlayer.hitPoints <= 0)
	{
		gameOver();
	}
	if (LOGIC_GAME::armorLeft <= 0)
	{
		gameOver();
	}
}

//////////////////////// MAIN LOOP ////////////////////////////////////////////////////////////////////////////////////////////////
void gameLoop(sf::RenderWindow& mWindow)
{
	srand(time(0));
	mWindow.setKeyRepeatEnabled(false);//We prevent our KeyPressed event from repeating again and again
	
    Menu myMenu(TextureHolder::TH());

	while (mWindow.isOpen())
	{
		mWindow.clear();
        int rezCondition = myMenu.update(mWindow, TextureHolder::TH());

		if (300 == rezCondition)//if "start" is pressed
		{
			Game game(mWindow);
			game.run();
			myMenu.reset();
		}
        if (0==rezCondition)//if "exit" is pressed
        {
            mWindow.close();
        }

		mWindow.draw(myMenu);
		mWindow.display();
	}
	mWindow.clear();
	mWindow.display();
}
