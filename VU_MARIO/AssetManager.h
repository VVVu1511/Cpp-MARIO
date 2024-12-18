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
	stick = 16,
	blue_ground = 17,
	blue_indestructible = 18,
	blue_baseBrick = 19,
	blue_brick = 20,
	pink_vertical_pipe = 21,
	pink_vertical_pipe_top = 22,
	pink_horizontal_pipe = 23,
	light_blue_ground = 24,
	light_blue_brick = 25,
	light_blue_baseBrick = 26,

	dark_blue_baseBrick = 27,
	dark_blue_indestructible = 28,
	winter_cloud = 29,
	winter_flag = 30,
	winter_stick = 31,
	moon = 32,
	christmas_tree = 33,
	princess = 34,
	star = 35,
	signpost = 36,
	snow_pipe = 37,
	gray_ground = 38,
	gray_brick = 39,
};

enum class ItemType {
	star = 1,
	mushroom = 2,
	flower = 3,
	coin = 4,
};

enum class NonPlayableCharacterType {
	bullet = -1,
	cactus = 1,
	boss = 2,
	goomba = 3,
	koopatroopa = 4,
	fire_sequence = 5,
};

enum class PlayableCharacterType {
	good_bullet = -1,
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

enum class BonusAnimation {
	bonus_brick_animation = 1,
	winter_goomba = 2,
	main_fire = 3,
	blue_turtle = 4,
	red_turtle = 5,
	boss_fire = 6,
};

class AssetManager {
private:
	const std::vector<sf::Color> all_colors = {
	//blocks
	sf::Color(1, 1, 1),
	sf::Color(255, 126, 0),
	sf::Color(255, 242, 0),
	sf::Color(156, 90, 60),
	sf::Color(1, 1, 1),
	sf::Color(82,34,13),
	sf::Color(34, 177, 76),
	sf::Color(47,255,0),
	sf::Color(71,122,58),
	sf::Color(27,64,17),
	sf::Color(0, 0, 0),
	sf::Color(115,115,115),
	sf::Color(1, 1, 1),

	sf::Color(77, 109, 243),
	sf::Color(1, 1, 1),
	sf::Color(138,40,138),
	sf::Color(136,193,222),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(177, 65, 175),
	sf::Color(177, 109, 169),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),

	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(194,192,93),
	sf::Color(1,1,1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(76, 82, 81),
	sf::Color(139, 150, 149),
	//item
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(1, 1, 1),
	sf::Color(150,141,6),
	//nonplayable
	sf::Color(148, 66, 137),
	sf::Color(113, 201, 154),
	sf::Color(153,0,48),
	sf::Color(168,230,29),
	sf::Color(201,127,47),
	//playable
	sf::Color(237,28,36),
	};


	const std::vector<std::string>mapFile = {"../images/map1.png","../images/map2.png" ,"../images/map3.png"};

	const int offsetItem = 1;
	const int offsetNonPlayable = 5;
	const int offsetPlayable = 10;

	const int offSetItemForColor = 39;
	const int offSetNonPlayableForColor = 43;
	const int offSetPlayableForColor = 48;


