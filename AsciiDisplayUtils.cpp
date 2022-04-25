#include <ftxui/dom/elements.hpp> // for Elements, Element
#include <sstream> // for stringstream
#include "AsciiDisplayUtils.hpp"

ftxui::Element AsciiDisplayUtils::asciiArt(std::string pAsciiArtString) {
    ftxui::Elements lines;
    for (ftxui::Element line : splitInTextElements(std::move(pAsciiArtString))) {
        lines.push_back(line);
    }
    return vbox(std::move(lines));
}

ftxui::Elements AsciiDisplayUtils::splitInTextElements(std::string pAsciiArtString) {
    ftxui::Elements textElements;
    std::stringstream stringstream{ pAsciiArtString };
    std::string line;
    while (std::getline(stringstream, line, '\n')) {
        textElements.push_back(ftxui::text(line));
    }
    return textElements;
}