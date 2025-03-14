#pragma once
#include "IExecutionEvent.h"

class LoadingScreenManager : public IExecutionEvent
{
public:
	static LoadingScreenManager* getInstance();

	void setProgress(float value);
	float getProgress();

	bool isDone();

	void startLoading();

	void loadScene();

	int getObjectNum();
	void addObject();
	void removeObject();

	void onFinishedExecution() override;

private:
	LoadingScreenManager();
	LoadingScreenManager(LoadingScreenManager const&) {};             // copy constructor is private
	LoadingScreenManager& operator=(LoadingScreenManager const&) {};  // assignment operator is private
	static LoadingScreenManager* sharedInstance;

	float progress = 0.0f;

	int spawnedObjects = 0;
};

