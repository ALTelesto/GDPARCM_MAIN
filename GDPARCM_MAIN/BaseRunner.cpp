#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "FPSCounter.h"
#include <iostream>

#include "AnimatedSprite.h"
#include "BeatBG.h"
#include "BeatCircle.h"
#include "LoadingBar.h"
#include "LoadingDoneText.h"
#include "LoadingScreenManager.h"
#include "MusicPlayer.h"
#include "SFXManager.h"
#include "StaticSprite.h"
#include "ThreadManager.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const float FRAME_RATE = 60.0f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.0f / FRAME_RATE);
BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Divisi", sf::Style::Close) {

	sharedInstance = this;
	this->window.setFramerateLimit(int(FRAME_RATE));

	ThreadManager::getInstance();

	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load initial sfx
	SFXManager::getInstance()->loadFromAssetList();

	LoadingScreenManager::getInstance()->startLoading();

	//load objects
	BeatBG* bgObject = new BeatBG("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	sf::Color beatColor[] = {
		sf::Color(255,0,0,255),
		sf::Color(255,125,0,255),
		sf::Color(255,200,0,255),
		sf::Color(0,255,0,255),
		sf::Color(0,255,200,255),
		sf::Color(0,125,255,255),
		sf::Color(125,0,255,255),
		sf::Color(200,0,255,255),
	};

	float bpm = 15.0;
	int beats = 8;
	float widthPartition = WINDOW_WIDTH / (beats+1);
	float heightPartition = WINDOW_HEIGHT / 5;

	//lines
	StaticSprite* topLine = new StaticSprite("TopLine", "beatline");
	topLine->setPosition(100, heightPartition - (heightPartition / 2));
	topLine->setColor(sf::Color(255, 255, 255, 100));
	GameObjectManager::getInstance()->addObject(topLine);

	StaticSprite* bottomLine = new StaticSprite("BottomLine", "beatline");
	bottomLine->setPosition(100, heightPartition + heightPartition * 3 + 100);
	bottomLine->setColor(sf::Color(255, 255, 255, 100));
	GameObjectManager::getInstance()->addObject(bottomLine);

	//loading bar
	LoadingBar* loadingBar = new LoadingBar("LoadingBar");
	loadingBar->setPosition(100, heightPartition + heightPartition * 3 + 105);
	loadingBar->setScale(1, 10);
	GameObjectManager::getInstance()->addObject(loadingBar);

	//beat circles
	for(int i = 0; i < beats; i++)
	{
		BeatCircle* circle = new BeatCircle("Beat "+i,i);
		float x = widthPartition + (widthPartition*i) - (widthPartition/3);
		circle->setHome(x, heightPartition - (heightPartition / 2));
		circle->setTarget(x, heightPartition + heightPartition * 3);
		float beatSpeed = (bpm - (0.25 * i)) / 60.0;
		circle->setSpeed(beatSpeed);
		circle->setBeatColor(beatColor[i]);
		GameObjectManager::getInstance()->addObject(circle);
	}

	LoadingDoneText* doneText = new LoadingDoneText("Loading Done");
	GameObjectManager::getInstance()->addObject(doneText);

	FPSCounter* fpsCounter = new FPSCounter();
	fpsCounter->setLayer(2);
	GameObjectManager::getInstance()->addObject(fpsCounter);
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	while (this->window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		this->fps = floor(1.0f / deltaTime);

		processEvents();
		update(sf::seconds(1.0f / this->fps));
		render();

		previousTime = currentTime;
	}
}

BaseRunner* BaseRunner::getInstance()
{
	return sharedInstance;
}

float BaseRunner::getFPS() const
{
	return this->fps;
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
		
		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}