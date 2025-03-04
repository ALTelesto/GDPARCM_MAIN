#pragma once
#include "AGameObject.h"
class BeatBG :
    public AGameObject
{
public:
    BeatBG(String name);
    void initialize();
    void processInput(sf::Event event);
    void update(sf::Time deltaTime);

    void setBeatColor(sf::Color color);
    void setColorDecay(float value);

    void beat();

private:
    sf::Color beatColor = sf::Color::Cyan;
    float colorBlend = 0.0f;
    float colorDecay = 1.5f;
};

