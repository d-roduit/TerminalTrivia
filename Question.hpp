#pragma once

#include <random> // for uniform_int_distribution, mt19937
#include <string>
#include <vector>

/// @brief Represents a question fetched from the Trivia API. It holds the question data
class Question {

private:
    /// @brief Random number generator engine. Used to generate a random index for the correct answer
    static std::mt19937 RANDOM_NUMBER_GENERATOR;

    /// @brief Distribution of range [0,3]. Used in conjunction with RANDOM_NUMBER_GENERATOR to generate a number in the specified range only
    static std::uniform_int_distribution<std::mt19937::result_type> DISTRIBUTION_0_3;

    std::string category;
    std::string type;
    std::string difficulty;
    std::string question;
    std::string correctAnswer;
    std::vector<std::string> incorrectAnswers;

    /// @brief A vector containing both the correct and incorrect answers
    std::vector<std::string> allPossibleAnswers;

    /// @brief The index of the correct answer in the allPossibleAnswers vector. Used to keep track of the position of the correct answer in the allPossibleAnswers vector
    int correctAnswerIndex;

public:
    Question(
        std::string pCategory,
        std::string pType,
        std::string pDifficulty,
        std::string pQuestion,
        std::string pCorrectAnswer,
        std::vector<std::string> pIncorrectAnswers
    );
    const std::string getCategory() const;
    const std::string getType() const;
    const std::string getDifficulty() const;
    const std::string getQuestion() const;
    const std::string getCorrectAnswer() const;
    const std::vector<std::string>& getIncorrectAnswers() const;
    const std::vector<std::string>& getAllPossibleAnswers() const;
    const int getCorrectAnswerIndex() const;

};