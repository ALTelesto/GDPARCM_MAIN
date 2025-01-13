#pragma once
#include "AGameObject.h"
class FPSCounter :    public AGameObject
{
	public:
		FPSCounter();
		~FPSCounter();
		void initialize() override;
		void processInput(sf::Event event) override;
		void update(sf::Time deltaTime) override;
		void draw(sf::RenderWindow* targetWindow) override;
	
	private:
		sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
		sf::Time updateTime;
		sf::Text* statsText;
		int framesPassed = 0;

		void updateFPS(sf::Time elapsedTime);
		
};

