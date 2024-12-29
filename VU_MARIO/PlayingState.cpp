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
#include "FireMario.h"
#include "SuperMario.h"
#include "BigMario.h"
#include "Mario.h"
#include "Bullet.h"
#include "MenuState.h"
#include "GoodBullet.h"
#include "GameOverState.h"
#include "CongratulationState.h"
#include "ChangingMapState.h"

void PlayingState::createMap(sf::RenderWindow* window, std::vector<Observer*>& observers, PlayingState* gameState){
	this->cleanObserverForEachLive(observers);
	
	this->m_restart_called = false;
	AssetManager* instance = AssetManager::getInstance();
	
	Observer* observer1 = new PlayingStateObserver;
	Observer* observer2 = new PlayableCharacterObserver;

	observers.push_back(observer1);
	observers.push_back(observer2);
	
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

	this->isCreated = true;
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
	
	int blockSize = all_blocks.size();
	int itemSize = all_items.size();
	int nonPlayableSize = all_non_playable_characters.size();
	int playableSize = all_playable_characters.size();
	
	for (int i = 0; i < blockSize; i++) {
		

		if (all_blocks[i] != nullptr && all_blocks[i]->canInteract() == true) {
			all_blocks[i]->update(deltaTime, observers);
		}
	}

	for (int i = 0; i < itemSize; i++) {
		

		if (all_items[i] != nullptr) {
			all_items[i]->update(deltaTime, observers);
		}
	}

	for (int i = 0; i < nonPlayableSize; i++) {
		if (all_non_playable_characters[i] != nullptr) {
			all_non_playable_characters[i]->update(deltaTime, observers);
		}
	}


	for (int i = 0; i < playableSize; i++) {
		PlayableCharacter* playable = all_playable_characters[i];

		if (playable != nullptr) {
			playable->update(deltaTime, observers);
		}
	}
	
	collision.handleAllCollision(std::vector<PlayableCharacter*>(this->all_playable_characters.begin(),this->all_playable_characters.begin() + playableSize), std::vector<NonPlayableCharacter*>(this->all_non_playable_characters.begin(), this->all_non_playable_characters.begin() + nonPlayableSize), std::vector<Item*>(this->all_items.begin(), this->all_items.begin() + itemSize), std::vector<Block*>(this->all_blocks.begin(), this->all_blocks.begin() + blockSize), deltaTime, observers, this->view);
	
	if(this->m_restart_called == false) view.update(std::vector<PlayableCharacter*>(this->all_playable_characters.begin(), this->all_playable_characters.begin() + playableSize), window);
}

void PlayingState::drawMap(sf::RenderWindow* window, const sf::Font& font){
	for (Block* block : this->all_blocks) {
		if (block != nullptr) {
			block->draw(window);
		}
	}

	for (Item* item : this->all_items) {
		if (item != nullptr) {
			item->draw(window);
		}
	}

	for (NonPlayableCharacter* non_playable : this->all_non_playable_characters) {
		if (non_playable != nullptr) {
			non_playable->draw(window);
		}
	}

	for (PlayableCharacter* playable : this->all_playable_characters) {
		if (playable != nullptr) {
			playable->draw(window);
		}
	}

	this->drawAttributes(window, font);
	
	view.setForWindow(window);
}

