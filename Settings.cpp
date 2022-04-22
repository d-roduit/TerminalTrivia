#include <ctime>
#include "Settings.hpp"

Settings& Settings::getInstance() {
    static Settings instance;
    return instance;
}

Settings::Settings() {
    selectedCategory = 0;

    difficultyEntries = {
        "Any Difficulty",
        "Easy",
        "Medium",
        "Hard",
    };
    selectedDifficulty = 0;

    typeEntries = {
        "Any Type",
        "Multiple Choice",
        "True / False",
    };
    selectedType = 0;

    soundEffectEntries = {
        "On",
        "Off",
    };
    selectedSoundEffect = 0;

    const std::time_t timestamp{ std::time(nullptr) };
    APISessionToken = "TERMINALTRIVIA_SESSION_TOKEN_" + std::to_string(timestamp);
}

const int Settings::getCategoryId() const {
    return categoryIdEntries[selectedCategory];
}

const std::string Settings::getDifficulty() const {
    return difficultyEntries[selectedDifficulty];
}

const std::string Settings::getType() const {
    return typeEntries[selectedType];
}

const int Settings::getAmount() const {
    return amount;
}

const bool Settings::areSoundEffectsEnabled() const {
    return (soundEffectEntries[selectedSoundEffect] == "On") ? true : false;
}

const std::vector<std::string>& Settings::getCategoryNameEntries() const {
    return categoryNameEntries;
}

const std::vector<std::string>& Settings::getDifficultyEntries() const {
    return difficultyEntries;
}

const std::vector<std::string>& Settings::getTypeEntries() const {
    return typeEntries;
}

const std::vector<std::string>& Settings::getSoundEffectEntries() const {
    return soundEffectEntries;
}

const std::string Settings::getAPISessionToken() const {
    return APISessionToken;
}

void Settings::setCategoryIdEntries(const std::vector<int> pCategoryIdEntries) {
    categoryIdEntries = pCategoryIdEntries;
}

void Settings::setCategoryNameEntries(const std::vector<std::string> pCategoryNameEntries) {
    categoryNameEntries = pCategoryNameEntries;
}
