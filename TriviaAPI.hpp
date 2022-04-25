#pragma once

#include <map>
#include <string>
#include "Question.hpp"

class TriviaAPI {

public:

private:
    static std::string API_ENDPOINT_TOKEN;
    static std::string API_ENDPOINT_CATEGORIES;
    static std::string API_ENDPOINT_QUESTIONS;
    static std::map<std::string, std::string> HTML_ENTITIES_CONVERSION_TABLE;
    std::string sessionToken;

public:
    static TriviaAPI& getInstance();

    const std::map<int, std::string> fetchCategories() const;
    const Question fetchQuestion(int pCategoryId, std::string pType, std::string pDifficulty);

    TriviaAPI(TriviaAPI const&) = delete;
    void operator=(TriviaAPI const&) = delete;

private:
    TriviaAPI();
    void fetchSessionToken();
    void resetSessionToken() const;
    const std::string decodeHTMLEntities(std::string pString) const;
};