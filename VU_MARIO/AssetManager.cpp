#include "AssetManager.h"

AssetManager* AssetManager::instance = nullptr;

void AssetManager::load(){
    this->loadBlocks();
    this->loadItems();
    this->loadNonPlayableCharacters();
    this->loadPlayableCharacters();
}

void AssetManager::loadBlocks(){
    sf::Texture* readFile = new sf::Texture;
    if (!readFile->loadFromFile(FILE[0])) {
        std::cout << "Cannot load from file " + FILE[0];
        exit(1);
    }
    blocks = readFile;
}

void AssetManager::loadItems(){
    for (int i = 1; i <= 4; i++) {
        sf::Texture* readFile = new sf::Texture;
        if (!readFile->loadFromFile(FILE[i])) {
            std::cout << "Cannot load from file " + FILE[i];
            exit(1);
        }
        items.push_back(readFile);
    }
}

void AssetManager::loadNonPlayableCharacters(){
    for (int i = 5; i <= 8; i++) {
        sf::Texture* readFile = new sf::Texture;
        if (!readFile->loadFromFile(FILE[i])) {
            std::cout << "Cannot load from file " + FILE[i];
            exit(1);
        }
        nonplayable_characters.push_back(readFile);
    }
}

void AssetManager::loadPlayableCharacters(){
    int size = FILE.size();

    for (int i = 9; i < size; i++) {
        sf::Texture* readFile = new sf::Texture;
        if (!readFile->loadFromFile(FILE[i])) {
            std::cout << "Cannot load from file " + FILE[i];
            exit(1);
        }
        playable_characters.push_back(readFile);
    }
}


AssetManager* AssetManager::getInstance() {
    if (!instance) {
        instance = new AssetManager;
        instance->load();
    }
    return instance;
}

AssetManager::AssetManager(){}


AssetManager::~AssetManager(){
    delete instance;
    
    delete blocks;

    for (const sf::Texture* item : items) {
        delete item;
    }

    for (const sf::Texture* playable_character : playable_characters) {
        delete playable_character;
    }

    for (const sf::Texture* non_playable_character : nonplayable_characters) {
        delete non_playable_character;
    }


    instance = nullptr;

}

std::pair<sf::Texture*, sf::IntRect> AssetManager::getBlock(BlockType type)
{
    return { blocks, IntRect[0][(int)type - 1] };
}

std::pair<sf::Texture*, std::vector<sf::IntRect>> AssetManager::getItem(ItemType type)
{
    if ((int)type - 1 < 0 || offsetItem + (int)type - 1 > IntRect.size()) {
        std::cout << "cannot get Item" + std::to_string((int)type) + "from asset manager";
        exit(1);
    }

    
    return { items[(int)type - 1], IntRect[offsetItem + (int)type - 1] };
}

std::pair<sf::Texture*, std::vector<sf::IntRect>> AssetManager::getPlayableCharacter(PlayableCharacterType type)
{
    if ((int)type - 1 < 0 || offsetPlayable + (int)type - 1 > IntRect.size()) {
        std::cout << "cannot get PlayableCharacter" + std::to_string((int)type) + "from asset manager";
        exit(1);
    }

    return { playable_characters[(int)type - 1], IntRect[offsetPlayable + (int)type - 1] };
}

std::pair<sf::Texture*, std::vector<sf::IntRect>> AssetManager::getNonPlayableCharacter(NonPlayableCharacterType type)
{
    if ((int)type - 1 < 0 || offsetNonPlayable + (int)type - 1 > IntRect.size()) {
        std::cout << "cannot get NonPlayableCharacter" + std::to_string((int)type) + "from asset manager";
        exit(1);
    }

    return { nonplayable_characters[(int)type - 1], IntRect[offsetNonPlayable + (int)type - 1] };
}

std::string AssetManager::getMapFile(int mapNum){
    if (mapNum < 0 || mapNum > 3) {
        std::cout << "Cannot get map";
        exit(1);
    }

    return mapFile[mapNum - 1];
}

int AssetManager::getID(sf::Color color, int& type)
{
    int size = all_colors.size();
    int result = -1;

    for (int i = 0; i < size; i++) {
        if (color == all_colors[i]) {
            result = i + 1;
            break;
        }
    }

    type = result;

    if (result > offSetPlayableForColor) result -= offSetPlayableForColor;
    else if (result > offSetNonPlayableForColor) result -= offSetNonPlayableForColor;
    else if (result > offSetItemForColor) result -= offSetItemForColor;

    return result;
}


sf::FloatRect AssetManager::ToFloatRect(const sf::IntRect& intRect)
{
    return sf::FloatRect(
        static_cast<float>(intRect.left),
        static_cast<float>(intRect.top),
        static_cast<float>(intRect.width),
        static_cast<float>(intRect.height)
    );
}










