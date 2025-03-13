#include "LoadingScreenManager.h"

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

bool LoadingScreenManager::isLoadingAnimDone()
{
	return this->finishLoadingAnim;
}

void LoadingScreenManager::setLoadingAnimDone(bool value)
{
	this->finishLoadingAnim = true;
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

LoadingScreenManager::LoadingScreenManager()
{
}
