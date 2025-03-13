#include "LoadingDoneText.h"

#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "LoadingScreenManager.h"

LoadingDoneText::LoadingDoneText(String name) : AGameObject(name)
{
}

LoadingDoneText::~LoadingDoneText()
{
	delete this->text->getFont();
	delete this->text;
	AGameObject::~AGameObject();
}

void LoadingDoneText::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->text = new sf::Text();
	this->text->setFont(*font);

	this->text->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->text->setOutlineThickness(2.5f);
	this->text->setCharacterSize(26);

	float x = BaseRunner::WINDOW_WIDTH - BaseRunner::WINDOW_WIDTH / 2 - 165;
	float y = BaseRunner::WINDOW_HEIGHT - 70;

	this->text->setPosition(x, x);

	this->text->setString("Press ENTER to continue");
}

void LoadingDoneText::processInput(sf::Event event)
{
	if(LoadingScreenManager::getInstance()->isDone() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		GameObjectManager::getInstance()->deleteObject(this);
	}
}

void LoadingDoneText::update(sf::Time deltaTime)
{
}

void LoadingDoneText::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->text != nullptr && LoadingScreenManager::getInstance()->isDone())
		targetWindow->draw(*this->text);
}
