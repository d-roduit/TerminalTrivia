#include "APISettings.hpp"

APISettings& APISettings::getInstance() {
	static APISettings instance;
	return instance;
}

APISettings::APISettings() {
	difficulty = 0;
	type = 0;
	category = 0;
}

int APISettings::getDifficulty() {
	return difficulty;
}

int APISettings::getType() {
	return type;
}

int APISettings::getCategory() {
	return category;
}

int APISettings::getAmount() {
	return amount;
}

void APISettings::setDifficulty(int pDifficulty) {
	difficulty = pDifficulty;
}

void APISettings::setType(int pType) {
	type = pType;
}

void APISettings::setCategory(int pCategory) {
	category = pCategory;
}