void PlayingState::temporaryCleanUp(sf::RenderWindow* window, const sf::Font& font){
	for (int i = 0; i < all_blocks.size(); i++) {
		if (all_blocks[i] == nullptr) continue;

		if (all_blocks[i]->canBeDeleted() == true || (all_blocks[i]->standInView(this->view) == false && all_blocks[i]->canBeDeletedWhenOutOfView() == true)) {
			delete all_blocks[i];
			all_blocks[i] = nullptr;
			all_blocks.erase(all_blocks.begin() + i);
		}
			
	}

	for (int i = 0; i < all_items.size(); i++) {
		if (all_items[i]->canBeDeleted() == true || (all_items[i]->standInView(this->view) == false && all_items[i]->canBeDeletedWhenOutOfView() == true)) {
			delete all_items[i];
			all_items[i] = nullptr;
			all_items.erase(all_items.begin() + i);
		}

	}

	for (int i = 0; i < this->all_non_playable_characters.size(); i++) {
		if ((all_non_playable_characters[i]->canBeDeleted() == true) || (all_non_playable_characters[i]->standInView(this->view) == false && all_non_playable_characters[i]->canBeDeletedWhenOutOfView() == true)) {
			delete all_non_playable_characters[i];
			all_non_playable_characters[i] = nullptr;
			all_non_playable_characters.erase(all_non_playable_characters.begin() + i);
		}
	}

	for (int i = 0; i < this->all_playable_characters.size(); i++) {
		if ((all_playable_characters[i]->canBeDeleted() == true)) {
			delete all_playable_characters[i];
			all_playable_characters[i] = nullptr;
			all_playable_characters.erase(all_playable_characters.begin() + i);
		}
	}

	for (int i = 0; i < this->garbage_of_playable_characters.size(); i++) {
		delete this->garbage_of_playable_characters[i];
		this->garbage_of_playable_characters[i] = nullptr;
		this->garbage_of_playable_characters.erase(this->garbage_of_playable_characters.begin() + i);	
	}

	for (int i = 0; i < this->garbage_of_non_playable_characters.size(); i++) {

		delete this->garbage_of_non_playable_characters[i];
		this->garbage_of_non_playable_characters[i] = nullptr;
		this->garbage_of_non_playable_characters.erase(this->garbage_of_non_playable_characters.begin() + i);
	}

	for (int i = 0; i < this->garbage_of_all_blocks.size(); i++) {

		delete this->garbage_of_all_blocks[i];
		this->garbage_of_all_blocks[i] = nullptr;
		this->garbage_of_all_blocks.erase(this->garbage_of_all_blocks.begin() + i);
	}

	for (int i = 0; i < this->garbage_of_all_items.size(); i++) {

		delete this->garbage_of_all_items[i];
		this->garbage_of_all_items[i] = nullptr;
		this->garbage_of_all_items.erase(this->garbage_of_all_items.begin() + i);
	}

	if (this->all_playable_characters.empty()) {
		this->decreaseLives(window,font);
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

	for (PlayableCharacter* garbage : garbage_of_playable_characters) {
		delete garbage;
		garbage = nullptr;
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
	
	//for (int i = 0; i < 0; i++) { // 5

	//	this->m_attributes_text[i].setPosition(offsetX, 30.f);

	//	offsetX += this->m_attributes_text[i].getGlobalBounds().width + 20.f;
	//}

	for (auto& motherfuck : this->m_attributes_text)
	{
		motherfuck.setPosition(offsetX, 30);
		offsetX += motherfuck.getGlobalBounds().width + 20;
	}


	view.setForAttributes(this->m_attributes_text);

	draw<sf::Text>(window, this->m_attributes_text);
}

PlayingState::PlayingState(){
	this->active = true;
	this->isCreated = false;
	this->m_attributes_text = std::vector<sf::Text>(5);
}

PlayingState::PlayingState(const std::pair<int, PlayableCharacterType>& mapAndMainCharacter) : PlayingState(){
	this->mapNum = mapAndMainCharacter.first;
	this->m_mainCharacterType = mapAndMainCharacter.second;
}

PlayingState::PlayingState(const int& coin, const int& live, const int& mapNum, const int& score, const PlayableCharacterType main){
	this->coin = coin;
	this->lives = live;
	this->mapNum = mapNum;
	this->score = score;
	this->m_mainCharacterType = main;
	this->m_attributes_text = std::vector<sf::Text>(5);
}

PlayingState::~PlayingState(){
	this->ultimateCleanUp();
}

void PlayingState::RealExecute(sf::RenderWindow* window, std::vector<Observer*>& observers, PlayingState* gameState, const float& deltaTime, const sf::Font& font){
	if (this->isCreated == false) this->createMap(window, observers, gameState);

	
	if (this->mapNum == 2 || this->mapNum == 3) {
		window->clear(sf::Color::Black);
	}

	this->update(window, observers, deltaTime);
	
	this->drawMap(window, font);
	
	this->temporaryCleanUp(window,font);
	
}

void PlayingState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){
	srand(NULL);
	
	this->RealExecute(window, observers, (PlayingState*)gameState, deltaTime,font);

	this->time -= deltaTime;

	if(this->m_changing_called == true) this->m_nextState = new ChangingMapState(m_mainCharacterType,font, score, coin, mapNum, time, lives);
	if (this->m_congrat_called == true) this->m_nextState = new CongratulationState(window);
}

void PlayingState::addCoin(){
	this->coin++;
}

void PlayingState::addScore(int score){
	this->score += score;
}

void PlayingState::decreaseLives(sf::RenderWindow* window,const sf::Font &font){
	this->lives--;
	
	if (this->lives <= 0) {
		this->active = false;
		this->m_nextState = new GameOverState(window);
		return;
	}

	this->restart();
}

void PlayingState::changeMap(){
	this->active = false;
	sf::sleep(sf::seconds(0.2));
	
	if (mapNum < 3) {
		this->mapNum++;
		this->restart();
		this->m_changing_called = true;
	}

	else {
		this->m_congrat_called = true;
	}
}

void PlayingState::restart(){
	this->time = 400.f;
	sf::sleep(sf::seconds(2));
	this->isCreated = false;
	
	for (Block* block : this->all_blocks) {
		if (block != nullptr && block->standInView(view)) {
			this->garbage_of_all_blocks.push_back(block);
		}
	}

	for (Item* item : this->all_items) {
		if (item != nullptr && item->standInView(view)) {
			this->garbage_of_all_items.push_back(item);
		}
	}

	for (NonPlayableCharacter* non_playable : this->all_non_playable_characters) {
		if (non_playable != nullptr && non_playable->standInView(view)) {
			this->garbage_of_non_playable_characters.push_back(non_playable);
		}
	}

	for (PlayableCharacter* playable : this->all_playable_characters) {
		if (playable != nullptr) {
			this->garbage_of_playable_characters.push_back(playable);
		}
	}

	this->all_blocks.clear();
	this->all_items.clear();
	this->all_playable_characters.clear();
	this->all_non_playable_characters.clear();
	this->m_restart_called = true;
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
	return m_nextState;
}

void PlayingState::drawState(sf::RenderWindow* window){

}

void PlayingState::handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window){

}

