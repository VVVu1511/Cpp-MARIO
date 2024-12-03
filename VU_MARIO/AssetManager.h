#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<map>
#include<SFML/Graphics.hpp>
#include <iostream>


enum class BlockType{
	big_castle = 1,
	ground = 2,
	bonus = 3,
	indestructible = 4,
	basebrick = 5,
	brick = 6,
	vertical_pipe = 7,
	vertical_pipe_top = 8,
	tree = 9,
	mountain = 10, 
	castle = 11,
	cloud = 12,
	fence = 13,
	flag = 14,
	palm = 15,
	stick = 16
};

enum class ItemType {
	star = 1,
	mushroom = 2,
	flower = 3,
	coin = 4,
};

enum class NonPlayableCharacterType {
	cactus = 1,
	boss = 2,
	goomba = 3,
	koopatroopa = 4,
};

enum class PlayableCharacterType {
	small_mario = 1,
	small_mario_disappear = 2,
	small_super_mario = 3,
	small_fire_mario = 4,
	small_luigi = 5,
	big_mario = 6,
	big_luigi = 7,
	big_fire_mario = 8,
	big_fire_luigi = 9,
	big_super_luigi = 10,
	big_super_mario = 11,
};


class AssetManager {
private:
	const std::vector<sf::Color> all_colors = {
	sf::Color(1, 1, 1),
	sf::Color(255, 126, 0),
	sf::Color(255, 242, 0),
	sf::Color(156, 90, 60),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(34, 177, 76),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(0, 0, 0),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(77, 109, 243),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(150,141,6),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(153,0,48),
	sf::Color(168,230,29),
	sf::Color(237,28,36),
	};


	const std::vector<std::string>mapFile = {"../images/map1.png","../images/map2.png" ,"../images/map3.png" };

	const int offsetItem = 1;
	const int offsetNonPlayable = 5;
	const int offsetPlayable = 9;

	const int offSetItemForColor = 16;
	const int offSetNonPlayableForColor = 20;
	const int offSetPlayableForColor = 24;



