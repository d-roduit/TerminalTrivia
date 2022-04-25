#pragma once

#include <vector>
#include <string>

/// @brief Holds the settings data
class Settings {

public:
    /// @brief Index of the category selected by the user
    int selectedCategory;

    /// @brief Index of the difficulty selected by the user
    int selectedDifficulty;

    /// @brief Index of the type selected by the user
    int selectedType;

    /// @brief Index of the sound effect setting selected by the user
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

    /// @brief Returns the category value that will be used by the API to fetch a question
    /// @return a category value
    const int getCategoryAPIValue() const;

    /// @brief Returns the difficulty value that will be used by the API to fetch a question
    /// @return a difficulty value
    const std::string getDifficultyAPIValue() const;

    /// @brief Returns the type value that will be used by the API to fetch a question
    /// @return a type value
    const std::string getTypeAPIValue() const;

    /// @brief Returns a boolean stating if the sound effects are enabled or not
    /// @return a boolean
    const bool areSoundEffectsEnabled() const;

    /// @brief Returns the category labels that will be displayed in the settings UI
    const std::vector<std::string>& getCategoryDisplayEntries() const;

    /// @brief Returns the difficulty labels that will be displayed in the settings UI
    const std::vector<std::string>& getDifficultyDisplayEntries() const;

    /// @brief Returns the type labels that will be displayed in the settings UI
    const std::vector<std::string>& getTypeDisplayEntries() const;

    /// @brief Returns the sound effect labels that will be displayed in the settings UI
    const std::vector<std::string>& getSoundEffectEntries() const;

    /// @brief Sets the category values available in the API
    /// @param pCategoryAPIValueEntries The category values available in the API
    void setCategoryAPIValueEntries(const std::vector<int> pCategoryAPIValueEntries);

    /// @brief Sets the category labels that will be displayed in the settings UI
    /// @param pCategoryDisplayEntries The category labels available in the API
    void setCategoryDisplayEntries(const std::vector<std::string> pCategoryDisplayEntries);

    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

private:
    Settings();

};