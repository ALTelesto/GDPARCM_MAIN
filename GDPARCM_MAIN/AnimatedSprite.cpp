#include "AnimatedSprite.h"

#include "TextureManager.h"

#include <random>

AnimatedSprite::AnimatedSprite(String name) : AGameObject(name)
{
}

void AnimatedSprite::initialize()
{
	this->sprite = new sf::Sprite();
}

void AnimatedSprite::update(sf::Time deltaTime)
{
	if (index == -1) nextFrame();

	tick += deltaTime.asSeconds();
	if(tick >= frameTime)
	{
		tick = tick - frameTime;
		this->nextFrame();
	}
}

void AnimatedSprite::processInput(sf::Event event)
{
}

void AnimatedSprite::setFrames(std::vector<String> frames)
{
	for(String textureName : frames)
	{
		sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(textureName, 0);
		if (texture == nullptr) return;
		this->frames.push_back(texture);
	}
	if(this->frames.size() >= 1)
	{
		index = 0;
	}
}

void AnimatedSprite::nextFrame()
{
	if (frames.empty()) return;

	index++;
	if(index > this->frames.size()-1)
	{
		index = 0;
	}
	this->sprite->setTexture(*frames[index]);

	float min = -variance;
	float max = variance;

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distributionF(min, max);
	this->frameTime = baseTime + distributionF(generator);
}
