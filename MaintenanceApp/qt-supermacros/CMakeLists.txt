cmake_minimum_required(VERSION 3.1)

project(QtSuperMacros)

find_package(Qt6 COMPONENTS Core Qml REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    QQmlHelpers.cpp
)

set(HEADERS
    QQmlVarPropertyHelpers.h
    QQmlPtrPropertyHelpers.h
    QQmlEnumClassHelper.h
    QQmlConstRefPropertyHelpers.h
    QQmlListPropertyHelper.h
    QQmlAutoPropertyHelpers.h
    QQmlHelpersCommon.h
)

set(DISTFILES
    README.md
    LICENSE.md
)

add_library(QtSuperMacros STATIC ${SOURCES} ${HEADERS} ${DISTFILES})

target_include_directories(QtSuperMacros PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(QtSuperMacros PRIVATE
    Qt6::Core
    Qt6::Qml
)
