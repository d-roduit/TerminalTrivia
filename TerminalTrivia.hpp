#pragma once

#include "Settings.hpp"
#include "Stats.hpp"

class TerminalTrivia {
   
private:
    Settings& settings;
    Stats& stats;

public:
    TerminalTrivia();

private:
    void renderMenu();
    void renderPlay(int questionIndex);
    void renderSettings();
    void renderStats();
};