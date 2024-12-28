#include "Sound.h"

SoundManager* SoundManager::instance = nullptr;


void SoundManager::load(){
	int size = this->soundFile.size();
	sounds = std::vector<sf::Sound>(size);
	soundBuffers = std::vector<sf::SoundBuffer>(size);

	for (int i = 0; i < size; i++) 
	{
		if (!soundBuffers[i].loadFromFile(soundFile[i])) {
			std::cout << "Can not load file " + soundFile[i];
			exit(1);
		}

		sounds[i].setBuffer(soundBuffers[i]);
	}
}

void SoundManager::cleanup(){
	for (auto& s : sounds) {
		s.stop();
	}

	soundBuffers.clear();
	sounds.clear();

	delete instance;
	
	instance = nullptr;
	
}

SoundManager::SoundManager(){}

SoundManager::~SoundManager(){
	this->cleanup();
}

SoundManager* SoundManager::getInstance()
{
	if (!instance) {
		instance = new SoundManager;
		instance->load();
	}
	return instance;
}

void SoundManager::playSound(SoundType id){
	this->sounds[(int)id - 1].play();
}

void SoundManager::stopSound(SoundType id){
	this->sounds[(int)id - 1].stop();
}

void SoundManager::clear() {
	for (auto& sound : sounds) {
		sound.stop();
	}

	sounds.clear();
	soundBuffers.clear();

	std::cout << "SoundManager: All sounds and buffers have been cleared." << std::endl;
}

void SoundManager::setVolume(SoundType type, float volume)
{
	this->sounds[(int)type - 1].setVolume(volume);
}


