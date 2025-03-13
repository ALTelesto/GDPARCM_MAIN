#pragma once
#include "PoolableObject.h"

class GameObjectPool
{
private:
	int poolSize;
	PoolableObject* poolableObject;

	std::vector<PoolableObject*> vecAvailableObject;
	std::vector<PoolableObject*> vecUsedObject;
public:
	GameObjectPool(int poolSize, PoolableObject* poolableObject);
	~GameObjectPool();

	void initialize();

	PoolableObject* requestPoolable();
	std::vector<PoolableObject*> requestPoolableBatch(int nRequestSize);
	void releasePoolable(PoolableObject* pPoolableObject);
	void releasePoolableBatch(std::vector<PoolableObject*> vecPoolableObject);

private:
	bool hasAvailable(int nRequestSize);
	void setEnabled(PoolableObject* pPoolableObject, bool bEnabled);
};

