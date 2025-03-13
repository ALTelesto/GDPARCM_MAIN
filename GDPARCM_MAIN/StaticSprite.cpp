#include "StaticSprite.h"

#include "TextureManager.h"

StaticSprite::StaticSprite(String name) : AGameObject(name)
{
}

StaticSprite::StaticSprite(String name, String textureName) : AGameObject(name)
{
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(textureName, 0);
	if (texture == nullptr) return;
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*texture);
}

void StaticSprite::processInput(sf::Event event)
{
}

void StaticSprite::update(sf::Time deltaTime)
{
}

void StaticSprite::initialize()
{
	if(this->sprite == nullptr) this->sprite = new sf::Sprite();
}

void StaticSprite::setColor(sf::Color color)
{
	this->sprite->setColor(color);
}

void StaticSprite::setTexture(String textureName)
{
	if (this->sprite == nullptr) this->sprite = new sf::Sprite();

	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(textureName, 0);
	if (texture == nullptr) return;

	this->sprite->setTexture(*texture);
}
