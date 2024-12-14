#include "PlayingState.h"
#include "KeyPressStrategy.h"
#include "LimitedTimeStrategy.h"
#include "AutomaticStrategy.h"
#include "GameState.h"
#include "AssetManager.h"
#include "Collision.h"
#include "PlayingStateObserver.h"
#include "PlayableCharacterObserver.h"
#include "View.h"
#include <vector>

void PlayingState::createMap(sf::RenderWindow* window, std::vector<Observer*>& observers, PlayingState* gameState){
	
	this->cleanObserverForEachLive(observers);

	AssetManager* instance = AssetManager::getInstance();
	
	observers.push_back(new PlayingStateObserver);
	observers.push_back(new PlayableCharacterObserver);
	
	for (Observer* observer : observers) {
		observer->addPlayingState(gameState);
	}

	view = View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));

	std::string mapFile = instance->getMapFile(this->mapNum);

	sf::Image readMap;
	if (!readMap.loadFromFile(mapFile)) {
		std::cout << "Cannot read file " + mapFile;
		exit(1);
	}

	unsigned int width = readMap.getSize().x;
	unsigned int height = readMap.getSize().y;
	
	for (unsigned int j = 0; j < height; j++) {
		for (unsigned int i = 0; i < width; i++) {
			sf::Color pixel = readMap.getPixel(i, j);

			int type = 0;
			
			int id = instance->getID(pixel,type);

			
			if (type >= 1 && type <= 39) {
				all_blocks.push_back(Block::createBlock(BlockType(id), sf::Vector2f(i * 32.f, j * 32.f)));
			}

			else if (type >= 40 && type <= 43) {
				all_items.push_back(Item::createItem(ItemType(id), sf::Vector2f(i * 32.f, j * 32.f)));
			}

			else if (type >= 44 && type <= 48) {
				all_non_playable_characters.push_back(NonPlayableCharacter::createCharacter(NonPlayableCharacterType(id), sf::Vector2f(i * 32.f, j * 32.f),this->mapNum));
			}

			else if (type >= 49 && type <= 59) {
				PlayableCharacter* new_character = PlayableCharacter::createCharacter(this->m_mainCharacterType, sf::Vector2f(i * 32.f, j * 32.f));
				all_playable_characters.push_back(new_character);
				for (Observer* observer : observers) {
					observer->addPlayableCharacter(new_character);
				}
			}			
		}	
	}

}

void PlayingState::update(sf::RenderWindow* window ,std::vector<Observer*>& observers, const float& deltaTime){
	
	/*bool canPlay = false;
	bool inTime = false;

	for (PlayableCharacter* playable : all_playable_characters) {
		if (playable->standInView(view)) {
			canPlay = true;
			break;
		}
		else {

		}
	}
	
	if (this->time > 0) {
		inTime = true;
	}

	if (canPlay == false || inTime == false) {
		this->decreaseLives();
		return;
	}*/
	
	for (Block* block : all_blocks) {
		if (block != nullptr && block->canInteract() == true && block->standInView(view) == true) {
			block->update(deltaTime, observers);
		}
	}

	for (Item* item : all_items) {
		if (item != nullptr && item->standInView(view) == true) {
			item->update(deltaTime, observers);
		}
	}

	for (NonPlayableCharacter* non_playable : all_non_playable_characters) {
		if (non_playable != nullptr && non_playable->standInView(view) == true) {
			non_playable->update(deltaTime, observers);
		}
	}	
	
	for (PlayableCharacter* playable : all_playable_characters) {
		playable->update(deltaTime,observers);
	}
	
	collision.handleAllCollision(this->all_playable_characters, this->all_non_playable_characters, this->all_items, this->all_blocks, deltaTime, observers, this->view);

	view.update(all_playable_characters, window);
}

void PlayingState::drawMap(sf::RenderWindow* window, const sf::Font& font){
	
	this->drawAttributes(window, font);

	for (Block* block : this->all_blocks) {
		if (block && block->standInView(view)) {
			block->draw(window);
		}
	}

	for (Item* item : this->all_items) {
		if (item && item->standInView(view)) {
			item->draw(window);
		}
	}

	for (NonPlayableCharacter* non_playable : this->all_non_playable_characters) {
		if (non_playable && non_playable->standInView(view)) {
			non_playable->draw(window);
		}
	}

	for (PlayableCharacter* playable : this->all_playable_characters) {
		if (playable) {
			playable->draw(window);
		}
	}

	view.setForWindow(window);
}

void PlayingState::temporaryCleanUp(){
	for (int i = 0; i < all_blocks.size(); i++) {
		if (all_blocks[i]->canBeDeleted() == true) {
			delete all_blocks[i];
			all_blocks[i] = nullptr;
			all_blocks.erase(all_blocks.begin() + i);
		}
			
	}

	for (int i = 0; i < all_items.size(); i++) {
		if (all_items[i]->canBeDeleted() == true) {
			delete all_items[i];
			all_items[i] = nullptr;
			all_items.erase(all_items.begin() + i);
		}

	}

	for (int i = 0; i < all_non_playable_characters.size(); i++) {
		if (all_non_playable_characters[i]->canBeDeleted() == true) {
			delete all_non_playable_characters[i];
			all_non_playable_characters[i] = nullptr;
			all_non_playable_characters.erase(all_non_playable_characters.begin() + i);
		}
	}
}

