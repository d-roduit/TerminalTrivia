#include "AsciiDisplayUtils.hpp"
#include <ftxui/dom/elements.hpp>
#include <sstream>

ftxui::Elements AsciiDisplayUtils::splitInTextElements(std::string asciiArtString) {
    ftxui::Elements textElements;
    std::stringstream stringstream(asciiArtString);
    std::string line;
    while (std::getline(stringstream, line, '\n')) {
        textElements.push_back(ftxui::text(line));
    }
    return textElements;
}

ftxui::Element AsciiDisplayUtils::asciiArt(std::string asciiArtString) {
    ftxui::Elements lines;
    for (ftxui::Element line: splitInTextElements(std::move(asciiArtString))) {
        lines.push_back(line);
    }
    return vbox(std::move(lines));
}