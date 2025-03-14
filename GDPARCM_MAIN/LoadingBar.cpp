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
	//for debugging
	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		LoadingScreenManager::getInstance()->setProgress(1);
	}*/
}

void LoadingBar::update(sf::Time deltaTime)
{
	if (LoadingScreenManager::getInstance()->isDone())
	{
		GameObjectManager::getInstance()->deleteObject(this);
		return;
	}
	this->sprite->setColor(sf::Color(255 * LoadingScreenManager::getInstance()->getProgress(), 255 * LoadingScreenManager::getInstance()->getProgress(), 255 * LoadingScreenManager::getInstance()->getProgress(), 255 * LoadingScreenManager::getInstance()->getProgress()));
}
