#include "LoadingAssetLoader.h"

#include <filesystem>
#include <iostream>

#include "LoadingScreenManager.h"
#include "SFXManager.h"
#include "StreamAssetLoader.h"
#include "TextureManager.h"
#include "ThreadManager.h"

LoadingAssetLoader::LoadingAssetLoader(IExecutionEvent* executionEvent)
{
	this->execEvent = executionEvent;
}

LoadingAssetLoader::~LoadingAssetLoader()
{
	std::cout << "Destroying loading asset loader. " << std::endl;
}

void LoadingAssetLoader::onFinishedExecution()
{
	this->guard.lock();
	done++;
    LoadingScreenManager::getInstance()->setProgress((float)done / totalCount);
    std::cout << "Loading asset done = " << done << std::endl;
	this->guard.unlock();
}

void LoadingAssetLoader::onStartTask()
{
    totalCount += TextureManager::getInstance()->getStreamingAssetCount();
    totalCount += SFXManager::getInstance()->getStreamingAssetCount();

    std::vector<std::filesystem::directory_entry> entries;

    for (const auto& entry : std::filesystem::directory_iterator(SFX_STREAMING_PATH))
    {
        entries.push_back(entry);
    }
    this->index = 0;
    while (this->index < entries.size())
    {
        std::string path = entries[this->index].path().generic_string();
        StreamAssetLoader* assetLoader = new StreamAssetLoader(path, this,false);
        ThreadManager::getInstance()->scheduleTask(assetLoader);
        this->index++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    entries.clear();
    for (const auto& entry : std::filesystem::directory_iterator(TEXTURE_STREAMING_PATH))
    {
        entries.push_back(entry);
    }

    this->index = 0;
    while (this->index < entries.size())
    {
        std::string path = entries[this->index].path().generic_string();
        StreamAssetLoader* assetLoader = new StreamAssetLoader(path, this,true);
        ThreadManager::getInstance()->scheduleTask(assetLoader);
        this->index++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    while(this->done < this->totalCount)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    delete this;
}
