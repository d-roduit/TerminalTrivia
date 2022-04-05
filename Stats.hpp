#pragma once

class Stats {

private:
    int nbAnsweredQuestions;
    int nbPositiveAnswers;

public:
    static Stats& getInstance();
    int getNbAnsweredQuestions();
    int getNbPositiveAnswers();
    int getPositiveAnswersRate();
    void incrementNbAnsweredQuestions(bool hasAnsweredCorrectly);
    Stats(Stats const&) = delete;
    void operator=(Stats const&) = delete;

private:
    Stats();
};