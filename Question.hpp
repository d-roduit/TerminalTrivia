#pragma once

#include <string>
#include <vector>

class Question {

private:
    static std::default_random_engine randomEngine;
    std::string category;
    std::string type;
    std::string difficulty;
    std::string question;
    std::string correctAnswer;
    std::vector<std::string> incorrectAnswers;

public:
    Question();
    std::string getCategory();
    std::string getType();
    std::string getDifficulty();
    std::string getQuestion();
    std::string getCorrectAnswer();
    std::vector<std::string> getIncorrectAnswers();
    std::vector<std::string> getAllPossibleAnswers();
    void setCategory(std::string pCategory);
    void setType(std::string pType);
    void setDifficulty(std::string pDifficulty);
    void setQuestion(std::string pQuestion);
    void setCorrectAnswer(std::string pCorrectAnswer);
    void setIncorrectAnswers(std::vector<std::string> pIncorrectAnswers);
};