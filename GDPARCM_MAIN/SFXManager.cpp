#include <fstream>
#include <iostream>
#include <filesystem>

#include "SFXManager.h"

#include "StringUtils.h"

//a singleton class
SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::getInstance()
{
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new SFXManager();
	}

	return sharedInstance;
}

SFXManager::SFXManager()
{
	this->countStreamingAssets();
}

void SFXManager::countStreamingAssets()
{
	this->streamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		this->streamingAssetCount++;
	}
	std::cout << "[SFXManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
}

void SFXManager::loadFromAssetList()
{
	std::cout << "[SFXManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/sfx.txt");
	String path;

	while (std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsSound(path, assetName, false);
		std::cout << "[SFXManager] Loaded texture: " << assetName << std::endl;
	}
}

sf::SoundBuffer* SFXManager::getFromSoundMap(const String assetName)
{
	if (this->soundMap[assetName] != nullptr) {
		return this->soundMap[assetName];
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return NULL;
	}
}

sf::SoundBuffer* SFXManager::getStreamSoundFromList(const int index)
{
	return this->streamingSoundList[index];
}

void SFXManager::instantiateAsSound(String path, String assetName, bool isStreaming)
{
	std::cout << "[SFXManager] Loading: " << assetName << std::endl;
	sf::SoundBuffer* sound = new sf::SoundBuffer;
	sound->loadFromFile(path);
	this->soundMap[assetName] = sound;

	if(isStreaming)
	{
		this->streamingSoundList.push_back(sound);
	}
	else
	{
		this->baseSoundList.push_back(sound);
	}
}

void SFXManager::onFinishedExecution()
{
}

int SFXManager::getStreamingAssetCount()
{
	return this->streamingAssetCount;
}


