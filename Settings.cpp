#include "Settings.hpp"

Settings& Settings::getInstance() {
    static Settings instance;
    return instance;
}

Settings::Settings() {
    categoryIdEntries = { 0, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };
    categoryNameEntries = {
        "Any Category",
        "General Knowledge",
        "Entertainment: Books",
        "Entertainment: Film",
        "Entertainment: Music",
        "Entertainment: Musicals & Theatres",
        "Entertainment: Television",
        "Entertainment: Video Games",
        "Entertainment: Board Games",
        "Science & Nature",
        "Science: Computers",
        "Science: Mathematics",
        "Mythology",
        "Sports",
        "Geography",
        "History",
        "Politics",
        "Art",
        "Celebrities",
        "Animals",
        "Vehicles",
        "Entertainment: Comics",
        "Science: Gadgets",
        "Entertainment: Japanese Anime & Manga",
        "Entertainment: Cartoon & Animations",
    };
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
}

int Settings::getCategoryId() const {
    return categoryIdEntries[selectedCategory];
}

std::string Settings::getDifficulty() const {
    return difficultyEntries[selectedDifficulty];
}

std::string Settings::getType() const {
    return typeEntries[selectedType];
}

int Settings::getAmount() const {
    return amount;
}

bool Settings::areSoundEffectsEnabled() const {
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