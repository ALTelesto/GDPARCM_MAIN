#include "Thrower.h"

#include <iostream>

#include "ThrownObject.h"
#include "GameObjectPool.h"

#include <random>

#include "GameObjectManager.h"
#include "LoadingScreenManager.h"
#include "TextureManager.h"

Thrower::Thrower(String name) : AGameObject(name)
{
}

void Thrower::initialize()
{
	std::vector<String> frames = {"circle","circle"};

	for (String textureName : frames)
	{
		sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(textureName, 0);
		if (texture == nullptr) return;
		this->frames.push_back(texture);
	}
	std::cout << "frame size thrower is " << this->frames.size() << std::endl;
}

void Thrower::processInput(sf::Event event)
{
}

void Thrower::update(sf::Time deltaTime)
{
	tick += deltaTime.asSeconds();
	if(tick >= delay)
	{
		if (LoadingScreenManager::getInstance()->getObjectNum() >= 12) return;
		std::cout << "throw!" << std::endl;

		tick = 0;

		float min = -variance;
		float max = variance;

		std::random_device rd;
		std::mt19937 generator(rd());
		std::uniform_real_distribution<float> distributionF(min, max);
		delay = baseDelay + distributionF(generator);

		std::uniform_int_distribution<int> distribution(0, this->frames.size() - 1);
		ThrownObject* object = new ThrownObject("throwobject" + std::to_string(index),*this->frames[distribution(generator)]);
		GameObjectManager::getInstance()->addObject(object);

		LoadingScreenManager::getInstance()->addObject();

		index++;
	}
}
