/*
* This file is encoded as "Unicode (UTF-8 with signature) - Code Page 65001" to support the characters in the HTML_ENTITIES_CONVERSION_TABLE.
* All other projects files are endoded as "Occidental alphabet (Windows) - Code Page 1252"
*/

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "Question.hpp"
#include "TriviaAPI.hpp"

std::string TriviaAPI::API_ENDPOINT_TOKEN{ "https://opentdb.com/api_token.php" };
std::string TriviaAPI::API_ENDPOINT_CATEGORIES{ "https://opentdb.com/api_category.php" };
std::string TriviaAPI::API_ENDPOINT_QUESTIONS{ "https://opentdb.com/api.php" };

std::map<std::string, std::string> TriviaAPI::HTML_ENTITIES_CONVERSION_TABLE{
    {"&#039;", "'"},
    {"&quot;", "\""},
    {"&amp;", "&"},
    {"&apos;", "'"},
    {"&lt;", "<"},
    {"&gt;", ">"},
    {"&acirc;", "â"},
    {"&agrave;", "à"},
    {"&eacute;", "é"},
    {"&ecirc;", "ê"},
    {"&egrave;", "è"},
    {"&euml;", "ë"},
    {"&icirc;", "î"},
    {"&iuml;", "ï"},
    {"&ocirc;", "ô"},
    {"&ucirc;", "û"},
    {"&ugrave;", "ù"},
    {"&uuml;", "ü"},
    {"&Acirc;", "Â"},
    {"&Agrave;", "À"},
    {"&Eacute;", "É"},
    {"&Ecirc;", "Ê"},
    {"&Egrave;", "È"},
    {"&Euml;", "Ë"},
    {"&Icirc;", "Î"},
    {"&Iuml;", "Ï"},
    {"&Ocirc;", "Ô"},
    {"&Ucirc;", "Û"},
    {"&Ugrave;", "Ù"},
    {"&Uuml;", "Ü"},
    {"&oelig;", "œ"},
    {"&ccedil;", "ç"},
    {"&szlig;", "ß"},
    {"&Oslash;", "Ø"},
};

TriviaAPI& TriviaAPI::getInstance() {
    static TriviaAPI instance;
    return instance;
}

TriviaAPI::TriviaAPI() {
    fetchSessionToken();
}

const std::map<int, std::string> TriviaAPI::fetchCategories() const {
    cpr::Response response = cpr::Get(cpr::Url{ API_ENDPOINT_CATEGORIES });

    std::map<int, std::string> categoriesMap{};

    if (response.status_code == 200 && response.header["content-type"] == "application/json") {
        nlohmann::json categoriesAsJSON = nlohmann::json::parse(response.text);

        if (categoriesAsJSON.contains("trivia_categories") && categoriesAsJSON["trivia_categories"].is_array()) {
            for (nlohmann::json category : categoriesAsJSON["trivia_categories"]) {
                if (!category.contains("id") || !category.contains("name") || !category["id"].is_number_integer() || !category["name"].is_string()) {
                    continue;
                }
                categoriesMap.insert({category["id"].get<int>(), category["name"].get<std::string>()});
            }
        }
    }

    return categoriesMap;
}

const Question TriviaAPI::fetchQuestion(int pCategoryId, std::string pType, std::string pDifficulty) {
    cpr::Parameters requestParameters{
        {"amount", "1"},
        {"token", sessionToken},
    };
    
    if (pCategoryId != -1) requestParameters.Add({"category", std::to_string(pCategoryId)});
    if (pType != "") requestParameters.Add({"type", pType});
    if (pDifficulty != "") requestParameters.Add({"difficulty", pDifficulty});

    cpr::Response response = cpr::Get(cpr::Url{ API_ENDPOINT_QUESTIONS }, requestParameters);

    if (response.status_code == 200 && response.header["content-type"] == "application/json") {
        nlohmann::json questionAsJSON = nlohmann::json::parse(response.text);
        
        Question question{ "Any Category", "multiple", "medium", "What is the firstname of the creator of TerminalTrivia ?", "Daniel", {"Dave", "David", "Dan"} };

        if (questionAsJSON.contains("response_code") && questionAsJSON["response_code"].is_number_integer()) {
            switch (questionAsJSON["response_code"].get<int>()) {
                case 0:
                    if (questionAsJSON.contains("results") && questionAsJSON["results"].is_array() && questionAsJSON["results"].size() > 0) {
                        const std::string category = questionAsJSON["results"][0]["category"].get<std::string>();
                        const std::string correct_answer = decodeHTMLEntities(questionAsJSON["results"][0]["correct_answer"].get<std::string>());
                        const std::string difficulty = questionAsJSON["results"][0]["difficulty"].get<std::string>();
                        const std::string questionText = decodeHTMLEntities(questionAsJSON["results"][0]["question"].get<std::string>());
                        const std::string type = questionAsJSON["results"][0]["type"].get<std::string>();
                        std::vector<std::string> incorrect_answers = questionAsJSON["results"][0]["incorrect_answers"].get<std::vector<std::string>>();
                        
                        for (std::string& answer : incorrect_answers) {
                            answer = decodeHTMLEntities(answer);
                        }

                        question = Question{ category, type, difficulty, questionText, correct_answer, incorrect_answers };
                    }
                    break;
                case 3:
                    fetchSessionToken();
                    question = fetchQuestion(pCategoryId, pType, pDifficulty);
                    break;
                case 4:
                    resetSessionToken();
                    question = fetchQuestion(pCategoryId, pType, pDifficulty);
                    break;
            }
        }

        return question;
    }
}

void TriviaAPI::fetchSessionToken() {
    cpr::Response response = cpr::Get(
        cpr::Url{ API_ENDPOINT_TOKEN },
        cpr::Parameters{
            {"command", "request"},
        }
    );

    if (response.status_code == 200 && response.header["content-type"] == "application/json") {
        nlohmann::json sessionTokenAsJSON = nlohmann::json::parse(response.text);
        if (sessionTokenAsJSON.contains("token") && sessionTokenAsJSON["token"].is_string()) {
            sessionToken = sessionTokenAsJSON["token"];
        }
    }
}

void TriviaAPI::resetSessionToken() const {
    cpr::Get(
        cpr::Url{ API_ENDPOINT_TOKEN },
        cpr::Parameters{
            {"command", "reset"},
            {"token", sessionToken},
        }
    );
}

const std::string TriviaAPI::decodeHTMLEntities(std::string pString) const {
    std::ostringstream oss;
    std::size_t position{ 0 };
    std::size_t previousPosition{ position };

    for (auto& [HTMLEntity, decodedCharacter] : HTML_ENTITIES_CONVERSION_TABLE) {
        while (true) {
            previousPosition = position;
            position = pString.find(HTMLEntity, position);
            if (position == std::string::npos) {
                break;
            }
            oss << pString.substr(previousPosition, position - previousPosition);
            oss << decodedCharacter;
            position += HTMLEntity.size();
        }
        oss << pString.substr(previousPosition);
        pString = oss.str();
        oss.str(""); // Reset the string stream
        position = 0;
    }

    return pString;
}