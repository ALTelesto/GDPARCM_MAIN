#pragma once
class LoadingScreenManager
{
public:
	static LoadingScreenManager* getInstance();

	void setProgress(float value);
	float getProgress();

	bool isDone();

	bool isLoadingAnimDone();
	void setLoadingAnimDone(bool value);

	int getObjectNum();
	void addObject();
	void removeObject();

private:
	LoadingScreenManager();
	LoadingScreenManager(LoadingScreenManager const&) {};             // copy constructor is private
	LoadingScreenManager& operator=(LoadingScreenManager const&) {};  // assignment operator is private
	static LoadingScreenManager* sharedInstance;

	float progress = 0.0f;
	bool finishLoadingAnim = false;

	int spawnedObjects = 0;
};

