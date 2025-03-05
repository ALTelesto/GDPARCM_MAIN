#include "BeatCircle.h"

#include <iostream>

#include "BeatBG.h"
#include "GameObjectManager.h"
#include "SFXManager.h"
#include "TextureManager.h"

BeatCircle::BeatCircle(String name, int id) : AGameObject(name), id(id)
{

}

void BeatCircle::initialize()
{
    this->posX = target_X;
    this->posY = target_Y;

    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("circle", 0);
	
    sprite = new sf::Sprite();
    sprite->setTexture(*texture);

    this->clickThreshold = this->sprite->getTextureRect().height / 2 + 15.0f;

    sf::SoundBuffer* sound = SFXManager::getInstance()->getFromSoundMap(std::to_string(id));
    if(sound)
    {
        this->beatSound = new sf::Sound(*sound);
    }
}

void BeatCircle::processInput(sf::Event event)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (isClick) return;
        sf::Vector2i mousePosition = sf::Mouse::getPosition();
        float centerX = posX + this->clickThreshold;
        float centerY = posY + this->clickThreshold;
        float distance = std::sqrt(std::pow(mousePosition.x - centerX, 2) + std::pow(mousePosition.y - centerY, 2));

        if (distance <= clickThreshold)
        {
            this->clickBeat();
        }
        isClick = true;
    }
    else
    {
        isClick = false;
    }
}

void BeatCircle::update(sf::Time deltaTime)
{
    progress += deltaTime.asSeconds() * speed;

    if (progress >= 1.0f)
    {
        progress = 1.0f;
        beat();
    }

    if(colorBlend > 0.0f)
    {
        colorBlend -= deltaTime.asSeconds() * colorDecay;
        if (colorBlend <= 0.0f) colorBlend = 0.0f;
        sf::Color interpolatedColor = sf::Color(
            static_cast<sf::Uint8>(255 * (1.0f - colorBlend) + beatColor.r * colorBlend),
            static_cast<sf::Uint8>(255 * (1.0f - colorBlend) + beatColor.g * colorBlend),
            static_cast<sf::Uint8>(255 * (1.0f - colorBlend) + beatColor.b * colorBlend),
            static_cast<sf::Uint8>(255 * (1.0f - colorBlend) + beatColor.a * colorBlend)
        );
        sprite->setColor(interpolatedColor);
    }

    float currentX;
    float currentY;
    if (isReturning)
    {
        currentX = target_X + (home_X - target_X) * progress;
        currentY = target_Y + (home_Y - target_Y) * progress;
    }
    else
    {
        currentX = home_X + (target_X - home_X) * progress;
        currentY = home_Y + (target_Y - home_Y) * progress;
    }

    posX = currentX;
    posY = currentY;
}

void BeatCircle::setSpeed(float value)
{
    speed = value;
}

void BeatCircle::setHome(float x, float y)
{
    home_X = x;
    home_Y = y;
}

void BeatCircle::setTarget(float x, float y)
{
    target_X = x;
    target_Y = y;
}

void BeatCircle::setBeatColor(sf::Color color)
{
    this->beatColor = color;
}

void BeatCircle::setColorDecay(float value)
{
    this->colorDecay = value;
}

void BeatCircle::beat()
{
    float excess = progress - 1.0f;
	progress = 0.0f + excess;
    colorBlend = 1.0f;
	isReturning = !isReturning;
    if (this->beatSound != nullptr) this->beatSound->play();

    BeatBG* bg = dynamic_cast<BeatBG*>(GameObjectManager::getInstance()->findObjectByName("BGObject"));
    if(bg!=nullptr)
    {
        bg->setBeatColor(this->beatColor);
        bg->beat();
    }
    //std::cout << "beat!" << std::endl;
}

void BeatCircle::clickBeat()
{
    if (this->beatSound != nullptr) this->beatSound->play();

    colorBlend = 1.0f;

    BeatBG* bg = dynamic_cast<BeatBG*>(GameObjectManager::getInstance()->findObjectByName("BGObject"));
    if (bg != nullptr)
    {
        bg->setBeatColor(this->beatColor);
        bg->beat();
    }
}
