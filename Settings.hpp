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
    std::vector<int> categoryAPIValueEntries;
    std::vector<std::string> categoryDisplayEntries;
    std::vector<std::string> difficultyDisplayEntries;
    std::vector<std::string> difficultyAPIValueEntries;
    std::vector<std::string> typeDisplayEntries;
    std::vector<std::string> typeAPIValueEntries;
    std::vector<std::string> soundEffectEntries;

public:
    static Settings& getInstance();

    const int getCategoryAPIValue() const;
    const std::string getDifficultyAPIValue() const;
    const std::string getTypeAPIValue() const;
    const bool areSoundEffectsEnabled() const;
    const std::vector<std::string>& getCategoryDisplayEntries() const;
    const std::vector<std::string>& getDifficultyDisplayEntries() const;
    const std::vector<std::string>& getTypeDisplayEntries() const;
    const std::vector<std::string>& getSoundEffectEntries() const;
    void setCategoryAPIValueEntries(const std::vector<int> pCategoryAPIValueEntries);
    void setCategoryDisplayEntries(const std::vector<std::string> pCategoryDisplayEntries);

    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

private:
    Settings();
};