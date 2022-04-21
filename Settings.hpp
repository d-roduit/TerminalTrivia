#pragma once

#include <vector>
#include <string>

class Settings {

public:
    int selectedCategory;
    int selectedDifficulty;
    int selectedType;
    int selectedSoundEffect;

private:
    const int amount{ 1 };
    std::vector<int> categoryIdEntries;
    std::vector<std::string> categoryNameEntries;
    std::vector<std::string> difficultyEntries;
    std::vector<std::string> typeEntries;
    std::vector<std::string> soundEffectEntries;

public:
    static Settings& getInstance();
    int getCategoryId() const;
    std::string getDifficulty() const;
    std::string getType() const;
    int getAmount() const;
    bool areSoundEffectsEnabled() const;
    const std::vector<std::string>& getCategoryNameEntries() const;
    const std::vector<std::string>& getDifficultyEntries() const;
    const std::vector<std::string>& getTypeEntries() const;
    const std::vector<std::string>& getSoundEffectEntries() const;
    
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

private:
    Settings();
};