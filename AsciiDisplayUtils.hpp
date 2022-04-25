#pragma once

#include <ftxui/dom/elements.hpp> // for Element, Elements
#include <string>

class AsciiDisplayUtils {
public:
    static ftxui::Element asciiArt(std::string asciiArtString);

private:
    AsciiDisplayUtils(); // Disallow creating an instance of this object
    static ftxui::Elements splitInTextElements(std::string asciiArtString);

};