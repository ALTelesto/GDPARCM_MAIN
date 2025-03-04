#include "BeatBG.h"

#include "TextureManager.h"

BeatBG::BeatBG(String name): AGameObject(name)
{
}

void BeatBG::initialize()
{
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("gradient", 0);

	sprite = new sf::Sprite();
	sprite->setTexture(*texture);
}

void BeatBG::processInput(sf::Event event)
{
}

void BeatBG::update(sf::Time deltaTime)
{
    if (colorBlend > 0.0f)
    {
        colorBlend -= deltaTime.asSeconds() * colorDecay;
        if (colorBlend <= 0.0f) colorBlend = 0.0f;
        sf::Color interpolatedColor = sf::Color(
        beatColor.r,
        beatColor.g,
        beatColor.b,
        255 - 255 * (1.0f - colorBlend)
        );
        sprite->setColor(interpolatedColor);
    }
}

void BeatBG::setBeatColor(sf::Color color)
{
	this->beatColor = color;
}

void BeatBG::setColorDecay(float value)
{
	this->colorDecay = value;
}

void BeatBG::beat()
{
    this->colorBlend = 1.0f;
}
