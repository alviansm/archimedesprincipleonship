cmake_minimum_required(VERSION 3.16)

project(ArchimedesPrincipleOnShip VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# Translation
set(TS_FILES translations/ArchimedesPrincipleOnShip_en_US.ts)

# Source groups
file(GLOB_RECURSE SRC_FILES
    src/app/*.cpp src/app/*.h
    src/ui/*.cpp src/ui/*.h src/ui/*.ui
    src/widgets/*.cpp src/widgets/*.h
    src/utils/*.cpp src/utils/*.h
)

set(PROJECT_SOURCES
    main.cpp
    ${SRC_FILES}
    ${TS_FILES}
)

# Add executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ArchimedesPrincipleOnShip
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(ArchimedesPrincipleOnShip ${PROJECT_SOURCES})
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# Link Qt libraries
target_link_libraries(ArchimedesPrincipleOnShip PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# macOS bundle metadata
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ArchimedesPrincipleOnShip)
endif()

set_target_properties(ArchimedesPrincipleOnShip PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Installation
include(GNUInstallDirs)
install(TARGETS ArchimedesPrincipleOnShip
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ArchimedesPrincipleOnShip)
endif()
