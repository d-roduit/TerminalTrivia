#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/component_options.hpp"   // for ButtonOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/screen/color.hpp"  // for Color, Color::Blue, Color::Green, Color::Red
#include <ftxui/dom/elements.hpp>   // for filler, text, hbox, vbox
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include "AsciiDisplayUtils.hpp"
#include <memory>                   // for allocator
#include <string>
#include <iostream>
#include <sstream>

int main() {
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

    auto settings = [] {
        ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
        ftxui::Component settings = ftxui::Container::Vertical({
            ftxui::Button("Back", screen.ExitLoopClosure())
        });
        screen.Loop(settings);
    };

    ftxui::Component menu = ftxui::Container::Vertical({
        ftxui::Button("Play", [&] { }),
        ftxui::Button("Settings", settings),
        ftxui::Button("Stats", [&] {}),
        ftxui::Button("Quit", screen.ExitLoopClosure())
    });

    std::string terminalTriviaAsciiArt = R"(
 _____                   _             _ _____     _       _       
|_   _|__ _ __ _ __ ___ (_)_ __   __ _| |_   _| __(_)_   ___) __ _ 
  | |/ _ \ '__| '_ ` _ \| | '_ \ / _` | | | || '__| \ \ / / |/ _` |
  | |  __/ |  | | | | | | | | | | (_| | | | || |  | |\ V /| | (_| |
  |_|\___|_|  |_| |_| |_|_|_| |_|\__,_|_| |_||_|  |_| \_/ |_|\__,_|
    )";

    ftxui::Component document = ftxui::Renderer(menu, [&] {
        return ftxui::vbox({
            ftxui::hbox(),
            ftxui::filler(),
            ftxui::hbox({
                ftxui::filler(),
                ftxui::vbox({
                    AsciiDisplayUtils::asciiArt(terminalTriviaAsciiArt) | ftxui::color(ftxui::Color::Blue),
                    ftxui::vbox(
                        ftxui::borderEmpty(menu->Render())
                    )
                }),
                ftxui::filler()
            }),
            ftxui::filler(),
            ftxui::hbox(),
        });
    });

    screen.Loop(document);
    return 0;
}