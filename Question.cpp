#include "Question.hpp"
#include <iostream>

std::mt19937 Question::RANDOM_NUMBER_GENERATOR{ std::random_device{}() };

std::uniform_int_distribution<std::mt19937::result_type> Question::DISTRIBUTION_0_3{ 0, 3 };

Question::Question(
    std::string pCategory,
    std::string pType,
    std::string pDifficulty,
    std::string pQuestion,
    std::string pCorrectAnswer,
    std::vector<std::string> pIncorrectAnswers
) {
    category = pCategory;
    type = pType;
    difficulty = pDifficulty;
    question = pQuestion;
    correctAnswer = pCorrectAnswer;
    incorrectAnswers = pIncorrectAnswers;

    allPossibleAnswers = { incorrectAnswers };

    if (pType == "multiple") {
        correctAnswerIndex = DISTRIBUTION_0_3(RANDOM_NUMBER_GENERATOR);
    }
    else {
        correctAnswerIndex = (correctAnswer == "True") ? 0 : 1;
    }

    allPossibleAnswers.insert(allPossibleAnswers.begin() + correctAnswerIndex, correctAnswer);
}

const std::string Question::getCategory() const { return category; }

const std::string Question::getType() const { return type; }

const std::string Question::getDifficulty() const { return difficulty; }

const std::string Question::getQuestion() const { return question; }

const std::string Question::getCorrectAnswer() const { return correctAnswer; }

const std::vector<std::string>& Question::getIncorrectAnswers() const { return incorrectAnswers; }

const std::vector<std::string>& Question::getAllPossibleAnswers() const { return allPossibleAnswers; }

const int Question::getCorrectAnswerIndex() const { return correctAnswerIndex; }

/*
void Question::setCategory(std::string pCategory) {
    category = pCategory;
}

void Question::setType(std::string pType) {
    type = pType;
}

void Question::setDifficulty(std::string pDifficulty) {
    difficulty = pDifficulty;
}

void Question::setQuestion(std::string pQuestion) {
    question = pQuestion;
}

void Question::setCorrectAnswer(std::string pCorrectAnswer) {
    correctAnswer = pCorrectAnswer;
}

void Question::setIncorrectAnswers(std::vector<std::string> pIncorrectAnswers) {
    incorrectAnswers = pIncorrectAnswers;
}
*/