#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/component_options.hpp"   // for ButtonOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/screen/color.hpp"  // for Color, Color::Blue, Color::Green, Color::Red
#include <ftxui/dom/elements.hpp>   // for filler, text, hbox, vbox
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include "AsciiDisplayUtils.hpp"
#include <string>
#include "TerminalTrivia.hpp"

TerminalTrivia::TerminalTrivia() : settings(Settings::getInstance()), stats(Stats::getInstance()) {
    renderMenu();
}

void TerminalTrivia::renderMenu() {
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

    std::string terminalTriviaAsciiArt = R"(
 _____                   _             _ _____     _       _       
|_   _|__ _ __ _ __ ___ (_)_ __   __ _| |_   _| __(_)_   ___) __ _ 
  | |/ _ \ '__| '_ ` _ \| | '_ \ / _` | | | || '__| \ \ / / |/ _` |
  | |  __/ |  | | | | | | | | | | (_| | | | || |  | |\ V /| | (_| |
  |_|\___|_|  |_| |_| |_|_|_| |_|\__,_|_| |_||_|  |_| \_/ |_|\__,_|
    )";

    // Components
    ftxui::Component playButton = ftxui::Button("Play", [&] {});
    ftxui::Component settingsButton = ftxui::Button("Settings", [&] { renderSettings(); });
    ftxui::Component statsButton = ftxui::Button("Stats", [&] {});
    ftxui::Component quitButton = ftxui::Button("Quit", screen.ExitLoopClosure());

    ftxui::Component navigationLayout = ftxui::Container::Vertical({
        playButton,
        settingsButton,
        statsButton,
        quitButton
    });

    ftxui::Component renderedLayout = ftxui::Renderer(navigationLayout, [&] {
        return ftxui::vbox({
            ftxui::filler(),
            ftxui::hbox({
                ftxui::filler(),
                ftxui::vbox({
                    AsciiDisplayUtils::asciiArt(terminalTriviaAsciiArt) | ftxui::color(ftxui::Color::Blue),
                    ftxui::vbox({
                        ftxui::borderEmpty(navigationLayout->Render()),
                    }),
                }),
                ftxui::filler(),
            }),
            ftxui::filler(),
        });
    });

    screen.Loop(renderedLayout);
}

void TerminalTrivia::renderPlay() {

}

void TerminalTrivia::renderSettings() {
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

    std::vector<std::string> tabEntries{
        "Category",
        "Difficulty",
        "Type",
    };
    int selectedTab = 0;

    // Components
    ftxui::Component backButton = ftxui::Button(" Back ", screen.ExitLoopClosure());
    ftxui::Component categoryRadiobox = ftxui::Radiobox(&settings.getCategoryNameEntries(), &settings.selectedCategory);
    ftxui::Component difficultyRadiobox = ftxui::Radiobox(&settings.getDifficultyEntries(), &settings.selectedDifficulty);
    ftxui::Component typeRadiobox = ftxui::Radiobox(&settings.getTypeEntries(), &settings.selectedType);
    ftxui::Component tabsToggle = ftxui::Toggle(&tabEntries, &selectedTab);
    ftxui::Component tabsContainer = ftxui::Container::Tab({
        categoryRadiobox,
        difficultyRadiobox,
        typeRadiobox,
    }, &selectedTab);

    ftxui::Component navigationLayout = ftxui::Container::Vertical({
        backButton,
        tabsToggle,
        tabsContainer
    });

    ftxui::Component renderedLayout = ftxui::Renderer(navigationLayout, [&] {
        return ftxui::vbox({
            ftxui::hbox({
                backButton->Render(),
            }),
            ftxui::vbox({
                ftxui::hcenter(ftxui::text("Settings") | ftxui::bold | ftxui::color(ftxui::Color::Blue)),
                ftxui::vbox({
                    tabsToggle->Render(),
                    ftxui::separator(),
                    tabsContainer->Render(),
                }) | ftxui::border,
            }),
        });
    });

    screen.Loop(renderedLayout);
}

void TerminalTrivia::renderStats() {

}
