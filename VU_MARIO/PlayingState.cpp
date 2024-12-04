#include "PlayingState.h"
#include "KeyPressStrategy.h"
#include "LimitedTimeStrategy.h"
#include "AutomaticStrategy.h"
#include "GameState.h"
#include "AssetManager.h"
#include "Collision.h"
#include "PlayingStateObserver.h"
#include "PlayableCharacterObserver.h"
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
			//call this to get type , id is id in the type
			int id = instance->getID(pixel,type);

			//create blocks, or items, or characters depends on ID
			if (type >= 1 && type <= 16) {
				all_blocks.push_back(Block::createBlock(BlockType(id), sf::Vector2f(i * 32.f, j * 32.f)));
			}

			else if (type >= 17 && type <= 20) {
				std::cout << type << " " << id;
				all_items.push_back(Item::createItem(ItemType(id), sf::Vector2f(i * 32.f, j * 32.f)));
			}

			else if (type >= 21 && type <= 24) {
				all_non_playable_characters.push_back(NonPlayableCharacter::createCharacter(NonPlayableCharacterType(id), sf::Vector2f(i * 32.f, j * 32.f)));
			}

			else if (type >= 25 && type <= 35) {
				PlayableCharacter* new_character = PlayableCharacter::createCharacter(PlayableCharacterType(id), sf::Vector2f(i * 32.f, j * 32.f));
				all_playable_characters.push_back(new_character);
				
				for (Observer* observer : observers) {
					observer->addPlayableCharacter(new_character);
				}
			}
			
		}
	}

}

void PlayingState::update(sf::RenderWindow* window ,std::vector<Observer*>& observers, const float& deltaTime){
	
	bool canPlay = false;
	bool inTime = false;

	for (PlayableCharacter* playable : all_playable_characters) {
		if (!playable->isDead()) {
			canPlay = true;
			break;
		}
	}
	
	if (this->time > 0) {
		inTime = true;
	}

	if (!canPlay || !inTime) {
		this->decreaseLives();
		return;
	}
	
	for (Block* block : all_blocks) {
		if (block->standInView(view)) {
			block->update(deltaTime, observers);
		}
	}

	for (Item* item : all_items) {
		if (item->standInView(view)) {
			item->update(deltaTime, observers);
		}
	}

	for (NonPlayableCharacter* non_playable : all_non_playable_characters) {
		if (non_playable->standInView(view)) {
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
		if (all_blocks[i]->isDead()) {
			delete all_blocks[i];
			all_blocks.erase(all_blocks.begin() + i);
		}
			
	}

	for (int i = 0; i < all_items.size(); i++) {
		if (all_items[i]->isDead()) {
			delete all_items[i];
			all_items.erase(all_items.begin() + i);
		}

	}

	for (int i = 0; i < all_playable_characters.size(); i++) {
		if (all_playable_characters[i]->isDead()) {
			delete all_playable_characters[i];
			all_playable_characters.erase(all_playable_characters.begin() + i);
		}

	}

	for (int i = 0; i < all_non_playable_characters.size(); i++) {
		if (all_non_playable_characters[i]->isDead()) {
			delete all_non_playable_characters[i];
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

	std::vector<sf::Text>attribute_text{5};
	
	attribute_text[0].setString(coins_value);
	attribute_text[1].setString(lives_value);
	attribute_text[2].setString(mapNum_value);
	attribute_text[3].setString(time_value);
	attribute_text[4].setString(score_value);

	float offsetX = 50.f;

	for (int i = 0; i < 5; i++) {
		attribute_text[i].setFillColor(sf::Color(236, 234, 226));
		attribute_text[i].setFont(font);
		attribute_text[i].setCharacterSize(40);
		attribute_text[i].setPosition(sf::Vector2f(offsetX, 30.f));

		offsetX += attribute_text[i].getGlobalBounds().width + 20.f;
	}

	view.setForAttributes(attribute_text);

	for (int i = 0; i < 5; i++) {
		window->draw(attribute_text[i]);
	}
}

PlayingState::PlayingState(){
	this->active = true;
}

PlayingState::~PlayingState(){
	this->ultimateCleanUp();
}

void PlayingState::RealExecute(sf::RenderWindow* window, std::vector<Observer*>& observers, PlayingState* gameState, const float& deltaTime, const sf::Font& font){

	if (this->isMapCreated == false) {
		this->createMap(window,observers,gameState);
		this->isMapCreated = true;
	}

	this->update(window,observers,deltaTime);
	
	this->drawMap(window,font);

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
		this->restart();
	}
	else {
		this->active = false;
	}
}

void PlayingState::restart(){
	this->time = 400;
	this->isMapCreated = false;
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