	std::vector<std::vector<sf::IntRect>> IntRect = {
	{sf::IntRect(0, 0, 296, 352), sf::IntRect(296, 0, 32, 32), sf::IntRect(328, 0, 32, 32),
	 sf::IntRect(360, 0, 32, 32), sf::IntRect(392, 0, 32, 32), sf::IntRect(424, 0, 32, 32),
	 sf::IntRect(456, 0, 56, 34), sf::IntRect(512, 0, 64, 30), sf::IntRect(576, 0, 64, 32),
	 sf::IntRect(640, 0, 96, 38), sf::IntRect(736, 0, 160, 160), sf::IntRect(896, 0, 64, 48),
	 sf::IntRect(960, 0, 64, 32), sf::IntRect(1024, 0, 32, 32), sf::IntRect(1056, 0, 62, 70),
	 sf::IntRect(1118, 0, 16, 304)},
	{sf::IntRect(0, 0, 28, 32), sf::IntRect(28, 0, 28, 32), sf::IntRect(56, 0, 28, 32),
	 sf::IntRect(84, 0, 28, 32)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32),
	 sf::IntRect(96, 0, 32, 32)},
	{sf::IntRect(0, 0, 20, 28), sf::IntRect(20, 0, 20, 28), sf::IntRect(40, 0, 20, 28),
	 sf::IntRect(60, 0, 20, 28)},
	{sf::IntRect(0, 0, 32, 48), sf::IntRect(32, 0, 32, 46)},
	{sf::IntRect(0, 0, 64, 64), sf::IntRect(64, 0, 64, 64)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 16)},
	{sf::IntRect(0, 0, 32, 48), sf::IntRect(32, 0, 32, 46),sf::IntRect(64, 0, 32, 28)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32),
	 sf::IntRect(96, 0, 32, 32), sf::IntRect(128, 0, 32, 32), sf::IntRect(160, 0, 32, 32)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32),
	 sf::IntRect(96, 0, 32, 32), sf::IntRect(128, 0, 32, 32)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32),
	 sf::IntRect(96, 0, 32, 32), sf::IntRect(128, 0, 32, 32), sf::IntRect(160, 0, 32, 32)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32),
	 sf::IntRect(96, 0, 32, 32), sf::IntRect(128, 0, 32, 32), sf::IntRect(160, 0, 32, 32)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32),
	 sf::IntRect(96, 0, 32, 32), sf::IntRect(128, 0, 32, 32), sf::IntRect(160, 0, 32, 32)},
	{sf::IntRect(0, 0, 32, 64), sf::IntRect(32, 0, 32, 64), sf::IntRect(64, 0, 32, 64),
	 sf::IntRect(96, 0, 32, 64), sf::IntRect(128, 0, 32, 64)},
	{sf::IntRect(0, 0, 32, 64), sf::IntRect(32, 0, 32, 64), sf::IntRect(64, 0, 32, 64),
	 sf::IntRect(96, 0, 32, 64), sf::IntRect(128, 0, 32, 64)},
	{sf::IntRect(0, 0, 32, 64), sf::IntRect(32, 0, 32, 64), sf::IntRect(64, 0, 32, 64),
	 sf::IntRect(96, 0, 32, 64), sf::IntRect(128, 0, 32, 64)},
	{sf::IntRect(0, 0, 32, 64), sf::IntRect(32, 0, 32, 64), sf::IntRect(64, 0, 32, 64),
	 sf::IntRect(96, 0, 32, 64), sf::IntRect(128, 0, 32, 64)},
	{sf::IntRect(0, 0, 32, 64), sf::IntRect(32, 0, 32, 64), sf::IntRect(64, 0, 32, 64),
	 sf::IntRect(96, 0, 32, 64), sf::IntRect(128, 0, 32, 64)},
	{sf::IntRect(0, 0, 32, 64), sf::IntRect(32, 0, 32, 64), sf::IntRect(64, 0, 32, 64),
	 sf::IntRect(96, 0, 32, 64), sf::IntRect(128, 0, 32, 64)},
	};

	const std::vector<std::string>FILE = {
		"../images/blocks.png",
		"../images/star.png",
		"../images/mushroom.png",
		"../images/flower.png",
		"../images/coin.png",
		"../images/cactus.png",
		"../images/boss.png",
		"../images/goomba.png",
		"../images/koopatroopa.png",
		"../images/small_mario.png",
		"../images/small_mario_disappear.png",
		"../images/small_super_mario.png",
		"../images/small_fire_mario.png",
		"../images/small_luigi.png",
		"../images/big_mario.png",
		"../images/big_luigi.png",
		"../images/big_fire_mario.png",
		"../images/big_fire_luigi.png",
		"../images/big_super_luigi.png",
		"../images/big_super_mario.png",
	};


	sf::Texture* blocks;
	std::vector<sf::Texture*> items;
	std::vector<sf::Texture*> playable_characters;
	std::vector<sf::Texture*> nonplayable_characters;


	const float gravity = 10.f;

	static AssetManager* instance;

	void load();
	void loadBlocks();
	void loadItems();
	void loadNonPlayableCharacters();
	void loadPlayableCharacters();


public:
	static AssetManager* getInstance();
	AssetManager();
	~AssetManager();

	std::pair<sf::Texture*, sf::IntRect> getBlock(BlockType type);
	std::pair<sf::Texture*, std::vector<sf::IntRect>> getItem(ItemType type);
	std::pair<sf::Texture*, std::vector<sf::IntRect>> getPlayableCharacter(PlayableCharacterType type);
	std::pair<sf::Texture*, std::vector<sf::IntRect>> getNonPlayableCharacter(NonPlayableCharacterType type);

	std::string getMapFile(int mapNum);
	int getID(sf::Color color,int& type);
	sf::FloatRect ToFloatRect(const sf::IntRect& intRect);
};




