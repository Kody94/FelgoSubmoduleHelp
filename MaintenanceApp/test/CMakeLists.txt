cmake_minimum_required(VERSION 3.16)

project(Test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Test qml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Test qml)

enable_testing()





