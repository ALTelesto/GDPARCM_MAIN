#pragma once
#include "AGameObject.h"
class LoadingBar :
    public AGameObject
{
public:
    LoadingBar(String name);
    void initialize() override;
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;
};

