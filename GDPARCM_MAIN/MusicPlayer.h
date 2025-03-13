#pragma once
#include <SFML/Audio/Sound.hpp>

#include "AGameObject.h"
class MusicPlayer :
    public AGameObject
{
public:
    MusicPlayer(String name);
    void initialize() override;
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;

private:
    std::vector<sf::SoundBuffer> source;
    sf::Sound* sound;
};

