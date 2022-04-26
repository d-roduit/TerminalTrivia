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
    {"&excl;", "!"},
    {"&quot;", "\""},
    {"&num;", "#"},
    {"&dollar;", "$"},
    {"&percnt;", "%"},
    {"&amp;", "&"},
    {"&apos;", "'"},
    {"&lpar;", "("},
    {"&rpar;", ")"},
    {"&ast;", "*"},
    {"&plus;", "+"},
    {"&comma;", ","},
    {"&period;", "."},
    {"&sol;", "/"},
    {"&bsol;", "\\"},
    {"&colon;", ":"},
    {"&semi;", ";"},
    {"&lt;", "<"},
    {"&equals;", "="},
    {"&gt;", ">"},
    {"&quest;", "?"},
    {"&commat;", "@"},
    {"&lsqb;", "["},
    {"&lbrack;", "["},
    {"&rsqb;", "]"},
    {"&rbrack;", "]"},
    {"&Hat;", "^"},
    {"&lowbar;", "_"},
    {"&grave;", "`"},
    {"&lcub;", "{"},
    {"&lbrace;", "{"},
    {"&verbar;", "|"},
    {"&vert;", "|"},
    {"&rcub;", "}"},
    {"&rbrace;", "}"},
    {"&iexcl;", "¡"},
    {"&cent;", "¢"},
    {"&pound;", "£"},
    {"&curren;", "¤"},
    {"&yen;", "¥"},
    {"&brvbar;", "¦"},
    {"&sect;", "§"},
    {"&Dot;", "¨"},
    {"&die;", "¨"},
    {"&DoubleDot;", "¨"},
    {"&uml;", "¨"},
    {"&copy;", "©"},
    {"&laquo;", "«"},
    {"&reg;", "®"},
    {"&circledR;", "®"},
    {"&macr;", "¯"},
    {"&OverBar;", "¯"},
    {"&strns;", "¯"},
    {"&deg;", "°"},
    {"&plusmn;", "±"},
    {"&pm;", "±"},
    {"&PlusMinus;", "±"},
    {"&acute;", "´"},
    {"&micro;", "µ"},
    {"&middot;", "·"},
    {"&cedil;", "¸"},
    {"&ordm;", "º"},
    {"&raquo;", "»"},
    {"&iquest;", "¿"},
    {"&Agrave;", "À"},
    {"&Aacute;", "Á"},
    {"&Acirc;", "Â"},
    {"&Atilde;", "Ã"},
    {"&Auml;", "Ä"},
    {"&Aring;", "Å"},
    {"&AElig;", "Æ"},
    {"&Ccedil;", "Ç"},
    {"&Egrave;", "È"},
    {"&Eacute;", "É"},
    {"&Ecirc;", "Ê"},
    {"&Euml;", "Ë"},
    {"&Igrave;", "Ì"},
    {"&Iacute;", "Í"},
    {"&Icirc;", "Î"},
    {"&Iuml;", "Ï"},
    {"&ETH;", "Ð"},
    {"&Ntilde;", "Ñ"},
    {"&Ograve;", "Ò"},
    {"&Oacute;", "Ó"},
    {"&Ocirc;", "Ô"},
    {"&Otilde;", "Õ"},
    {"&Ouml;", "Ö"},
    {"&times;", "×"},
    {"&Oslash;", "Ø"},
    {"&Ugrave;", "Ù"},
    {"&Uacute;", "Ú"},
    {"&Ucirc;", "Û"},
    {"&Uuml;", "Ü"},
    {"&Yacute;", "Ý"},
    {"&THORN;", "Þ"},
    {"&szlig;", "ß"},
    {"&agrave;", "à"},
    {"&aacute;", "á"},
    {"&acirc;", "â"},
    {"&atilde;", "ã"},
    {"&auml;", "ä"},
    {"&aring;", "å"},
    {"&aelig;", "æ"},
    {"&ccedil;", "ç"},
    {"&egrave;", "è"},
    {"&eacute;", "é"},
    {"&ecirc;", "ê"},
    {"&euml;", "ë"},
    {"&igrave;", "ì"},
    {"&iacute;", "í"},
    {"&icirc;", "î"},
    {"&iuml;", "ï"},
    {"&eth;", "ð"},
    {"&ntilde;", "ñ"},
    {"&ograve;", "ò"},
    {"&oacute;", "ó"},
    {"&ocirc;", "ô"},
    {"&otilde;", "õ"},
    {"&ouml;", "ö"},
    {"&divide;", "÷"},
    {"&oslash;", "ø"},
    {"&ugrave;", "ù"},
    {"&uacute;", "ú"},
    {"&ucirc;", "û"},
    {"&uuml;", "ü"},
    {"&yacute;", "ý"},
    {"&yuml;", "ÿ"},
    {"&Amacr;", "Ā"},
    {"&amacr;", "ā"},
    {"&Abreve;", "Ă"},
    {"&abreve;", "ă"},
    {"&Aogon;", "Ą"},
    {"&aogon;", "ą"},
    {"&Cacute;", "Ć"},
    {"&cacute;", "ć"},
    {"&Ccirc;", "Ĉ"},
    {"&ccirc;", "ĉ"},
    {"&Cdot;", "Ċ"},
    {"&cdot;", "ċ"},
    {"&Ccaron;", "Č"},
    {"&ccaron;", "č"},
    {"&Dcaron;", "Ď"},
    {"&dcaron;", "ď"},
    {"&Dstrok;", "Đ"},
    {"&dstrok;", "đ"},
    {"&Emacr;", "Ē"},
    {"&emacr;", "ē"},
    {"&Edot;", "Ė"},
    {"&edot;", "ė"},
    {"&Eogon;", "Ę"},
    {"&eogon;", "ę"},
    {"&Ecaron;", "Ě"},
    {"&ecaron;", "ě"},
    {"&Gcirc;", "Ĝ"},
    {"&gcirc;", "ĝ"},
    {"&Gbreve;", "Ğ"},
    {"&gbreve;", "ğ"},
    {"&Gdot;", "Ġ"},
    {"&gdot;", "ġ"},
    {"&Gcedil;", "Ģ"},
    {"&Hcirc;", "Ĥ"},
    {"&hcirc;", "ĥ"},
    {"&Hstrok;", "Ħ"},
    {"&hstrok;", "ħ"},
    {"&Itilde;", "Ĩ"},
    {"&itilde;", "ĩ"},
    {"&Imacr;", "Ī"},
    {"&imacr;", "ī"},
    {"&Iogon;", "Į"},
    {"&iogon;", "į"},
    {"&Idot;", "İ"},
    {"&IJlig;", "Ĳ"},
    {"&ijlig;", "ĳ"},
    {"&Jcirc;", "Ĵ"},
    {"&jcirc;", "ĵ"},
    {"&Kcedil;", "Ķ"},
    {"&kcedil;", "ķ"},
    {"&kgreen;", "ĸ"},
    {"&Lacute;", "Ĺ"},
    {"&lacute;", "ĺ"},
    {"&Lcedil;", "Ļ"},
    {"&lcedil;", "ļ"},
    {"&Lcaron;", "Ľ"},
    {"&lcaron;", "ľ"},
    {"&Nacute;", "Ń"},
    {"&nacute;", "ń"},
    {"&Ncedil;", "Ņ"},
    {"&ncedil;", "ņ"},
    {"&Ncaron;", "Ň"},
    {"&ncaron;", "ň"},
    {"&Omacr;", "Ō"},
    {"&omacr;", "ō"},
    {"&Odblac;", "Ő"},
    {"&odblac;", "ő"},
    {"&OElig;", "Œ"},
    {"&oelig;", "œ"},
    {"&Racute;", "Ŕ"},
    {"&racute;", "ŕ"},
    {"&Rcedil;", "Ŗ"},
    {"&rcedil;", "ŗ"},
    {"&Rcaron;", "Ř"},
    {"&rcaron;", "ř"},
    {"&Sacute;", "Ś"},
    {"&sacute;", "ś"},
    {"&Scirc;", "Ŝ"},
    {"&scirc;", "ŝ"},
    {"&Scedil;", "Ş"},
    {"&scedil;", "ş"},
    {"&Scaron;", "Š"},
    {"&scaron;", "š"},
    {"&Tcaron;", "Ť"},
    {"&Utilde;", "Ũ"},
    {"&utilde;", "ũ"},
    {"&Umacr;", "Ū"},
    {"&umacr;", "ū"},
    {"&Ubreve;", "Ŭ"},
    {"&ubreve;", "ŭ"},
    {"&Uring;", "Ů"},
    {"&uring;", "ů"},
    {"&Udblac;", "Ű"},
    {"&udblac;", "ű"},
    {"&Uogon;", "Ų"},
    {"&uogon;", "ų"},
    {"&Wcirc;", "Ŵ"},
    {"&wcirc;", "ŵ"},
    {"&Ycirc;", "Ŷ"},
    {"&ycirc;", "ŷ"},
    {"&Yuml;", "Ÿ"},
    {"&Zacute;", "Ź"},
    {"&zacute;", "ź"},
    {"&Zdot;", "Ż"},
    {"&zdot;", "ż"},
    {"&Zcaron;", "Ž"},
    {"&zcaron;", "ž"},
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