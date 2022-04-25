#include "Settings.hpp"

Settings& Settings::getInstance() {
    static Settings instance;
    return instance;
}

Settings::Settings() {
    selectedCategory = 0;

    difficultyDisplayEntries = {
        "Any Difficulty",
        "Easy",
        "Medium",
        "Hard",
    };
    difficultyAPIValueEntries = {
        "",
        "easy",
        "medium",
        "hard",
    };
    selectedDifficulty = 0;

    typeDisplayEntries = {
        "Any Type",
        "Multiple Choice",
        "True / False",
    };
    typeAPIValueEntries = {
        "",
        "multiple",
        "boolean",
    };
    selectedType = 0;

    soundEffectEntries = {
        "On",
        "Off",
    };
    selectedSoundEffect = 0;
}

const int Settings::getCategoryAPIValue() const {
    return categoryAPIValueEntries[selectedCategory];
}

const std::string Settings::getDifficultyAPIValue() const {
    return difficultyAPIValueEntries[selectedDifficulty];
}

const std::string Settings::getTypeAPIValue() const {
    return typeAPIValueEntries[selectedType];
}

const bool Settings::areSoundEffectsEnabled() const {
    return (soundEffectEntries[selectedSoundEffect] == "On") ? true : false;
}

const std::vector<std::string>& Settings::getCategoryDisplayEntries() const {
    return categoryDisplayEntries;
}

const std::vector<std::string>& Settings::getDifficultyDisplayEntries() const {
    return difficultyDisplayEntries;
}

const std::vector<std::string>& Settings::getTypeDisplayEntries() const {
    return typeDisplayEntries;
}

const std::vector<std::string>& Settings::getSoundEffectEntries() const {
    return soundEffectEntries;
}

void Settings::setCategoryAPIValueEntries(const std::vector<int> pCategoryAPIValueEntries) {
    categoryAPIValueEntries = pCategoryAPIValueEntries;
}

void Settings::setCategoryDisplayEntries(const std::vector<std::string> pCategoryDisplayEntries) {
    categoryDisplayEntries = pCategoryDisplayEntries;
}
