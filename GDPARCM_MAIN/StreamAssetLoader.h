#pragma once
#include "IETThread.h"
#include "IWorkerAction.h"
class IExecutionEvent;
class StreamAssetLoader :
	public IWorkerAction
{
private:
	typedef std::string String;
public:
	StreamAssetLoader(String path, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

	void onStartTask() override;

private:
	String path;
	IExecutionEvent* execEvent;
};

