#pragma once
#include <mutex>
#include <string>

#include "IExecutionEvent.h"
#include "IWorkerAction.h"
class LoadingAssetLoader :
    public IWorkerAction, IExecutionEvent
{
private:
    typedef std::string String;
public:
    LoadingAssetLoader(IExecutionEvent* executionEvent);
    ~LoadingAssetLoader();

    void onFinishedExecution() override;
    void onStartTask() override;

private:
    std::mutex guard;

    const std::string TEXTURE_STREAMING_PATH = "Media/Streaming/";
    const std::string SFX_STREAMING_PATH = "Media/SFXStreaming/";
    IExecutionEvent* execEvent;

    int index = 0;

    int totalCount = 0;
    int done = 0;
};

