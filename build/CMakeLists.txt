cmake_minimum_required(VERSION 3.5)

project(CryliaPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Qml Svg Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Qml Svg Core)

find_package(SDL2 REQUIRED)
find_library(SDL_MIXER_LIBRARY
    NAMES SDL2_mixer
    HINTS
    ENV SDLMIXERDIR
    ENV SDLDIR
    PATH_SUFFIXES lib
)
find_library(SDL_IMAGE_LIBRARY
    NAMES SDL2_image
    HINTS
    ENV SDLIMAGEDIR
    ENV SDLDIR
    PATH_SUFFIXES lib
)

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

set(PROJECT_SOURCES
    ../src/main.cpp
    ../src/core/audio/audio.cpp
    ../src/Public/MainWindow.cpp
    ../src/Public/Modules/FloatingControls/FloatingControls.cpp
    ../src/Public/Pages/pages.cpp
    ../src/Public/Pages/Playlist/PlaylistPage.cpp
    ../src/Public/Widgets/Playlist/PlaylistWidget.cpp
    ../src/Public/Layouts/QOverlayout.cpp
)

set(PROJECT_HEADERS
    ../src/core/audio/audio.h
    ../src/Public/MainWindow.h
    ../src/Public/Modules/FloatingControls/FloatingControls.h
    ../src/Public/Pages/pages.h
    ../src/Public/Pages/Playlist/PlaylistPage.h
    ../src/Public/Widgets/Playlist/PlaylistWidget.h
    ../src/Public/Layouts/QOverlayout.h
)

set(PROJECT_RESOURCES
    ../assets/resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CryliaPlayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_RESOURCES}
    )
else()
    if(ANDROID)
        add_library(CryliaPlayer SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_RESOURCES}
        )
    else()
        add_executable(CryliaPlayer
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_RESOURCES}
        )
    endif()
endif()

target_link_libraries(CryliaPlayer PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::Core
    ${SDL2_LIBRARIES}
    ${SDL_IMAGE_LIBRARY}
    ${SDL_MIXER_LIBRARY}
    PkgConfig::LIBAV
)

# set_target_properties(CryliaPlayer PROPERTIES
# MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
# MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
# MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
# MACOSX_BUNDLE TRUE
# WIN32_EXECUTABLE TRUE
# )
install(TARGETS CryliaPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CryliaPlayer)
endif()
