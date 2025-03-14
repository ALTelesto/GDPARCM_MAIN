#include <stddef.h>
#include "GameObjectManager.h"
#include <iostream>

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new GameObjectManager();
	}

	return sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(AGameObject::String name)
{
	if (this->gameObjectMap[name] != NULL) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

List GameObjectManager::getAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->gameObjectList.size() + this->gameObjectList1.size();
}

void GameObjectManager::processInput(sf::Event event) {
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		this->gameObjectList[i]->processInput(event);
	}
	for (int i = 0; i < this->gameObjectList1.size(); i++)
	{
		this->gameObjectList1[i]->processInput(event);
	}
	for (int i = 0; i < this->gameObjectList2.size(); i++)
	{
		this->gameObjectList2[i]->processInput(event);
	}
}

void GameObjectManager::update(sf::Time deltaTime)
{
	//std::cout << "Delta time: " << deltaTime.asSeconds() << "\n";
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if(this->gameObjectList[i]->isEnabled()) this->gameObjectList[i]->update(deltaTime);
	}
	for (int i = 0; i < this->gameObjectList1.size(); i++)
	{
		if (this->gameObjectList1[i]->isEnabled()) this->gameObjectList1[i]->update(deltaTime);
	}
	for (int i = 0; i < this->gameObjectList2.size(); i++)
	{
		if (this->gameObjectList2[i]->isEnabled()) this->gameObjectList2[i]->update(deltaTime);
	}
}

//draws the object if it contains a sprite
void GameObjectManager::draw(sf::RenderWindow* window) {
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i]->isEnabled()) this->gameObjectList[i]->draw(window);
	}
	for (int i = 0; i < this->gameObjectList1.size(); i++)
	{
		if (this->gameObjectList1[i]->isEnabled()) this->gameObjectList1[i]->draw(window);
	}
	for (int i = 0; i < this->gameObjectList2.size(); i++)
	{
		if (this->gameObjectList2[i]->isEnabled()) this->gameObjectList2[i]->draw(window);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	//also initialize the oject
	this->gameObjectMap[gameObject->getName()] = gameObject;
	if(gameObject->getLayer() == 0) this->gameObjectList.push_back(gameObject);
	else if(gameObject->getLayer() == 1) this->gameObjectList1.push_back(gameObject);
	else this->gameObjectList2.push_back(gameObject);
	this->gameObjectMap[gameObject->getName()]->initialize();
}

//also frees up allocation of the object.
void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	if(gameObject->getLayer() == 0)
	{
		for (int i = 0; i < this->gameObjectList.size(); i++) {
			if (this->gameObjectList[i] == gameObject) {
				index = i;
				break;
			}
		}
	}
	else if (gameObject->getLayer() == 1)
	{
		for (int i = 0; i < this->gameObjectList1.size(); i++) {
			if (this->gameObjectList1[i] == gameObject) {
				index = i;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < this->gameObjectList2.size(); i++) {
			if (this->gameObjectList2[i] == gameObject) {
				index = i;
				break;
			}
		}
	}
	

	if (index != -1) {
		if(gameObject->getLayer() == 0) this->gameObjectList.erase(this->gameObjectList.begin() + index);
		else if(gameObject->getLayer() == 1) this->gameObjectList1.erase(this->gameObjectList1.begin() + index);
		else this->gameObjectList2.erase(this->gameObjectList2.begin() + index);
		
	}
	
	delete gameObject;
}

void GameObjectManager::deleteObjectByName(AGameObject::String name) {
	AGameObject* object = this->findObjectByName(name);
	
	if (object != NULL) {
		this->deleteObject(object);
	}
}
