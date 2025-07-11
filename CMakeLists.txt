cmake_minimum_required(VERSION 3.16)

project(QClassic VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

set(PROJECT_SOURCES
  Main.cpp
        MainWindow.cpp
        MainWindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QClassic
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Piece.h Piece.cpp

        Library.h Library.cpp
        PlayerBar.h PlayerBar.cpp
        SideBar.h SideBar.cpp

        MenuBar.h MenuBar.cpp
        QClassic.qrc
        Playlist.h Playlist.cpp
        IPieceView.h IPieceView.cpp
        TreeView.h TreeView.cpp

        Styles.qss
        AppData.h AppData.cpp
        Identifiable.h Identifiable.cpp
        LibraryView.h LibraryView.cpp
        QueueView.h QueueView.cpp

        IPieceList.h IPieceList.cpp
        PieceEditor.h PieceEditor.cpp
        Playback.h Playback.cpp
        PieceMenu.h PieceMenu.cpp
        PieceViewType.h PieceViewType.cpp





    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QClassic APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QClassic SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QClassic
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set_source_files_properties(macosmedia.mm PROPERTIES
    COMPILE_FLAGS "-fobjc-arc"
    LANGUAGE OBJCXX
)

target_link_libraries(QClassic PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Multimedia
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QClassic)
endif()
set_target_properties(QClassic PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QClassic
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QClassic)
endif()
