#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"
#include <iostream>

#include "AnimatedSprite.h"
#include "BeatBG.h"
#include "BeatCircle.h"
#include "LoadingBar.h"
#include "LoadingDoneText.h"
#include "LoadingScreenManager.h"
#include "SFXManager.h"
#include "StaticSprite.h"
#include "Thrower.h"

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

	//load initial sfx
	SFXManager::getInstance()->loadFromAssetList();

	LoadingScreenManager::getInstance();

	//load objects
	//BGObject* bgObject = new BGObject("BGObject");
	//GameObjectManager::getInstance()->addObject(bgObject);

	//TextureDisplay* display = new TextureDisplay();
	//GameObjectManager::getInstance()->addObject(display);
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
	/*StaticSprite* test = new StaticSprite("test", "whitebg");
	GameObjectManager::getInstance()->addObject(test);*/
	StaticSprite* topLine = new StaticSprite("TopLine", "beatline");
	topLine->setPosition(100, heightPartition - (heightPartition / 2));
	topLine->setColor(sf::Color(255, 255, 255, 100));
	GameObjectManager::getInstance()->addObject(topLine);

	StaticSprite* bottomLine = new StaticSprite("BottomLine", "beatline");
	bottomLine->setPosition(100, heightPartition + heightPartition * 3 + 100);
	bottomLine->setColor(sf::Color(255, 255, 255, 100));
	GameObjectManager::getInstance()->addObject(bottomLine);

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

	//loaded scene stuff
	std::vector<std::string> frames;

	/*StaticSprite* white = new StaticSprite("white");
	white->setTexture("whitebg");

	BGObject* rain = new BGObject("rain");
	GameObjectManager::getInstance()->addObject(rain);*/

	Thrower* thrower = new Thrower("thrower");
	GameObjectManager::getInstance()->addObject(thrower);

	/*AnimatedSprite* girl = new AnimatedSprite("girl");
	frames = { "biggirl0","biggirl1","biggirl2" };
	girl->setFrames(frames);
	girl->setScale(0.037, 0.037);
	girl->setPosition(WINDOW_WIDTH / 2 - 342.25 / 2 - 220, WINDOW_HEIGHT - 640);
	GameObjectManager::getInstance()->addObject(girl);

	AnimatedSprite* man = new AnimatedSprite("man");
	frames = { "bigman0","bigman1","bigman2"};
	man->setFrames(frames);
	man->setScale(0.037, 0.037);
	man->setPosition(WINDOW_WIDTH / 2 - 342.25/2, WINDOW_HEIGHT - 660);
	GameObjectManager::getInstance()->addObject(man);*/

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