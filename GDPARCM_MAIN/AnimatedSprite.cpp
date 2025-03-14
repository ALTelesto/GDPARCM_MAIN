#include "AnimatedSprite.h"

#include "TextureManager.h"

#include <random>

AnimatedSprite::AnimatedSprite(String name) : AGameObject(name)
{
}

void AnimatedSprite::initialize()
{
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

void AnimatedSprite::draw(sf::RenderWindow* targetWindow)
{
	if (!this->frameList.empty()) {
		this->frameList[index]->setPosition(this->posX, this->posY);
		this->frameList[index]->setScale(this->scaleX, this->scaleY);
		targetWindow->draw(*this->frameList[index]);
	}
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
		this->frameList.clear();
		for(int i = 0; i < this->frames.size(); i++)
		{
			sf::Sprite* sprite = new sf::Sprite;
			sprite->setTexture(*this->frames[i]);
			this->frameList.push_back(sprite);
		}
		index = 0;
	}
}

void AnimatedSprite::nextFrame()
{
	if (frames.empty()) return;

	std::random_device rd;
	std::mt19937 generator(rd());

	if (!reverse) {
		index++;
		if (index > this->frames.size() - 1)
		{
			index = 0;
			std::uniform_int_distribution<int> distribution(0, 1);
			if (distribution(generator) > 0) this->reverse = !this->reverse;
		}
	}
	else
	{
		index--;
		if (index < 0)
		{
			index = this->frames.size() - 1;
			std::uniform_int_distribution<int> distribution(0, 1);
			if (distribution(generator) > 0) this->reverse = !this->reverse;
		}
	}
	
	//this->sprite->setTexture(*frames[index]);

	float min = -variance;
	float max = variance;

	
	std::uniform_real_distribution<float> distributionF(min, max);
	this->frameTime = baseTime + distributionF(generator);
}
