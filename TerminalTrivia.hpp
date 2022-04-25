#pragma once

#include "Settings.hpp"
#include "Stats.hpp"
#include "TriviaAPI.hpp"

class TerminalTrivia {
   
private:
    Settings& settings;
    Stats& stats;
    TriviaAPI& triviaAPI;

public:
    TerminalTrivia();

private:
    void renderMenu();
    void renderPlay();
    void renderSettings();
    void renderStats();

};