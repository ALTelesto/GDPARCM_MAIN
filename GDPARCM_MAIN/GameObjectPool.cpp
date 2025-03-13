#include "GameObjectPool.h"

#include "GameObjectManager.h"

GameObjectPool::GameObjectPool(int poolSize, PoolableObject* poolableObject) : poolSize(poolSize), poolableObject(poolableObject)
{
}

GameObjectPool::~GameObjectPool()
{
}

void GameObjectPool::initialize()
{
    PoolableObject* newPoolable;

    for (int i = 0; i < this->poolSize; i++) {
        newPoolable = this->poolableObject->clone();


    	GameObjectManager::getInstance()->addObject(newPoolable);

        newPoolable->setEnabled(false);
        this->vecAvailableObject.push_back(newPoolable);
    }
}

PoolableObject* GameObjectPool::requestPoolable()
{
    PoolableObject* pPoolableObject = NULL;

    if (this->hasAvailable(1)) {
        pPoolableObject = this->vecAvailableObject[0];
        this->vecUsedObject.push_back(pPoolableObject);
        this->vecAvailableObject.erase(this->vecAvailableObject.begin());

        this->setEnabled(pPoolableObject, true);
    }

    return pPoolableObject;
}

std::vector<PoolableObject*> GameObjectPool::requestPoolableBatch(int nRequestSize)
{
    std::vector<PoolableObject*> vecPoolableBatch = {};

    if (this->hasAvailable(nRequestSize)) {
        for (int i = 0; i < nRequestSize; i++)
            vecPoolableBatch.push_back(this->requestPoolable());
    }

    return vecPoolableBatch;
}

void GameObjectPool::releasePoolable(PoolableObject* pPoolableObject)
{
    int nIndex = -1;

    for (int i = 0; i < this->vecUsedObject.size() && nIndex == -1; i++) {
        if (this->vecUsedObject[i] == pPoolableObject)
            nIndex = i;
    }

    if (nIndex != -1) {
        this->vecAvailableObject.push_back(pPoolableObject);
        this->vecUsedObject.erase(this->vecUsedObject.begin() + nIndex);
        this->setEnabled(pPoolableObject, false);
    }
}

void GameObjectPool::releasePoolableBatch(std::vector<PoolableObject*> vecPoolableObject)
{
    for (int i = 0; i < vecPoolableObject.size(); i++)
        this->releasePoolable(vecPoolableObject[i]);
}

bool GameObjectPool::hasAvailable(int nRequestSize)
{
    if (this->vecAvailableObject.size() >= nRequestSize)
        return true;

    return false;
}

void GameObjectPool::setEnabled(PoolableObject* pPoolableObject, bool bEnabled)
{
    pPoolableObject->setEnabled(bEnabled);

    if (bEnabled)
        pPoolableObject->onActivate();

    else
        pPoolableObject->onRelease();
}
