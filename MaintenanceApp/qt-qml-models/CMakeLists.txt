cmake_minimum_required(VERSION 3.1)

project(QtQmlModels)

find_package(Qt6 COMPONENTS Core Qml REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    QQmlObjectListModel.cpp
    QQmlVariantListModel.cpp
)

set(HEADERS
    QQmlObjectListModel.h
    QQmlVariantListModel.h
)

add_library(QtQmlModels STATIC ${SOURCES} ${HEADERS})

target_include_directories(QtQmlModels PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(QtQmlModels PRIVATE
    Qt6::Core
    Qt6::Qml
)
