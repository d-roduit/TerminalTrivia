#include <math.h>       /* round */
#include "Stats.hpp"

Stats& Stats::getInstance() {
	static Stats instance;
	return instance;
}

Stats::Stats() {
	nbAnsweredQuestions = 0;
	nbPositiveAnswers = 0;
}

int Stats::getNbAnsweredQuestions() {
	return nbAnsweredQuestions;
}

int Stats::getNbPositiveAnswers() {
	return nbPositiveAnswers;
}

int Stats::getPositiveAnswersRate() {
	if (nbAnsweredQuestions == 0) return 0;
	return (int)round((nbPositiveAnswers / (double)nbAnsweredQuestions) * 100);
}

void Stats::incrementNbAnsweredQuestions(bool hasAnsweredCorrectly) {
	nbAnsweredQuestions++;
	if (hasAnsweredCorrectly) nbPositiveAnswers++;
}
