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
    std::string APISessionToken;

public:
    static Settings& getInstance();
    const int getCategoryId() const;
    const std::string getDifficulty() const;
    const std::string getType() const;
    const int getAmount() const;
    const bool areSoundEffectsEnabled() const;
    const std::vector<std::string>& getCategoryNameEntries() const;
    const std::vector<std::string>& getDifficultyEntries() const;
    const std::vector<std::string>& getTypeEntries() const;
    const std::vector<std::string>& getSoundEffectEntries() const;
    const std::string getAPISessionToken() const;
    void setCategoryIdEntries(const std::vector<int> categoryIdEntries);
    void setCategoryNameEntries(const std::vector<std::string> categoryNameEntries);

    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

private:
    Settings();
};