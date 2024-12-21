#include "ChangingMapState.h"
#include "AssetManager.h"
#include "PlayingState.h"

ChangingMapState::ChangingMapState(){
	this->delay_time = 2;
}

ChangingMapState::ChangingMapState(PlayableCharacterType main, const sf::Font& font,const int& score, const int& coins, const int& mapNum, const int& time, const int& lives){
	this->delay_time = 2;
	
	std::ostringstream cur_score;
	cur_score << std::setfill('0') << std::setw(6) << std::to_string(score);
	this->m_contents.push_back(cur_score.str());

	std::ostringstream cur_coins;
	cur_coins << std::setfill('0') << std::setw(2) << std::to_string(score);
	this->m_contents.push_back(cur_coins.str());

	this->m_contents.push_back(std::to_string(time));

	std::string world = "WORLD " + std::to_string(mapNum) + "-1";
	this->m_contents.push_back(world);

	this->m_contents.push_back(std::to_string(lives));

	std::pair<sf::Texture*, std::vector<sf::IntRect>>character_image = AssetManager::getInstance()->getPlayableCharacter(PlayableCharacterType::small_mario);
	std::pair<sf::Texture*, std::vector<sf::IntRect>>coin_image = AssetManager::getInstance()->getItem(ItemType::coin);

	sf::Sprite character;
	character.setTexture(*character_image.first);
	character.setTextureRect(character_image.second[0]);

	sf::Sprite coin;
	coin.setTexture(*coin_image.first);
	coin.setTextureRect(coin_image.second[0]);

	this->m_icons.push_back(coin);
	this->m_icons.push_back(character);

	this->m_texts = std::vector<sf::Text>(5);
	
	float offSetX = 0;
	std::vector<sf::Vector2f>texts_position;

	for (int i = 0; i < 3; i++) {
		
		texts_position.push_back(sf::Vector2f(offSetX, 30.f));

		offSetX += this->m_texts[i].getGlobalBounds().width + 30.f;
	}

	texts_position.push_back(sf::Vector2f(300.f, 100.f));
	texts_position.push_back(sf::Vector2f(350.f, 120.f));


	this->m_icons[0].setPosition(sf::Vector2f(50.f, 30.f));
	this->m_icons[1].setPosition(sf::Vector2f(300.f, 120.f));

	int texts_size = this->m_texts.size();
	int sprites_size = this->m_icons.size();

	setAttributes<sf::Text>(this->m_texts, this->m_contents, std::vector<sf::Color>(texts_size, sf::Color::White), font, {}, {}, {}, std::vector<int>(texts_size,30), texts_position);
	
	this->m_cur_coin = coins;
	this->m_cur_lives = lives;
	this->m_cur_main = main;
	this->m_cur_mapNum = mapNum;
	this->m_cur_score = score;
}

void ChangingMapState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){
	if(delay_time > 0) delay_time -= deltaTime;

	else {
		this->active = false;
		this->m_nextState = new PlayingState(this->m_cur_coin,this->m_cur_lives,this->m_cur_mapNum,this->m_cur_score,this->m_cur_main);
	}

	this->drawState(window);

	view.setForWindow(window);
}

bool ChangingMapState::isActive(){
	return this->active;
}

void ChangingMapState::drawState(sf::RenderWindow* window){
	this->draw<sf::Sprite>(window, this->m_icons);
	this->draw<sf::Text>(window, this->m_texts);
}

void ChangingMapState::handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window){

}
