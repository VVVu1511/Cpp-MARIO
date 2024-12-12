#pragma once
#include<SFML/Audio.hpp>
#include<iostream>
#include<vector>

enum class SoundType {
    one_up_collect = 1,
    back_to_small = 2,
    background_castle = 3,
    background_open = 4,
    background_star = 5,
    background_summer = 6,
    background_underground = 7,
    background_winter = 8,
    block_destroyed = 9,
    block_hitted = 10,
    bonus_appeared = 11,
    bonus_collected = 12,
    boss_destroyed = 13,
    coin_sound = 14,
    enemy_destroyed = 15,
    fire_rocket = 16,
    fireball_popped = 17,
    fireworks = 18,
    flag_down = 19,
    game_over = 20,
    getting_points = 21,
    jump_small = 22,
    jump_tall = 23,
    level_finished = 24,
    mario_dead = 25,
    menu_return = 26,
    time_passed = 27,
    world_finished = 28,

};

class SoundManager {
private:
    const std::vector<std::string>soundFile = {
        "../sounds/1up_collected.wav",
        "../sounds/back_to_small.wav",
        "../sounds/background_castle.wav",
        "../sounds/background_open.wav",
        "../sounds/background_star.wav",
        "../sounds/background_summer.wav",
        "../sounds/background_underground.wav",
        "../sounds/background_winter.wav",
        "../sounds/block_destroyed.wav",
        "../sounds/block_hitted.wav",
        "../sounds/bonus_appeard.wav",
        "../sounds/bonus_collected.wav",
        "../sounds/boss_destroyed.wav",
        "../sounds/coin_sound.wav",
        "../sounds/enemy_destroyed.wav",
        "../sounds/fire_rocket.wav",
        "../sounds/fireball_popped.wav",
        "../sounds/fireworks.wav",
        "../sounds/flag_down.wav",
        "../sounds/game_over.wav",
        "../sounds/getting_points.wav",
        "../sounds/jump_small.wav",
        "../sounds/jump_tall.wav",
        "../sounds/level_finished.wav",
        "../sounds/mario_dead.wav",
        "../sounds/menu_return.wav",
        "../sounds/time_passed.wav",
        "../sounds/world_finished.wav",
    };

    std::vector<sf::Sound> sounds;
    std::vector<sf::SoundBuffer> soundBuffers;

    static SoundManager* instance;    

    void load();
    void cleanup();
public:
    SoundManager();
    ~SoundManager();

    static SoundManager* getInstance();
    void playSound(SoundType id);
    void stopSound(SoundType id);
    sf::Sound::Status getSoundStatus(SoundType id);
};