#include <string>
#include <vector>
#include <map>
#include "Windows.h" // for PlaySound
#include "ftxui/component/component.hpp" // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp" // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Green, Color::Red
#include <ftxui/dom/elements.hpp> // for Elements, Element, filler, text, hbox, vbox
#include <ftxui/screen/screen.hpp> // for Screen
#include "AsciiDisplayUtils.hpp"
#include "Question.hpp"
#include "Settings.hpp"
#include "Stats.hpp"
#include "TriviaAPI.hpp"
#include "TerminalTrivia.hpp"

TerminalTrivia::TerminalTrivia() : settings(Settings::getInstance()), stats(Stats::getInstance()), triviaAPI(TriviaAPI::getInstance()) {
  
    // Set categories ids (=APIValue) and names (=Display) from API into settings
    // We must initialize the categoryAPIValueEntries and categoryDisplayEntries variables with the entry "Any Category"
    // because the fetched trivia categories strangely do not contain the basic "Any Category" entry.
    const std::map<int, std::string> categoriesMap{ triviaAPI.fetchCategories() };
    std::vector<int> categoryAPIValueEntries{ -1 };
    std::vector<std::string> categoryDisplayEntries{ "Any Category" };

    for (const auto& [categoryId, categoryName] : categoriesMap) {
        categoryAPIValueEntries.push_back(categoryId);
        categoryDisplayEntries.push_back(categoryName);
    }

    settings.setCategoryAPIValueEntries(categoryAPIValueEntries);
    settings.setCategoryDisplayEntries(categoryDisplayEntries);

    // Render the game menu
    renderMenu();
}

void TerminalTrivia::renderMenu() {
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

    // Game title
    std::string terminalTriviaAsciiArt = R"(
 _____                   _             _ _____     _       _       
|_   _|__ _ __ _ __ ___ (_)_ __   __ _| |_   _| __(_)_   ___) __ _ 
  | |/ _ \ '__| '_ ` _ \| | '_ \ / _` | | | || '__| \ \ / / |/ _` |
  | |  __/ |  | | | | | | | | | | (_| | | | || |  | |\ V /| | (_| |
  |_|\___|_|  |_| |_| |_|_|_| |_|\__,_|_| |_||_|  |_| \_/ |_|\__,_|
    )";

    // UI Components
    ftxui::Component playButton = ftxui::Button("Play", [&] { renderPlay(); });
    ftxui::Component settingsButton = ftxui::Button("Settings", [&] { renderSettings(); });
    ftxui::Component statsButton = ftxui::Button("Stats", [&] { renderStats(); });

    // Navigation Components
    ftxui::Component navigationLayout = ftxui::Container::Vertical({
        playButton,
        settingsButton,
        statsButton
    });

    // Components which will be rendered
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
    Question question{ triviaAPI.fetchQuestion(settings.getCategoryAPIValue(), settings.getTypeAPIValue(), settings.getDifficultyAPIValue()) };

    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

    // Play Component State
    int mainNavigationSelectedButton{ 1 }; // 1 always corresponds to the first button of the answer buttons

    // Question Component State
    int selectedAnswerIndex{ -1 };
    bool hasUserAnswered{ false };
    bool isUserAnswerCorrect{ false };
 
    /* ---------------------------------------------------
    * Question component
    *--------------------------------------------------- */
    // UI Components
    std::vector<ftxui::Component> answerButtons{};
    for (std::size_t answerIndex{ 0 }; answerIndex < question.getAllPossibleAnswers().size(); answerIndex++) {
        std::string buttonText = "(" + std::string(1, static_cast<char>(answerIndex + 97)) + ")  " + question.getAllPossibleAnswers()[answerIndex];

        auto buttonOnClick = [&, answerIndex] {
            if (!hasUserAnswered) {
                hasUserAnswered = true;
                selectedAnswerIndex = answerIndex;
                isUserAnswerCorrect = (answerIndex == question.getCorrectAnswerIndex());
                stats.incrementNbAnsweredQuestions(isUserAnswerCorrect);
                if (settings.areSoundEffectsEnabled()) {
                    const std::string soundFileName = (isUserAnswerCorrect) ? "answer_correct_sound.wav" : "answer_wrong_sound.wav";
                    PlaySound(TEXT(("sounds/" + soundFileName).c_str()), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
                }
            }

            // It is always 2 because the "nextQuestionButton" component is index 2 in the "mainNavigationLayout" component.
            // The answer buttons are not taken into consideration in the "mainNavigationLayout" component.
            mainNavigationSelectedButton = 2;
        };

        answerButtons.push_back(ftxui::Button(buttonText, buttonOnClick));
    }

    // Navigation Components
    ftxui::Component questionComponentNavigationLayout = ftxui::Container::Vertical(answerButtons);

    // Components which will be rendered
    ftxui::Component questionComponentRenderer = ftxui::Renderer(questionComponentNavigationLayout, [&]() {
        std::vector<ftxui::Element> renderedButtons{};

        if (!hasUserAnswered) {
            for (const ftxui::Component& answerButton : answerButtons) {
                renderedButtons.push_back(answerButton->Render());
            }
        }
        else {
            for (std::size_t answerIndex{ 0 }; answerIndex < answerButtons.size(); answerIndex++) {
                if (answerIndex == question.getCorrectAnswerIndex()) {
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
                ftxui::paragraph(question.getQuestion()) | ftxui::bold | ftxui::color(ftxui::Color::Orange1),
            }),
            ftxui::separatorEmpty(),
            ftxui::vbox(renderedButtons),
            (hasUserAnswered) ? ftxui::separatorEmpty() : ftxui::emptyElement(),
            (hasUserAnswered && isUserAnswerCorrect) ? ftxui::text("Good answer !") | ftxui::color(ftxui::Color::Green) : ftxui::emptyElement(),
            (hasUserAnswered && !isUserAnswerCorrect) ? ftxui::text("You will have better luck next question :)") | ftxui::color(ftxui::Color::Red) : ftxui::emptyElement(),
        });
    });

    /* ---------------------------------------------------
    * Play component
    *--------------------------------------------------- */
    // UI Components
    ftxui::Component backButton = ftxui::Button(" Back to menu ", [&] { renderMenu(); });
    ftxui::Component nextQuestionButton = ftxui::Button(" Next question ", [&] {
        if (!hasUserAnswered) return;
        renderPlay();
    });

    // Navigation Components
    ftxui::Component mainNavigationLayout = ftxui::Container::Vertical({
        backButton,
        questionComponentNavigationLayout,
    }, &mainNavigationSelectedButton);

    // Component which will be rendered
    ftxui::Component mainRenderedLayout = ftxui::Renderer(mainNavigationLayout, [&] {
        ftxui::Element nextQuestionButtonContainer{ ftxui::emptyElement() };
        
        // Add nextQuestionButton to the UI only if user has already answered
        if (hasUserAnswered) {
            mainNavigationLayout->Add(nextQuestionButton);
            nextQuestionButtonContainer = ftxui::vbox({
                ftxui::separatorEmpty(),
                ftxui::hbox({
                    nextQuestionButton->Render(),
                }),
            });
        }

        return ftxui::vbox({
            ftxui::hbox({
                backButton->Render(),
            }),
            ftxui::vbox({
                ftxui::hcenter(ftxui::text("Play") | ftxui::bold | ftxui::color(ftxui::Color::Blue)),
                ftxui::separatorEmpty(),
                questionComponentRenderer->Render(),
                nextQuestionButtonContainer,
            }),
        });
    });

    screen.Loop(mainRenderedLayout);
}

