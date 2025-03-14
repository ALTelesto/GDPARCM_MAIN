#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Audio/SoundBuffer.hpp>

#include "IExecutionEvent.h"
#include "ThreadPool.h"

class SFXManager :
    public IExecutionEvent
{
public:
	typedef std::string String;
	typedef std::vector<sf::SoundBuffer*> SoundList;
	typedef std::unordered_map<String, sf::SoundBuffer*> HashTable;
public:
	static SFXManager* getInstance();
	void loadFromAssetList();

	sf::SoundBuffer* getFromSoundMap(const String assetName);

	sf::SoundBuffer* getStreamSoundFromList(const int index);

	void instantiateAsSound(String path, String assetName, bool isStreaming);

	void onFinishedExecution() override;

	int getStreamingAssetCount();

private:
	SFXManager();
	SFXManager(SFXManager const&) {};             // copy constructor is private
	SFXManager& operator=(SFXManager const&) {};  // assignment operator is private
	static SFXManager* sharedInstance;

	void countStreamingAssets();
	int streamingAssetCount = 0;

	HashTable soundMap;
	SoundList baseSoundList;
	SoundList streamingSoundList;

	const std::string STREAMING_PATH = "Media/SFXStreaming/";

};

