#include "LoadingBar.h"

#include "GameObjectManager.h"
#include "LoadingScreenManager.h"
#include "TextureManager.h"

LoadingBar::LoadingBar(String name) : AGameObject(name)
{
}

void LoadingBar::initialize()
{
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("beatline", 0);
	if (texture == nullptr) {
		delete this;
		return;
	}
	this->sprite->setTexture(*texture);
}

void LoadingBar::processInput(sf::Event event)
{
}

void LoadingBar::update(sf::Time deltaTime)
{
	if (LoadingScreenManager::getInstance()->isDone()) GameObjectManager::getInstance()->deleteObject(this);
	this->sprite->setColor(sf::Color(255, 255, 255, 255 * LoadingScreenManager::getInstance()->getProgress()));
}
