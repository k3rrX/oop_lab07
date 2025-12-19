cmake_minimum_required(VERSION 3.10)
project(Lab07_MultiThreadedGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Для Windows: настройка кодировки
if(WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE "/utf-8")
endif()

add_executable(lab07
    main.cpp
    npc.cpp
    game.cpp
)

target_include_directories(lab07 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Для поддержки std::shared_mutex (нужен C++17)
target_compile_features(lab07 PUBLIC cxx_std_17)