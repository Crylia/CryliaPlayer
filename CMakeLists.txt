cmake_minimum_required(VERSION 3.5)

project(CryliaPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Qml Svg Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Qml Svg Core Sql)

find_package(SDL2 QUIET)

if(NOT SDL2_FOUND)
    message(STATUS "SDL2 not found. Fallback to SDL3.")

    # Find SDL3 package
    find_package(SDL3 REQUIRED CONFIG)
    set(SDL_INCLUDE_DIRS ${SDL3_INCLUDE_DIRS})
    set(SDL_LIBRARIES ${SDL3_LIBRARIES})
else()
    message(STATUS "SDL2 found.")
    set(SDL_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})
    set(SDL_LIBRARIES ${SDL2_LIBRARIES})
endif()

find_library(SDL_MIXER_LIBRARY NAMES SDL2_mixer SDL3_mixer)
include_directories(${SDL_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavdevice
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS src/*.h)
file(GLOB_RECURSE PROJECT_RESOURCES assets/resources.qrc)

add_executable(CryliaPlayer
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_RESOURCES}
)

target_link_libraries(CryliaPlayer PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Sql
    ${SDL_LIBRARIES}
    ${SDL_MIXER_LIBRARY}
    PkgConfig::LIBAV
    fmt
)

install(TARGETS CryliaPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(DESKTOP_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/CryliaPlayer.desktop.in)
set(DESKTOP_FILE ${CMAKE_CURRENT_BINARY_DIR}/CryliaPlayer.desktop)

configure_file(${DESKTOP_FILE_IN} ${DESKTOP_FILE} @ONLY)

install(FILES ${DESKTOP_FILE} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES assets/aqua.jpg DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons)