void PlayingState::ultimateCleanUp(){
	for (PlayableCharacter* character : all_playable_characters) {
		delete character;
		character = nullptr;
	}

	for (NonPlayableCharacter* character : all_non_playable_characters) {
		delete character;
		character = nullptr;
	}

	for (Block* block : all_blocks) {
		delete block;
		block = nullptr;
	}

	for (Item* item : all_items) {
		delete item;
		item = nullptr;
	}

	all_playable_characters.clear();
	all_non_playable_characters.clear();
	all_blocks.clear();
	all_items.clear();
}

void PlayingState::cleanObserverForEachLive(std::vector<Observer*>& observers){
	for (Observer* observer : observers) {
		delete observer;
		observer = nullptr;
	}
	observers.clear();
}

void PlayingState::drawAttributes(sf::RenderWindow* window, const sf::Font& font){
	std::string coins_value = "COIN: " + std::to_string(coin);
	std::string lives_value = "LIVES: " + std::to_string(lives);
	std::string mapNum_value = "";
	std::string time_value = "TIME: " + std::to_string((int)time);
	std::string score_value = "SCORE: " + std::to_string(score);

	switch (mapNum) {
	case 1:
		mapNum_value = "WORLD 1-1";
		break;
	case 2:
		mapNum_value = "WORLD 1-2";
		break;
	case 3:
		mapNum_value = "WORLD 1-3";
		break;
	default:
		break;
	}

	int size = this->m_attributes_text.size();

	float offsetX = 20.f;
	
	std::vector<std::string>temp = { coins_value,lives_value,mapNum_value,time_value,score_value };
	
	setAttributes<sf::Text>(this->m_attributes_text, temp, std::vector<sf::Color>(size, sf::Color(236, 234, 226)), font, {}, {}, {}, std::vector<int>(size, 40), {});
	
	for (int i = 0; i < 5; i++) {

		this->m_attributes_text[i].setPosition(offsetX, 30.f);

		offsetX += this->m_attributes_text[i].getGlobalBounds().width + 20.f;
	}


	view.setForAttributes(this->m_attributes_text);

	draw<sf::Text>(window, this->m_attributes_text);
}

PlayingState::PlayingState(){
	this->active = true;
	this->mapNum = 1;
	this->m_mainCharacterType = PlayableCharacterType::small_mario;
	this->m_attributes_text = std::vector<sf::Text>(5);
}

PlayingState::PlayingState(const std::pair<int, PlayableCharacterType>& mapAndMainCharacter){
	this->active = true;
	this->mapNum = mapAndMainCharacter.first;
	this->m_mainCharacterType = mapAndMainCharacter.second;
}

PlayingState::~PlayingState(){
	this->ultimateCleanUp();
}

void PlayingState::RealExecute(sf::RenderWindow* window, std::vector<Observer*>& observers, PlayingState* gameState, const float& deltaTime, const sf::Font& font){
	if(time == 400) this->createMap(window, observers, gameState);

	this->update(window, observers, deltaTime);
	
	this->drawMap(window, font);
	
	this->temporaryCleanUp();
	
}

void PlayingState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){
	srand(NULL);
	
	this->RealExecute(window, observers, (PlayingState*)gameState, deltaTime,font);

	this->time -= deltaTime;
}

void PlayingState::addCoin(){
	this->coin++;
}

void PlayingState::addScore(int score){
	this->score += score;
}

void PlayingState::decreaseLives(){
	this->lives--;
	
	if (lives <= 0) {
		this->active = false;
		return;
	}

	this->restart();
}

void PlayingState::changeMap(){
	
	if (mapNum < 3) {
		mapNum++;
		this->expiredTimeOfChangingMap = 2;
		this->restart();
	}

	else {
		this->expiredTimeOfCongratulation = 2;
	}
}

void PlayingState::restart(){
	this->time = 400;
	sf::sleep(sf::seconds(2));
	this->isCreated = false;
	this->ultimateCleanUp();
}

bool PlayingState::isActive()
{
	return this->active;
}

void PlayingState::hitBonusBrick(const sf::Vector2f& position, ItemType type) {

	this->all_blocks.push_back(Block::createBlock(BlockType::basebrick,position));

	this->all_items.push_back(Item::createItem(type,sf::Vector2f(position.x + 5.f,position.y - 30.f)));
}

GameState* PlayingState::nextState(){
	return nullptr;
}

void PlayingState::drawState(sf::RenderWindow* window){

}

void PlayingState::handleInputEvent(const sf::Event*& ev, const sf::Font& font){

}

void PlayingState::bossShootingEvent(const sf::Vector2f& position, const float& speed){
	NonPlayableCharacter* new_bullet = NonPlayableCharacter::createCharacter(NonPlayableCharacterType::bullet, position, this->mapNum);

	if(speed < 0) this->all_non_playable_characters[this->all_non_playable_characters.size() - 1]->changeDirection();

	this->all_non_playable_characters.push_back(new_bullet);
}

void PlayingState::mainShootingEvent(const sf::Vector2f& position, const float& speed){

}




