#include "IconObject.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"

IconObject::IconObject(String name, int textureIndex): AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void IconObject::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	//TextureManager::getInstance()->loadSingleStreamAsset(this->textureIndex);
	sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(this->textureIndex);
	if(texture == nullptr)
	{
		return;
	}
	this->sprite->setTexture(*texture);
}

void IconObject::processInput(sf::Event event)
{
}

void IconObject::update(sf::Time deltaTime)
{
}
