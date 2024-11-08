cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Host VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS QuickWidgets)
find_package(Qt6 REQUIRED COMPONENTS QCharts)

set(COMMON_LIB_PATH ../common)
set(TARGET VSMT_Host)

set(COMMON_SRC
    ${COMMON_LIB_PATH}/metrics.h
    ${COMMON_LIB_PATH}/metrics.cpp
    ${COMMON_LIB_PATH}/vsockmanager.cpp
    ${COMMON_LIB_PATH}/vsockmanager.h
    ${COMMON_LIB_PATH}/util.cpp
    ${COMMON_LIB_PATH}/util.h
)


set(HOST_SRC
    src/speedometer.qml
    src/ChartView.qml
    src/gaugewidget.h
    src/gaugewidget.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    src/mainwindow.ui
    src/clientdispatcher.h
    src/clientdispatcher.cpp
    src/clientstreamhandler.h
    src/clientstreamhandler.cpp
    src/responseparser.h
    src/responseparser.cpp
    src/model.h
    src/model.cpp
    src/controller.h
    src/controller.cpp
    src/main.cpp        
)

set(PROJECT_SOURCES
    ${COMMON_SRC}
    ${HOST_SRC}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VSMT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}        
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET VSMT APPEND src/ChartView.qml
#       PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${TARGET} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${TARGET}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(${TARGET} PRIVATE ${COMMON_LIB_PATH})
target_link_libraries(${TARGET} PRIVATE Qt5::QuickWidgets)
target_link_libraries(${TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VSMT)
endif()

set_target_properties(${TARGET} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${TARGET}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VSMT)
endif()
