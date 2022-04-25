#pragma once

#include "Settings.hpp"
#include "Stats.hpp"
#include "TriviaAPI.hpp"

/// @brief Represents the TerminalTrivia game. Used to run the game.
class TerminalTrivia {
   
private:
    /// @brief Holds the settings data
    Settings& settings;

    /// @brief Holds the stats data
    Stats& stats;

    /// @brief triviaAPI obect used to interact with the Trivia API
    TriviaAPI& triviaAPI;

public:
    /// @brief Constructor of the TerminalTrivia class. When instantiated, runs the game
    TerminalTrivia();

private:
    /// @brief Renders the main menu with buttons to render the other screens of the game
    void renderMenu();

    /// @brief Renders the play screen.
    void renderPlay();

    /// @brief Renders the settings screen
    void renderSettings();

    /// @brief Renders the stats screen
    void renderStats();

};