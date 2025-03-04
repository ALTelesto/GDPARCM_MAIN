#include "BatchAssetLoader.h"

#include <filesystem>
#include <iostream>

#include "StreamAssetLoader.h"
#include "TextureManager.h"

BatchAssetLoader::BatchAssetLoader(IExecutionEvent* executionEvent)
{
	this->execEvent = executionEvent;
}

BatchAssetLoader::~BatchAssetLoader()
{
	std::cout << "Destroying batch asset loader. " << std::endl;
}

void BatchAssetLoader::onStartTask()
{
    std::vector<std::filesystem::directory_entry> entries;
    for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH))
    {
        entries.push_back(entry);
    }
    int batchSize = 50;
    while (this->index < entries.size() - 1)
    {
        int currentBatch = 0;
        while(currentBatch < batchSize)
        {
            std::string path = entries[this->index].path().generic_string();
            StreamAssetLoader* assetLoader = new StreamAssetLoader(path, this);
            TextureManager::getInstance()->getThreadPool()->scheduleTask(assetLoader);
            currentBatch++;
            this->index++;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }

        while (this->nBatchDone < currentBatch)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        if (this->nBatchDone <= 0) break;

        for (int i = 0; i < this->nBatchDone; i++)
        {
            this->execEvent->onFinishedExecution();
        }
        this->nBatchDone = 0;

    }

    delete this;
}

void BatchAssetLoader::onFinishedExecution()
{
	this->guard.lock();
	nBatchDone++;
	this->guard.unlock();
}
