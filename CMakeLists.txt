cmake_minimum_required(VERSION 3.28)
project(llfcchat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "E:/Tools/Qt/6.5.3/mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

set(QRC_SOURCE_FILE Resources/rc.qrc)
qt_add_resources(${QRC_SOURCE_FILE})

include_directories(
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/Sources/Headers
)
add_executable(llfcchat Sources/main.cpp
        Sources/logindialog.cpp
        Sources/Headers/logindialog.h
        Sources/Forms/logindialog.ui
        Sources/mainwindow.cpp
        Sources/Headers/mainwindow.h
        Sources/Forms/mainwindow.ui
        ${QRC_SOURCE_FILE}
        Sources/registerdialog.cpp
        Sources/Headers/registerdialog.h
        Sources/Forms/registerdialog.ui
        Sources/Headers/global.h
        Sources/global.cpp
        Sources/Headers/singleton.hpp
        Sources/HttpManager.cpp
        Sources/Headers/HttpManager.h
        Sources/timerbutton.cpp
        Sources/Headers/timerbutton.h
)
target_link_libraries(llfcchat
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)

endif ()
