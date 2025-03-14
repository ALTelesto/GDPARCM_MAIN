#include "TransitionScreen.h"

#include "GameObjectManager.h"
#include "LoadingScreenManager.h"
#include "TextureManager.h"

TransitionScreen::TransitionScreen(String name) : AGameObject(name)
{
}

void TransitionScreen::initialize()
{
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("whitebgLarge", 0);
	this->setScale(0.5, 0.5);
	this->sprite = new sf::Sprite;
	this->sprite->setTexture(*texture);

	speed = transitionSpeed;
}

void TransitionScreen::processInput(sf::Event event)
{
}

void TransitionScreen::update(sf::Time deltaTime)
{
	progress += speed * deltaTime.asSeconds();
	if(progress > 1.f)
	{
		progress = 0.0f;
		if(!isReturning && isDownTime)
		{
			isReturning = true;
			speed = transitionSpeed;
		}
		else if(!isDownTime)
		{
			loadScene();
			isDownTime = true;
			speed = downtimeSpeed;
		}
		else
		{
			GameObjectManager::getInstance()->deleteObject(this);
			return;
		}
	}

	if(!isReturning && !isDownTime)
	{
		this->sprite->setColor(sf::Color(
		255, 255, 255,
		255 * progress));
	}
	else if (isReturning)
	{
		this->sprite->setColor(sf::Color(
			255, 255, 255,
			255 - 255 * progress));
	}
	
}

void TransitionScreen::loadScene()
{
	LoadingScreenManager::getInstance()->loadScene();
}
