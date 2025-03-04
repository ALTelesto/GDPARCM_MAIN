#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"
#include <iostream>

#include "BeatBG.h"
#include "BeatCircle.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const float FRAME_RATE = 60.0f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.0f / FRAME_RATE);
BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Entity Component", sf::Style::Close) {

	sharedInstance = this;
	this->window.setFramerateLimit(int(FRAME_RATE));

	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	//BGObject* bgObject = new BGObject("BGObject");
	//GameObjectManager::getInstance()->addObject(bgObject);

	//TextureDisplay* display = new TextureDisplay();
	//GameObjectManager::getInstance()->addObject(display);
	BeatBG* bgObject = new BeatBG("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	float bpm = 20.0;
	int beats = 8;
	float widthPartition = WINDOW_WIDTH / (beats+1);
	float heightPartition = WINDOW_HEIGHT / 5;
	for(int i = 0; i < beats; i++)
	{
		BeatCircle* circle = new BeatCircle("Beat "+i);
		float x = widthPartition + (widthPartition*i) - (widthPartition/3);
		circle->setHome(x, heightPartition - (heightPartition / 2));
		circle->setTarget(x, heightPartition + heightPartition * 3);
		float beatSpeed = (bpm - (0.25 * i)) / 60.0;
		circle->setSpeed(beatSpeed);
		GameObjectManager::getInstance()->addObject(circle);
	}

	FPSCounter* fpsCounter = new FPSCounter();
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