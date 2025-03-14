#pragma once
#include "AGameObject.h"
class AnimatedSprite :
    public AGameObject
{
    typedef std::vector<sf::Texture*> Frames;

public:
    AnimatedSprite(String name);
    void initialize() override;
    void update(sf::Time deltaTime) override;
    void processInput(sf::Event event) override;
    void draw(sf::RenderWindow* targetWindow) override;

    void setFrames(std::vector<String> frames);

private:
    void nextFrame();

	Frames frames;
    std::vector<sf::Sprite*> frameList;

    int index = -1;
    float baseTime = 0.33f;
    float variance = 0.01f;
    float frameTime = 0.33f;
    float tick = 0.0f;

    bool reverse = false;
};

