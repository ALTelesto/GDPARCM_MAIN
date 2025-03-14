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

    float rBaseSpeed = 0.f;
    float rVarianceSpeed = 1.15f;
    float rSpeed;
    float angle = 0.f;

    int index = -1;
};

