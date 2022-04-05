#pragma once

class APISettings {

private:
    int difficulty;
    int type;
    int category;
    const int amount{ 1 };

public:
    static APISettings& getInstance();
    int getDifficulty();
    int getType();
    int getCategory();
    int getAmount();
    void setDifficulty(int pDifficulty);
    void setType(int pType);
    void setCategory(int pCategory);

    APISettings(APISettings const&) = delete;
    void operator=(APISettings const&) = delete;

private:
    APISettings();
};