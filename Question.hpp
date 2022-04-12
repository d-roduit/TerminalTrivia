#pragma once

#include <algorithm>
#include <random>
#include <string>
#include <vector>

class Question {

private:
    static std::mt19937 RANDOM_NUMBER_GENERATOR;
    static std::uniform_int_distribution<std::mt19937::result_type> DISTRIBUTION_0_1;
    static std::uniform_int_distribution<std::mt19937::result_type> DISTRIBUTION_0_3;
    const std::uniform_int_distribution<std::mt19937::result_type>& distribution;
    std::string category;
    std::string type;
    std::string difficulty;
    std::string question;
    std::string correctAnswer;
    std::vector<std::string> incorrectAnswers;
    std::vector<std::string> allPossibleAnswers;
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
    /*
    void setCategory(std::string pCategory);
    void setType(std::string pType);
    void setDifficulty(std::string pDifficulty);
    void setQuestion(std::string pQuestion);
    void setCorrectAnswer(std::string pCorrectAnswer);
    void setIncorrectAnswers(std::vector<std::string> pIncorrectAnswers);
    */
};