cmake_minimum_required(VERSION 3.19)
project(pong LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(pong
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    menu.h menu.cpp menu.ui
    test.h test.cpp test.ui
    chart.h chart.cpp
    ponging.h ponging.cpp
    connection.h connection.cpp
    qcustomplot.h qcustomplot.cpp
    resources.qrc
)

qt_add_translations(pong TS_FILES pong_pl_PL.ts)

qt_add_translations(
    TARGETS pong
    TS_FILES pong_en_US.ts
)
find_package(Qt6 REQUIRED COMPONENTS Core SerialPort PrintSupport Widgets)

target_link_libraries(pong
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::SerialPort
        Qt6::PrintSupport
)

include(GNUInstallDirs)

install(TARGETS pong
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET pong
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
