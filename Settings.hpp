#pragma once

#include <vector>
#include <string>

class Settings {

public:
    int selectedCategory;
    int selectedDifficulty;
    int selectedType;

private:
    const int amount{ 1 };
    std::vector<int> categoryIdEntries;
    std::vector<std::string> categoryNameEntries;
    std::vector<std::string> difficultyEntries;
    std::vector<std::string> typeEntries;

public:
    static Settings& getInstance();
    int getCategoryId() const;
    std::string getDifficulty() const;
    std::string getType() const;
    int getAmount() const;
    const std::vector<std::string>& getCategoryNameEntries() const;
    const std::vector<std::string>& getDifficultyEntries() const;
    const std::vector<std::string>& getTypeEntries() const;
    
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

private:
    Settings();
};