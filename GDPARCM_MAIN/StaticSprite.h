#pragma once
#include "AGameObject.h"
class StaticSprite :
    public AGameObject
{
public:
    StaticSprite(String name);
    StaticSprite(String name, String textureName);
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;
    void initialize() override;

    void setColor(sf::Color color);

    void setTexture(String textureName);
};

