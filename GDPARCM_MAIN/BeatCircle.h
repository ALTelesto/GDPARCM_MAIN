#pragma once
#include "AGameObject.h"
#include "SFML/Audio/Sound.hpp"
class BeatCircle :
    public AGameObject
{
public:
	BeatCircle(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void setSpeed(float value);
	void setHome(float x, float y);
	void setTarget(float x, float y);

	void setBeatColor(sf::Color color);
	void setColorDecay(float value);

private:
	void beat();

	float target_X = 960.0f; float target_Y = 810.0f;
	float home_X = 960.0; float home_Y = 270.0f;

	float speed = 0.33333333333333333333333333333333f;
	float progress = 1.0f;

	sf::Color beatColor = sf::Color::Cyan;
	float colorBlend = 0.0f;
	float colorDecay = 1.0f;

	bool isReturning = false;

	sf::Sound* beatSound;
};

