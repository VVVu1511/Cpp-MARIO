#include "Collision.h"
#include "Observer.h"
#include "View.h"
#include "Block.h"
#include "Item.h"
#include "PlayableCharacter.h"
#include "NonPlayableCharacter.h"
#include "Character.h"
#include <iostream>

void Collision::handleAllCollision(std::vector<PlayableCharacter*> good_characters, std::vector<NonPlayableCharacter*> bad_characters, std::vector<Item*> items, std::vector<Block*> blocks, const float& deltaTime, std::vector<Observer*>& observers,View view){
	for (PlayableCharacter* good_character : good_characters) {
		good_character->reset();
		if (good_character == nullptr) continue;

		for (Block* block : blocks) {
			if (block != nullptr && block->canInteract() == true && block->standInView(view)) {
				GoodCharacterAndBlock(good_character, block, deltaTime, observers);
			}
		}
	}

	for (NonPlayableCharacter* bad_character : bad_characters) {
		bad_character->reset();
		for (Block* block : blocks) {
			if (block != nullptr && block->canInteract() == true && bad_character->standInView(view) && block->standInView(view)) {
				BadCharacterAndBlock(bad_character, block, deltaTime, observers);
			}
		}
	}

	for (PlayableCharacter* good_character : good_characters) {
		for (NonPlayableCharacter* bad_character : bad_characters) {
			if (good_character == nullptr) continue;

			if (bad_character->standInView(view)) {
				GoodCharacterAndBadCharacter(good_character, bad_character, deltaTime, observers);
			}
		}
	}
	
	
	int enemies_size = bad_characters.size();

	for (int i = 0; i < enemies_size - 1; i++) {
		for (int j = i + 1; j < enemies_size; j++) {
			if (bad_characters[i]->standInView(view) && bad_characters[j]->standInView(view)) {
				BadCharacterAndBadCharacter(bad_characters[i], bad_characters[j], deltaTime, observers);
			}
		}
	}
	
	
	for (PlayableCharacter* good_character : good_characters) {
		if (good_character == nullptr) continue;

		for (Item* item : items) {
			if (item->standInView(view)) {
				GoodCharacterAndItem(good_character, item, deltaTime, observers);
			}
		}

	}

	for (Item* item : items) {
		item->reset();
		for (Block* block : blocks) {
			if (block->canInteract() && item->standInView(view) && block->standInView(view)) {
				ItemAndBlock(item, block, deltaTime, observers,good_characters);
			}
		}
	}

}

void Collision::GoodCharacterAndBlock(PlayableCharacter* good_character, Block* block, const float& deltaTime, std::vector<Observer*>& observers){
	if (good_character != nullptr &&  !block->isDead() && !good_character->isDead()) {
		good_character->hit(block, observers);
		good_character->StandOn(block,observers);
	}
}

void Collision::BadCharacterAndBlock(NonPlayableCharacter* bad_character, Block* block, const float& deltaTime, std::vector<Observer*>& observers){
	if (!block->isDead() && !bad_character->isDead()) {
		bad_character->StandOn(block,observers);
		bad_character->hit(block, observers);
		block->hit(bad_character, observers);
	}
}

void Collision::GoodCharacterAndItem(PlayableCharacter* good_character, Item* item, const float& deltaTime, std::vector<Observer*>& observers){
	if (good_character != nullptr && !good_character->isDead() && !item->isDead()) {
		good_character->collect(item, observers);
	}
}

void Collision::GoodCharacterAndBadCharacter(PlayableCharacter* good_character, NonPlayableCharacter* bad_character, const float& deltaTime, std::vector<Observer*>& observers){
	if (good_character != nullptr && !good_character->isDead() && !bad_character->isDead()) {
		good_character->standOn(bad_character, observers);
		if(!bad_character->isDead()) good_character->hit(bad_character, observers);
	}
}

void Collision::BadCharacterAndBadCharacter(NonPlayableCharacter* bad_character, NonPlayableCharacter* bad_character2, const float& deltaTime, std::vector<Observer*>& observers){
	if (!bad_character2->isDead() && !bad_character->isDead()) {
		bad_character->hit(bad_character2, observers);
	}
}

void Collision::ItemAndBlock(Item* item, Block* block, const float& deltaTime, std::vector<Observer*>& observers, const std::vector<PlayableCharacter*>& characters){
	if (!block->isDead() && !item->isDead()) {
		item->standOn(block,observers);
		item->hit(block);
		block->hit(item, observers, characters);
	}
}


