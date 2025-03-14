#include "MusicPlayer.h"

#include "SFXManager.h"

MusicPlayer::MusicPlayer(String name) : AGameObject(name)
{
}

void MusicPlayer::initialize()
{
	sf::SoundBuffer* source0 = SFXManager::getInstance()->getFromSoundMap("music0");
	sf::SoundBuffer* source1 = SFXManager::getInstance()->getFromSoundMap("music1");
	sf::SoundBuffer* source2 = SFXManager::getInstance()->getFromSoundMap("music2");
	sf::SoundBuffer* source3 = SFXManager::getInstance()->getFromSoundMap("music3");

	this->source.push_back(source0);
	this->source.push_back(source2);
	this->source.push_back(source3);
	this->source.push_back(source1);

	this->sound = new sf::Sound();
	this->sound->setLoop(true);
	this->sound->setBuffer(*source0);
	this->sound->play();
	this->sound->setVolume(40);
}

void MusicPlayer::processInput(sf::Event event)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !pressed)
	{
		pressed = true;

		this->sound->stop();
		index++;
		if (index > source.size() - 1) index = 0;
		this->sound->setBuffer(*this->source[index]);
		this->sound->setVolume(40);

		this->sound->play();
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && pressed)
	{
		pressed = false;
	}
}

void MusicPlayer::update(sf::Time deltaTime)
{
}
