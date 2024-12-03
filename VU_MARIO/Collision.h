#pragma once
#include <vector>

class Character;
class PlayableCharacter;
class NonPlayableCharacter;
class Block;
class Item;
class View;
class Observer;

class Collision {
public:
	void handleAllCollision(std::vector<PlayableCharacter*>good_characters, std::vector<NonPlayableCharacter*>bad_characters
	, std::vector<Item*>items, std::vector<Block*>blocks, const float& deltaTime, std::vector<Observer*>& observers,View view);

	void GoodCharacterAndBlock(PlayableCharacter* good_character, Block* block, const float& deltaTime, std::vector<Observer*>& observers);
	void BadCharacterAndBlock(NonPlayableCharacter* bad_character, Block* block, const float& deltaTime, std::vector<Observer*>& observers);
	void GoodCharacterAndItem(PlayableCharacter* good_character, Item* item, const float& deltaTime, std::vector<Observer*>& observers);
	void GoodCharacterAndBadCharacter(PlayableCharacter* good_character, NonPlayableCharacter* bad_character, const float& deltaTime, std::vector<Observer*>& observers);
	void BadCharacterAndBadCharacter(NonPlayableCharacter* bad_character, NonPlayableCharacter* bad_character2, const float& deltaTime, std::vector<Observer*>& observers);
	void ItemAndBlock(Item* item, Block* block, const float& deltaTime, std::vector<Observer*>& observers);
};