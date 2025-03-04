#pragma once
#include <mutex>
#include <string>

#include "IExecutionEvent.h"
#include "IWorkerAction.h"
class BatchAssetLoader :
    public IWorkerAction, IExecutionEvent
{
private:
    typedef std::string String;
public:
    BatchAssetLoader(IExecutionEvent* executionEvent);
    ~BatchAssetLoader();

    void onStartTask() override;
    void onFinishedExecution() override;

private:
    std::mutex guard;
    //String path;
    const std::string STREAMING_PATH = "Media/Streaming/";
    IExecutionEvent* execEvent;

    int nBatchDone = 0;
    int index = 0;
};

