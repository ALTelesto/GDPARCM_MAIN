#include "MusicPlayer.h"

#include "SFXManager.h"

MusicPlayer::MusicPlayer(String name) : AGameObject(name)
{
}

void MusicPlayer::initialize()
{
	//sf::SoundBuffer source0 = SFXManager::getInstance()->getFromSoundMap()

	this->sound = new sf::Sound();
}

void MusicPlayer::processInput(sf::Event event)
{
}

void MusicPlayer::update(sf::Time deltaTime)
{
}
