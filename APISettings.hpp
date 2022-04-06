#pragma once

#include <string>

class APISettings {

private:
    std::string difficulty;
    std::string type;
    int category;
    const int amount{ 1 };

public:
    static APISettings& getInstance();
    std::string getDifficulty();
    std::string getType();
    int getCategory();
    int getAmount();
    void setDifficulty(std::string pDifficulty);
    void setType(std::string pType);
    void setCategory(int pCategory);

    APISettings(APISettings const&) = delete;
    void operator=(APISettings const&) = delete;

private:
    APISettings();
};