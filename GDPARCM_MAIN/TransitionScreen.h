#pragma once
#include "AGameObject.h"
class TransitionScreen :
    public AGameObject
{
public:
    TransitionScreen(String name);
    void initialize() override;
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;

private:
    void loadScene();

    float transitionSpeed = 0.5f;
    float downtimeSpeed = 0.2f;
    float speed = 0.5f;
    float progress = 0.f;

    bool isReturning = false;
    bool isDownTime = false;
};

