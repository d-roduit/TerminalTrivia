#include <algorithm>
#include <random>
#include "Question.hpp"

std::mt19937 Question::RANDOM_NUMBER_GENERATOR{ std::random_device{}() };

std::uniform_int_distribution<std::mt19937::result_type> Question::DISTRIBUTION_0_1{ 0, 1 };

std::uniform_int_distribution<std::mt19937::result_type> Question::DISTRIBUTION_0_3{ 0, 3 };

Question::Question(
    std::string pCategory,
    std::string pType,
    std::string pDifficulty,
    std::string pQuestion,
    std::string pCorrectAnswer,
    std::vector<std::string> pIncorrectAnswers
) : distribution((type == "multiple") ? DISTRIBUTION_0_3 : DISTRIBUTION_0_1) {
    category = pCategory;
    type = pType;
    difficulty = pDifficulty;
    question = pQuestion;
    correctAnswer = pCorrectAnswer;
    incorrectAnswers = pIncorrectAnswers;
    correctAnswerIndex = -1;
}

std::string Question::getCategory() const { return category; }

std::string Question::getType() const { return type; }

std::string Question::getDifficulty() const { return difficulty; }

std::string Question::getQuestion() const { return question; }

std::string Question::getCorrectAnswer() const { return correctAnswer; }

const std::vector<std::string>& Question::getIncorrectAnswers() const { return incorrectAnswers; }

const std::vector<std::string>& Question::getAllPossibleAnswers() {
	allPossibleAnswers = { incorrectAnswers };
    correctAnswerIndex = distribution(RANDOM_NUMBER_GENERATOR);
    allPossibleAnswers.insert(allPossibleAnswers.begin() + correctAnswerIndex, correctAnswer);
	return allPossibleAnswers;
}

int Question::getCorrectAnswerIndex() const {
    return correctAnswerIndex;
}

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