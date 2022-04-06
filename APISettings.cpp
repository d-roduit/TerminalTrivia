#include "APISettings.hpp"

APISettings& APISettings::getInstance() {
	static APISettings instance;
	return instance;
}

APISettings::APISettings() {
	difficulty = "";
	type = "";
	category = -1;
}

std::string APISettings::getDifficulty() {
	return difficulty;
}

std::string APISettings::getType() {
	return type;
}

int APISettings::getCategory() {
	return category;
}

int APISettings::getAmount() {
	return amount;
}

void APISettings::setDifficulty(std::string pDifficulty) {
	difficulty = pDifficulty;
}

void APISettings::setType(std::string pType) {
	type = pType;
}

void APISettings::setCategory(int pCategory) {
	category = pCategory;
}