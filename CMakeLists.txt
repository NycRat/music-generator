cmake_minimum_required(VERSION 3.10)
project(MusicGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.6.0 COMPONENTS system window graphics network audio REQUIRED)

add_executable(MusicGenerator 
  App.cpp
  AudioGenerator.cpp
  AudioPlayerUI.cpp
  Button.cpp
  main.cpp
  SettingsUI.cpp
  VisualAudio.cpp
)

# Include SFML headers
target_include_directories(MusicGenerator PRIVATE ${SFML_INCLUDE_DIR})

# Link SFML libraries
target_link_libraries(MusicGenerator PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
