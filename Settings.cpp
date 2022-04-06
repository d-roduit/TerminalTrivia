#include "Settings.hpp"

Settings& Settings::getInstance() {
	static Settings instance;
	return instance;
}

Settings::Settings() {
	difficulty = "";
	type = "";
	category = -1;
}

int Settings::getCategory() {
	return category;
}

std::string Settings::getDifficulty() {
	return difficulty;
}

std::string Settings::getType() {
	return type;
}

int Settings::getAmount() {
	return amount;
}

void Settings::setCategory(int pCategory) {
	category = pCategory;
}

void Settings::setDifficulty(std::string pDifficulty) {
	difficulty = pDifficulty;
}

void Settings::setType(std::string pType) {
	type = pType;
}