void TerminalTrivia::renderSettings() {
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

    // Tabs State
    std::vector<std::string> tabEntries{
        "Category",
        "Difficulty",
        "Type",
        "Sound Effects",
    };
    int selectedTab = 0;

    // UI Components
    ftxui::Component backButton = ftxui::Button(" Back ", screen.ExitLoopClosure());
    ftxui::Component categoryRadiobox = ftxui::Radiobox(&settings.getCategoryDisplayEntries(), &settings.selectedCategory);
    ftxui::Component difficultyRadiobox = ftxui::Radiobox(&settings.getDifficultyDisplayEntries(), &settings.selectedDifficulty);
    ftxui::Component typeRadiobox = ftxui::Radiobox(&settings.getTypeDisplayEntries(), &settings.selectedType);
    ftxui::Component soundEffectRadiobox = ftxui::Radiobox(&settings.getSoundEffectEntries(), &settings.selectedSoundEffect);
    ftxui::Component tabsToggle = ftxui::Toggle(&tabEntries, &selectedTab);
    ftxui::Component tabsContainer = ftxui::Container::Tab({
        categoryRadiobox,
        difficultyRadiobox,
        typeRadiobox,
        soundEffectRadiobox,
    }, &selectedTab);

    // Navigation Components
    ftxui::Component navigationLayout = ftxui::Container::Vertical({
        backButton,
        tabsToggle,
        tabsContainer
    });

    // Component which will be rendered
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
                    (selectedTab != 0) ? tabsContainer->Render() : tabsContainer->Render() | ftxui::vscroll_indicator | ftxui::frame,
                }) | ftxui::border,
            }),
        });
    });

    screen.Loop(renderedLayout);
}

void TerminalTrivia::renderStats() {
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

    // UI Components
    ftxui::Component backButton = ftxui::Button(" Back ", screen.ExitLoopClosure());

    // Navigation Components
    ftxui::Component navigationLayout = ftxui::Container::Vertical({
        backButton,
    });

    // Component which will be rendered
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
