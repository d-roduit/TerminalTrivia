#include <algorithm>
#include <random>
#include "Question.hpp"

std::default_random_engine Question::randomEngine = std::default_random_engine{ std::random_device{}() };

Question::Question() {}

std::string Question::getCategory() { return category; }

std::string Question::getType() { return type; }

std::string Question::getDifficulty() { return difficulty; }

std::string Question::getQuestion() { return question; }

std::string Question::getCorrectAnswer() { return correctAnswer; }

std::vector<std::string> Question::getIncorrectAnswers() { return incorrectAnswers; }

std::vector<std::string> Question::getAllPossibleAnswers() {
	std::vector<std::string> allPossibleAnswers{ incorrectAnswers };
	allPossibleAnswers.push_back(correctAnswer);
	std::shuffle(std::begin(allPossibleAnswers), std::end(allPossibleAnswers), randomEngine);
	return allPossibleAnswers;
}

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