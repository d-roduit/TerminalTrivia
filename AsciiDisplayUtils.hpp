#pragma once

#include <ftxui/dom/elements.hpp> // for Element, Elements
#include <string>

/// @brief Utility class to help display ascii art correctly
class AsciiDisplayUtils {

public:
    /// @brief Returns the ascii art as a ftxui::vbox Element to display the ascii art correctly
    /// @param pAsciiArtString the ascii art string
    /// @return the ascii art as a ftxui::vbox Element containing ftxui::text Elements for each line of the ascii art
    static ftxui::Element asciiArt(std::string pAsciiArtString);

private:
    AsciiDisplayUtils(); // Disallow creating an instance of this object

    /// @brief Split an ascii art string in a vector of ftxui::text Element to display the ascii art correctly
    /// @param pAsciiArtString the ascii art string
    /// @return the ascii art as a vector of ftxui::text Element
    static ftxui::Elements splitInTextElements(std::string pAsciiArtString);

};