cmake_minimum_required(VERSION 3.16)

project(Agenda VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

set(CMAKE_AUTORCC ON)
qt_add_executable(appAgenda
    main.cpp image.qrc icon.rc
)


qt_add_qml_module(appAgenda
    URI Agenda
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES ../express_manager/test/core/Agenda.cpp ../express_manager/test/core/Agenda.h ../express_manager/test/core/AgendaItem.cpp ../express_manager/test/core/AgendaItem.h ../express_manager/test/core/FileProcess.cpp ../express_manager/test/core/FileProcess.h
        SOURCES agendamanager.h agendamanager.cpp
        QML_FILES DatePicker.qml
        QML_FILES TimePicker.qml
        QML_FILES AgendaItemDelegate.qml
        QML_FILES StatCard.qml
        RESOURCES image.qrc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAgenda PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAgenda
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAgenda
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appAgenda
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)