	std::vector<std::vector<sf::IntRect>> IntRect = {
		//block
		{sf::IntRect(0, 0, 296, 352), sf::IntRect(296, 0, 32, 32), sf::IntRect(328, 0, 32, 32), sf::IntRect(360, 0, 32, 32), 
		sf::IntRect(392, 0, 32, 32), sf::IntRect(424, 0, 32, 32), sf::IntRect(456, 0, 56, 34), sf::IntRect(512, 0, 64, 30),
		sf::IntRect(576, 0, 64, 32), sf::IntRect(640, 0, 96, 38), sf::IntRect(736, 0, 160, 160), sf::IntRect(896, 0, 64, 48),
		sf::IntRect(960, 0, 64, 32), sf::IntRect(1024, 0, 32, 32), sf::IntRect(1056, 0, 62, 70), sf::IntRect(1118, 0, 16, 304),
		sf::IntRect(1134, 0, 32, 32), sf::IntRect(1166, 0, 32, 32), sf::IntRect(1198, 0, 32, 32), sf::IntRect(1230, 0, 32, 32),
		sf::IntRect(1262, 0, 56, 34), sf::IntRect(1318, 0, 64, 30), sf::IntRect(1382, 0, 78, 64), sf::IntRect(1460, 0, 32, 32),
		sf::IntRect(1492, 0, 32, 32), sf::IntRect(1524, 0, 32, 32), sf::IntRect(1556, 0, 32, 32), sf::IntRect(1588, 0, 32, 32),
		sf::IntRect(1620, 0, 64, 48), sf::IntRect(1684, 0, 32, 32), sf::IntRect(1716, 0, 16, 304), sf::IntRect(1732, 0, 59, 58),
		sf::IntRect(1791, 0, 50, 79), sf::IntRect(1841, 0, 28, 48), sf::IntRect(1869, 0, 14, 16), sf::IntRect(1883, 0, 51, 53),
		sf::IntRect(1934, 0, 16, 48), sf::IntRect(1950, 0, 32, 32), sf::IntRect(1982, 0, 32, 32)},
		//item
	{sf::IntRect(0, 0, 28, 32), sf::IntRect(28, 0, 28, 32), sf::IntRect(56, 0, 28, 32),
	 sf::IntRect(84, 0, 28, 32)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32),
	 sf::IntRect(96, 0, 32, 32)},
	{sf::IntRect(0, 0, 20, 28), sf::IntRect(20, 0, 20, 28), sf::IntRect(40, 0, 20, 28),
	 sf::IntRect(60, 0, 20, 28)},
	//nonplayable
	{sf::IntRect(0, 0, 32, 48), sf::IntRect(32, 0, 32, 46)},
	{sf::IntRect(0, 0, 64, 64), sf::IntRect(64, 0, 64, 64)},
	{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 16)},
	{sf::IntRect(0, 0, 32, 48), sf::IntRect(32, 0, 32, 46),sf::IntRect(64, 0, 32, 28)},
	{sf::IntRect(0, 0, 29, 80)},
	//playable
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

	
	const std::vector<std::vector<sf::IntRect>>bonusIntRect = { 
		{sf::IntRect(0,0,32,32),sf::IntRect(32,0,32,32)} ,
		{sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32)},
		{sf::IntRect(0, 0, 16, 16), sf::IntRect(16, 0, 16, 16), sf::IntRect(32, 0, 16, 16), sf::IntRect(48, 0, 16, 16)},
		{sf::IntRect(0, 0, 32, 46), sf::IntRect(32, 0, 32, 48),sf::IntRect(64, 0, 32, 28)},
		{sf::IntRect(0, 0, 32, 48), sf::IntRect(32, 0, 32, 46),sf::IntRect(64, 0, 32, 28)},
		{sf::IntRect(0, 0, 48, 16), sf::IntRect(48, 0, 48, 16)},
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
		"../images/fire_sequence.png",
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

	const std::vector<std::string>BONUS_FILE = {
		"../images/bonus_brick.png",
		"../images/winter_goomba.png",
		"../images/main_fire.png",
		"../images/blue_turtle.png",
		"../images/red_turtle.png",
		"../images/boss_fire.png",
	};

	
	sf::Texture* blocks;
	std::vector<sf::Texture*> items;
	std::vector<sf::Texture*> playable_characters;
	std::vector<sf::Texture*> nonplayable_characters;
	std::vector<sf::Texture*> bonus_animation;

	const float gravity = 10.f;

	static AssetManager* instance;

	void load();
	void loadBlocks();
	void loadItems();
	void loadNonPlayableCharacters();
	void loadPlayableCharacters();
	void loadBonusAnimation();

public:
	static void destroy();
	static AssetManager* getInstance();

	AssetManager();
	~AssetManager();

	std::pair<sf::Texture*, sf::IntRect> getBlock(BlockType type);
	std::pair<sf::Texture*, std::vector<sf::IntRect>> getItem(ItemType type);
	std::pair<sf::Texture*, std::vector<sf::IntRect>> getPlayableCharacter(PlayableCharacterType type);
	std::pair<sf::Texture*, std::vector<sf::IntRect>> getNonPlayableCharacter(NonPlayableCharacterType type);
	std::pair<sf::Texture*, std::vector<sf::IntRect>> getBonusAnimation(BonusAnimation type);

	std::string getMapFile(int mapNum);
	int getID(sf::Color color,int& type);
	sf::FloatRect ToFloatRect(const sf::IntRect& intRect);

};




