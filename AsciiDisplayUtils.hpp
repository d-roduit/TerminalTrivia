#pragma once

#include <ftxui/dom/elements.hpp>

class AsciiDisplayUtils {
public:
    static ftxui::Element asciiArt(std::string asciiArtString);

private:
    // Disallow creating an instance of this object
    AsciiDisplayUtils();
    static ftxui::Elements splitInTextElements(std::string asciiArtString);
};