#include "ThrownObject.h"

#include <random>

#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "LoadingScreenManager.h"
#include "TextureManager.h"

ThrownObject::ThrownObject(String name, sf::Texture texture) : AGameObject(name), texture(texture)
{
}

void ThrownObject::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(this->texture);
	this->setScale(1, 1);

	this->randomize();
}

void ThrownObject::update(sf::Time deltaTime)
{
	posY -= deltaTime.asSeconds() * speed;
	speed -= deltaTime.asSeconds() * gravity;

	if(posY > BaseRunner::WINDOW_HEIGHT + 200)
	{
		std::cout << "boom" << std::endl;
		LoadingScreenManager::getInstance()->removeObject();
		GameObjectManager::getInstance()->deleteObject(this);
	}
}

void ThrownObject::processInput(sf::Event event)
{
}

void ThrownObject::setTexture(sf::Texture texture)
{
	if (this->sprite == nullptr) this->sprite = new sf::Sprite(texture);
	else this->sprite->setTexture(texture);
}

void ThrownObject::randomize()
{
	float min = -varianceSpeed;
	float max = varianceSpeed;

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distributionF(min, max);

	speed = baseSpeed + distributionF(generator);

	min = -45.f;
	max = 45.f;
	distributionF = std::uniform_real_distribution<float>(min, max);

	this->sprite->setRotation(distributionF(generator));

	min = 0 + 100;
	max = BaseRunner::WINDOW_WIDTH - 100;
	distributionF = std::uniform_real_distribution<float>(min, max);

	this->setPosition(distributionF(generator), BaseRunner::WINDOW_HEIGHT);
}
