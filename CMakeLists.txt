cmake_minimum_required (VERSION 3.8)

# Output the build of the libraries to the same folder as the executable
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

project ("TerminalTrivia")

# Add source for the executable
add_executable (TerminalTrivia "TerminalTrivia.cpp" "AsciiDisplayUtils.cpp"  "Stats.cpp" "Question.cpp" "APISettings.cpp")

include(FetchContent)

# --- Fetch FTXUI --------------------------------------------------------------
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG 81b7207121e41c3b838eca6f54396e4f676fa3d8
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
# ------------------------------------------------------------------------------

# --- Fetch json ---------------------------------------------------------------
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)
# ------------------------------------------------------------------------------

# --- Fetch cpr ----------------------------------------------------------------
FetchContent_Declare(cpr
	GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 6ea2dec23c3df14ac3b27b7d2d6bbff0cb7ba1b0
)
FetchContent_MakeAvailable(cpr)
# ------------------------------------------------------------------------------

target_link_libraries(TerminalTrivia
	PRIVATE nlohmann_json::nlohmann_json
	PRIVATE cpr::cpr
	PRIVATE ftxui::screen
	PRIVATE ftxui::dom
	PRIVATE ftxui::component
)