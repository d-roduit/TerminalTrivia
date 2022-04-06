#pragma once

#include <string>

class Settings {

private:
    int category;
    std::string difficulty;
    std::string type;
    const int amount{ 1 };

public:
    static Settings& getInstance();
    int getCategory();
    std::string getDifficulty();
    std::string getType();
    int getAmount();
    void setCategory(int pCategory);
    void setDifficulty(std::string pDifficulty);
    void setType(std::string pType);
    
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

private:
    Settings();
};