void PlayingState::bossShootingEvent(const sf::Vector2f& position, const float& speed){
	NonPlayableCharacter* new_bullet = NonPlayableCharacter::createCharacter(NonPlayableCharacterType::bullet, sf::Vector2f(position.x + 5.f,position.y + 5.f), this->mapNum);
	
	if(new_bullet != nullptr && speed < 0) new_bullet->changeDirection();

	if(new_bullet != nullptr) this->all_non_playable_characters.push_back(new_bullet);
}

void PlayingState::mainShootingEvent(const sf::Vector2f& position, const float& speed){
	PlayableCharacter* new_good_bullet = PlayableCharacter::createCharacter(PlayableCharacterType::good_bullet, position);

	if (new_good_bullet != nullptr && speed < 0) new_good_bullet->changeDirection();

	if (new_good_bullet != nullptr) this->all_playable_characters.push_back(new_good_bullet);
}

void PlayingState::mainCollectingFlowerEvent(PlayableCharacter* character){
	
	PlayableCharacter* temp = all_playable_characters[0];
	all_playable_characters[0] = new FireMario(temp);
		
	garbage_of_playable_characters.push_back(temp);
	
}

void PlayingState::mainCollectingMushroomEvent(PlayableCharacter* character){
	
	PlayableCharacter* temp = all_playable_characters[0];
	all_playable_characters[0] = new BigMario(temp);
		
	garbage_of_playable_characters.push_back(temp);
	
}

void PlayingState::mainCollectingStarEvent(PlayableCharacter* character){
	PlayableCharacter* temp = all_playable_characters[0];
	all_playable_characters[0] = new SuperMario(temp);
		
	garbage_of_playable_characters.push_back(temp);
}

void PlayingState::mainBecomeSmall(PlayableCharacter* character){

	PlayableCharacter* temp = all_playable_characters[0];
	all_playable_characters[0] = new Mario(temp);
		
	garbage_of_playable_characters.push_back(temp);
	
}




