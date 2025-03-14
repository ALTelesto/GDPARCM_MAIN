#pragma once
#include "AGameObject.h"
class GameObjectPool;

class Thrower :
    public AGameObject
{
    typedef std::vector<sf::Texture*> Frames;
public:
    Thrower(String name);
    void initialize() override;
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;

private:
    Frames frames;

    float baseDelay = 0.3f;
    float variance = 0.2f;
    float delay;
    float tick;

    int index = 0;
};

