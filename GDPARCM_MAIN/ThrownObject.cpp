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
	this->setScale(0.15f, 0.15f);

	this->randomize();
}

void ThrownObject::update(sf::Time deltaTime)
{
	posY -= deltaTime.asSeconds() * speed;
	speed -= deltaTime.asSeconds() * gravity;

	angle += rSpeed;
	this->sprite->setRotation(angle);

	if(posY > BaseRunner::WINDOW_HEIGHT + 200)
	{
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

	min = -rVarianceSpeed;
	max = rVarianceSpeed;
	distributionF = std::uniform_real_distribution<float>(min, max);

	rSpeed = rBaseSpeed + distributionF(generator);

	min = -10.f;
	max = 10.f;
	distributionF = std::uniform_real_distribution<float>(min, max);

	this->angle = distributionF(generator);

	min = 0 + 100;
	max = BaseRunner::WINDOW_WIDTH - 100;
	distributionF = std::uniform_real_distribution<float>(min, max);

	this->setPosition(distributionF(generator), BaseRunner::WINDOW_HEIGHT);
}
