cmake_minimum_required(VERSION 3.5)

project(CryliaPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Qml Svg Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Qml Svg Core)

set(PROJECT_SOURCES
    ../src/main.cpp
    ../src/Public/MainWindow.cpp
    ../src/Public/Modules/FloatingControls/FloatingControls.cpp
    ../src/Public/Pages/pages.cpp
    ../src/Public/Pages/Playlist/PlaylistPage.cpp
    ../src/Public/Widgets/Playlist/PlaylistWidget.cpp
    ../src/Public/Layouts/QOverlayout.cpp
)

set(PROJECT_HEADERS
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

qt5_add_resources(PROJECT_SOURCES ${PROJECT_RESOURCES})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CryliaPlayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_RESOURCES}
    )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET CryliaPlayer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CryliaPlayer SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_RESOURCES}
        )

    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CryliaPlayer
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_RESOURCES}
        )
    endif()
endif()

target_link_libraries(CryliaPlayer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::Qml PRIVATE Qt${QT_VERSION_MAJOR}::Svg PRIVATE Qt${QT_VERSION_MAJOR}::Core)

set_target_properties(CryliaPlayer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS CryliaPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CryliaPlayer)
endif()
