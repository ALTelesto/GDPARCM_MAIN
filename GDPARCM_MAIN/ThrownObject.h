#pragma once
#include "AGameObject.h"

class ThrownObject :
    public AGameObject
{
public:
    ThrownObject(String name, sf::Texture texture);
    void initialize() override;
    void update(sf::Time deltaTime) override;
    void processInput(sf::Event event) override;

    void setTexture(sf::Texture texture);

private:
    sf::Texture texture;
    void randomize();

    float baseSpeed = 700;
    float varianceSpeed = 200;
    float speed;
    float gravity = 450;

    int index = -1;
};

