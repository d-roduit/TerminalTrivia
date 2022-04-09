#pragma once

class Stats {

private:
    int nbAnsweredQuestions;
    int nbPositiveAnswers;

public:
    static Stats& getInstance();
    int getNbAnsweredQuestions() const;
    int getNbPositiveAnswers() const;
    int getPositiveAnswersRate() const;
    void incrementNbAnsweredQuestions(bool hasAnsweredCorrectly);

    Stats(Stats const&) = delete;
    void operator=(Stats const&) = delete;

private:
    Stats();
};