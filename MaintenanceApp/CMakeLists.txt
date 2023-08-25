cmake_minimum_required(VERSION 3.16)

project(MaintenanceApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Felgo REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)
add_subdirectory(qt-supermacros)
add_subdirectory(qt-qml-models)
add_library(qt-supermacros)
add_library(qt-qml-models)

set(PRODUCT_IDENTIFIER "com.fawkesengineering.MaintenanceApp")
set(PRODUCT_VERSION_NAME "1.0")
set(PRODUCT_VERSION_CODE 1)

set(PRODUCT_STAGE "test")

# Optionally set a license key that is used instead of the license key from
# main.qml file (App::licenseKey for your app or GameWindow::licenseKey for your game)
# Only used for local builds and Felgo Cloud Builds (https://felgo.com/cloud-builds)
# Not used if using Felgo Live
set(PRODUCT_LICENSE_KEY "")

file(GLOB_RECURSE QmlFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} qml/*.qml qml/*.js)
file(GLOB_RECURSE AssetsFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} assets/* qml/*)
list(REMOVE_ITEM AssetsFiles ${QmlFiles})

qt_add_executable(MaintenanceApp
	main.cpp
	CEosSerialMonitor.h CEosSerialMonitor.cpp
    ${QmlFiles}
    ${AssetsFiles}
)

felgo_configure_executable(MaintenanceApp)

# Deploy resources to build folder/package directly
# comment for publishing
#deploy_resources("${QmlFiles};${AssetsFiles}")

# Add QML files and resources to QML module to included them via QRC automatically:
qt_add_qml_module(MaintenanceApp
    URI BasicApp
    VERSION 1.0
# uncomment for publishing:
	QML_FILES ${QmlFiles}
	RESOURCES ${AssetsFiles}
    NO_RESOURCE_TARGET_PATH
)

enable_testing()

# NOTE: for PUBLISHING, perform the following steps:
# 1. comment the deploy_resources line above, to avoid shipping your qml files with the application (instead they get compiled to the app binary)
# 2. uncomment the QML_FILES and RESOURCES above; this compiles your qml files and js files to the app binary and protects your source code
# 3. change the setMainQmlFile() call in main.cpp to the one starting with "qrc:/" - this loads the qml files from the resources
# for more details see the "Deployment Guides" in the Felgo Documentation

# during development, use the deploy_resources because you then get shorter compilation times (the qml files do not need to be compiled to the binary but are just copied)
# also, for quickest deployment on Desktop disable the "Shadow Build" option in Projects/Builds - you can then select "Run Without Deployment" from the Build menu in Qt Creator if you only changed QML files; this speeds up application start, because your app is not copied & re-compiled but just re-interpreted

target_include_directories(MaintenanceApp PUBLIC
						  "${PROJECT_BINARY_DIR}"
						  "${PROJECT_SOURCE_DIR}/qt-supermacros"
						  "${PROJECT_SOURCE_DIR}/qt-qml-models"
						  )

target_compile_definitions(MaintenanceApp
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(MaintenanceApp PRIVATE Felgo QtSuperMacros QtQmlModels Qt6::SerialPort)

# uncomment this line to add the Live Client Module and use live reloading with your custom C++ code
# for the remaining steps to build a custom Live Code Reload app see here: https://felgo.com/custom-code-reload-app/
find_package(FelgoLive REQUIRED)
target_link_libraries(MaintenanceApp PRIVATE FelgoLive)
