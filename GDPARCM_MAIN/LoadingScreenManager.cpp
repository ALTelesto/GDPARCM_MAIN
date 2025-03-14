#include "LoadingScreenManager.h"

#include "AnimatedSprite.h"
#include "BaseRunner.h"
#include "BGObject.h"
#include "GameObjectManager.h"
#include "LoadingAssetLoader.h"
#include "MusicPlayer.h"
#include "StaticSprite.h"
#include "TextureManager.h"
#include "ThreadManager.h"
#include "Thrower.h"

LoadingScreenManager* LoadingScreenManager::sharedInstance = nullptr;

LoadingScreenManager* LoadingScreenManager::getInstance()
{
	if (sharedInstance == nullptr) {
		//initialize
		sharedInstance = new LoadingScreenManager();
	}

	return sharedInstance;
}

void LoadingScreenManager::setProgress(float value)
{
	this->progress = value;

	if(this->progress >= 1.0f)
	{
		this->progress = 1.0f;
	}
	if(this->progress <= 0.0f)
	{
		this->progress = 0.0f;
	}
}

float LoadingScreenManager::getProgress()
{
	return this->progress;
}

bool LoadingScreenManager::isDone()
{
	return (this->progress >= 1.0f);
}

void LoadingScreenManager::startLoading()
{
	LoadingAssetLoader* thread = new LoadingAssetLoader(this);
	ThreadManager::getInstance()->scheduleTask(thread);
}

void LoadingScreenManager::loadScene()
{
	GameObjectManager::getInstance()->deleteObjectByName("TopLine");
	GameObjectManager::getInstance()->deleteObjectByName("BottomLine");
	GameObjectManager::getInstance()->deleteObjectByName("BGObject");

	//loaded scene stuff
	std::vector<std::string> frames;

	MusicPlayer* musicPlayer = new MusicPlayer("musicplayer");
	GameObjectManager::getInstance()->addObject(musicPlayer);

	BGObject* rain = new BGObject("rain");
	GameObjectManager::getInstance()->addObject(rain);

	StaticSprite* gradient = new StaticSprite("gradient");
	gradient->setTexture("gradientLarge");
	gradient->setScale(0.5, 0.5);
	gradient->setColor(sf::Color(0, 0, 0, 150));
	GameObjectManager::getInstance()->addObject(gradient);

	Thrower* thrower = new Thrower("thrower");
	GameObjectManager::getInstance()->addObject(thrower);

	AnimatedSprite* girl = new AnimatedSprite("girl");
	frames = { "biggirl0","biggirl1","biggirl2" };
	girl->setFrames(frames);
	//girl->setScale(0.037, 0.037);
	girl->setScale(0.185, 0.185);
	girl->setPosition(BaseRunner::WINDOW_WIDTH / 2 - 342.25 / 2 - 220, BaseRunner::WINDOW_HEIGHT - 640);
	girl->setLayer(1);
	GameObjectManager::getInstance()->addObject(girl);

	AnimatedSprite* man = new AnimatedSprite("man");
	frames = { "bigman0","bigman1","bigman2" };
	man->setFrames(frames);
	man->setScale(0.185, 0.185);
	man->setPosition(BaseRunner::WINDOW_WIDTH / 2 - 342.25 / 2, BaseRunner::WINDOW_HEIGHT - 660);
	man->setLayer(1);
	GameObjectManager::getInstance()->addObject(man);

	AnimatedSprite* title = new AnimatedSprite("title");
	frames = { "divisi0","divisi1","divisi2" };
	title->setFrames(frames);
	title->setScale(0.5, 0.5);
	title->setLayer(1);
	GameObjectManager::getInstance()->addObject(title);
}

int LoadingScreenManager::getObjectNum()
{
	return this->spawnedObjects;
}

void LoadingScreenManager::addObject()
{
	spawnedObjects++;
}

void LoadingScreenManager::removeObject()
{
	spawnedObjects--;
}

void LoadingScreenManager::onFinishedExecution()
{
}

LoadingScreenManager::LoadingScreenManager()
{
}
