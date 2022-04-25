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

int Stats::getNbAnsweredQuestions() const {
	return nbAnsweredQuestions;
}

int Stats::getNbPositiveAnswers() const {
	return nbPositiveAnswers;
}

int Stats::getPositiveAnswersRate() const {
	if (nbAnsweredQuestions == 0) return 0;
	return (int)round((nbPositiveAnswers / (double)nbAnsweredQuestions) * 100);
}

void Stats::incrementNbAnsweredQuestions(bool pHasAnsweredCorrectly) {
	nbAnsweredQuestions++;
	if (pHasAnsweredCorrectly) nbPositiveAnswers++;
}
