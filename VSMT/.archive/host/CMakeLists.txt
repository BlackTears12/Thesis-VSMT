cmake_minimum_required(VERSION 3.14)

project(host LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

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
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    clientdispatcher.h
    clientdispatcher.cpp
    clientstreamhandler.h
    clientstreamhandler.cpp
    responseparser.h
    responseparser.cpp
    model.h
    model.cpp
    controller.h
    controller.cpp
    main.cpp
)

set(PROJECT_SOURCES
    ${COMMON_SRC}
    ${HOST_SRC}
)

add_executable(${TARGET}
  ${PROJECT_SOURCES}
)

target_link_libraries(${TARGET} Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
