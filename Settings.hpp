#pragma once

#include <string>

class Settings {

private:
    std::string difficulty;
    std::string type;
    int category;
    const int amount{ 1 };

public:
    static Settings& getInstance();
    std::string getDifficulty();
    std::string getType();
    int getCategory();
    int getAmount();
    void setDifficulty(std::string pDifficulty);
    void setType(std::string pType);
    void setCategory(int pCategory);
    
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

private:
    Settings();
};