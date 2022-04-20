#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/component_options.hpp"   // for ButtonOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/screen/color.hpp"  // for Color, Color::Blue, Color::Green, Color::Red
#include <ftxui/dom/elements.hpp>   // for filler, text, hbox, vbox
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include <thread>
#include <chrono>
#include <string>
#include "AsciiDisplayUtils.hpp"
#include "Question.hpp"
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
    ftxui::Component playButton = ftxui::Button("Play", [&] { renderPlay(0); });
    ftxui::Component settingsButton = ftxui::Button("Settings", [&] { renderSettings(); });
    ftxui::Component statsButton = ftxui::Button("Stats", [&] { renderStats(); });

    ftxui::Component navigationLayout = ftxui::Container::Vertical({
        playButton,
        settingsButton,
        statsButton
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

void TerminalTrivia::renderPlay(int questionIndex) {
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

    // Play State
    int mainNavigationSelectedButton{ 1 };

    // Question State
    std::vector<Question> questions{
        Question{ "12", "multiple", "easy", "What is 3 * 5 ?", "15", { "10", "12", "17"} },
        Question{ "12", "boolean", "medium", "Is 10 * 12 = 120 ?", "True", { "False" } },
        Question{ "12", "boolean", "medium", "Is 10 * 0.5 = 50 ?", "False", { "True" } },
        Question{ "13", "multiple", "medium", "How much do I love Thubidu ?", "With passion", { "A bit", "It's okay", "Much" } },
    };
    int selectedAnswerIndex{ -1 };
    bool hasUserAnswered{ false };
    bool isUserAnswerCorrect{ false };
    
    /* ---------------------------------------------------
    * Question component
    *--------------------------------------------------- */
    std::vector<ftxui::Component> answerButtons{};
    for (size_t answerIndex{ 0 }; answerIndex < questions[questionIndex].getAllPossibleAnswers().size(); answerIndex++) {
        answerButtons.push_back(ftxui::Button("(" + std::string(1, static_cast<char>(answerIndex + 97)) + ")  " + questions[questionIndex].getAllPossibleAnswers()[answerIndex], [
            this,
            &mainNavigationSelectedButton,
            &questions,
            &questionIndex,
            &selectedAnswerIndex,
            &hasUserAnswered,
            &isUserAnswerCorrect,
            answerIndex
        ] {
            if (!hasUserAnswered) {
                hasUserAnswered = true;
                selectedAnswerIndex = answerIndex;
                isUserAnswerCorrect = (answerIndex == questions[questionIndex].getCorrectAnswerIndex());
                stats.incrementNbAnsweredQuestions(isUserAnswerCorrect);
            }

            // It is always 2 because the "nextQuestionButton" component is index 2 in the "mainNavigationLayout" component.
            // The answer buttons are not taken into consideration in the "mainNavigationLayout" component.
            mainNavigationSelectedButton = 2;
        }));
    }

    ftxui::Component questionComponentNavigationLayout = ftxui::Container::Vertical(answerButtons);

    ftxui::Component questionComponentRenderer = ftxui::Renderer(questionComponentNavigationLayout, [
        answerButtons,
        &questions,
        &questionIndex,
        &selectedAnswerIndex,
        &hasUserAnswered,
        &isUserAnswerCorrect
    ]() {
        std::vector<ftxui::Element> renderedButtons{};

        if (!hasUserAnswered) {
            for (const ftxui::Component& answerButton : answerButtons) {
                renderedButtons.push_back(answerButton->Render());
            }
        }
        else {
            for (size_t answerIndex{ 0 }; answerIndex < answerButtons.size(); answerIndex++) {
                if (answerIndex == questions[questionIndex].getCorrectAnswerIndex()) {
                    renderedButtons.push_back(answerButtons[answerIndex]->Render() | ftxui::color(ftxui::Color::Green));
                    continue;
                }

                if (answerIndex == selectedAnswerIndex) {
                    renderedButtons.push_back(answerButtons[answerIndex]->Render() | ftxui::color(ftxui::Color::Red));
                    continue;
                }

                renderedButtons.push_back(answerButtons[answerIndex]->Render());
            }
        }

        return ftxui::vbox({
            ftxui::hbox({
                ftxui::text("Question:") | ftxui::bold | ftxui::color(ftxui::Color::Orange1),
                ftxui::separatorEmpty(),
                ftxui::separatorEmpty(),
                ftxui::separatorEmpty(),
                ftxui::text(questions[questionIndex].getQuestion()) | ftxui::bold | ftxui::color(ftxui::Color::Orange1),
            }),
            ftxui::separatorEmpty(),
            ftxui::vbox(renderedButtons),
            (hasUserAnswered && isUserAnswerCorrect) ? ftxui::text("Good answer!") | ftxui::color(ftxui::Color::Green) : ftxui::emptyElement(),
            (hasUserAnswered && !isUserAnswerCorrect) ? ftxui::text("Oh noo, you will have more chance next question!") | ftxui::color(ftxui::Color::Red) : ftxui::emptyElement(),
            ftxui::text("selectedAnswerIndex: " + std::to_string(selectedAnswerIndex)),
        });
    });

    /* ---------------------------------------------------
    * Play component
    *--------------------------------------------------- */
    ftxui::Component backButton = ftxui::Button(" Back to menu ", [this] { renderMenu(); });
    ftxui::Component nextQuestionButton = ftxui::Button(" Next question ", [this, &hasUserAnswered, &questionIndex, &questions] {
        if (!hasUserAnswered) return;

        if (questionIndex + 1 >= questions.size()) {
            questionIndex = 0;
        }
        else {
            questionIndex += 1;
        }

        renderPlay(questionIndex);
    });

    ftxui::Component mainNavigationLayout = ftxui::Container::Vertical({
        backButton,
        questionComponentNavigationLayout,
        nextQuestionButton,
    }, &mainNavigationSelectedButton);

    ftxui::Component mainRenderedLayout = ftxui::Renderer(mainNavigationLayout, [backButton, questionComponentRenderer, nextQuestionButton] {
        return ftxui::vbox({
            ftxui::hbox({
                backButton->Render(),
            }),
            ftxui::vbox({
                ftxui::hcenter(ftxui::text("Play") | ftxui::bold | ftxui::color(ftxui::Color::Blue)),
                ftxui::separatorEmpty(),
                questionComponentRenderer->Render(),
                ftxui::separatorEmpty(),
                ftxui::hbox({
                    nextQuestionButton->Render(),
                }),
            }),
        });
    });

    screen.Loop(mainRenderedLayout);
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
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

    // Components
    ftxui::Component backButton = ftxui::Button(" Back ", screen.ExitLoopClosure());

    ftxui::Component navigationLayout = ftxui::Container::Vertical({
        backButton,
    });

    ftxui::Component renderedLayout = ftxui::Renderer(navigationLayout, [&] {
        return ftxui::vbox({
            ftxui::hbox({
                backButton->Render(),
            }),
            ftxui::vbox({
                ftxui::hcenter(ftxui::text("Stats") | ftxui::bold | ftxui::color(ftxui::Color::Blue)),
                ftxui::hbox({
                    ftxui::vbox({
                        ftxui::text("Number of questions answered:"),
                        ftxui::text("Number of positive answers:"),
                        ftxui::text("Positive answers rate:"),
                    }),
                    ftxui::separatorEmpty(),
                    ftxui::separatorEmpty(),
                    ftxui::vbox({
                        ftxui::text(std::to_string(stats.getNbAnsweredQuestions())),
                        ftxui::text(std::to_string(stats.getNbPositiveAnswers())),
                        ftxui::text(std::to_string(stats.getPositiveAnswersRate()) + "%"),
                    }),
                }) | ftxui::border,
            }),
        });
    });

    screen.Loop(renderedLayout);
}
