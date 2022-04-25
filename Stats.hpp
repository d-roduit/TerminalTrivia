#pragma once

/// @brief Holds the stats data
class Stats {

private:
    /// @brief Total number of answered questions
    int nbAnsweredQuestions;

    /// @brief Number of questions asnwered correctly
    int nbPositiveAnswers;

public:
    static Stats& getInstance();

    /// @brief Returns the total number of answered questions
    int getNbAnsweredQuestions() const;

    /// @brief Returns the number of questions answered correctly
    int getNbPositiveAnswers() const;

    /// @brief Returns the percentage of correct answers compared to the total number of question answered
    int getPositiveAnswersRate() const;

    /// @brief Increment the stats values
    /// @param pHasAnsweredCorrectly A boolean stating if the answer is correct or not
    void incrementNbAnsweredQuestions(bool pHasAnsweredCorrectly);

    Stats(Stats const&) = delete;
    void operator=(Stats const&) = delete;

private:
    Stats();

};