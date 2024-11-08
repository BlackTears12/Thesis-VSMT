cmake_minimum_required(VERSION 3.14)

project(Guest LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET VSMT_Guest)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(COMMON_LIB_PATH ../common)

set(COMMON_SRC
    ${COMMON_LIB_PATH}/metrics.h
    ${COMMON_LIB_PATH}/metrics.cpp
    ${COMMON_LIB_PATH}/vsockmanager.cpp
    ${COMMON_LIB_PATH}/vsockmanager.h
    ${COMMON_LIB_PATH}/util.cpp
    ${COMMON_LIB_PATH}/util.h
    ${COMMON_LIB_PATH}/sockmanager.h
    ${COMMON_LIB_PATH}/sockmanager.cpp
)

set(GUEST_SRC
    src/main.cpp
    src/applicaton.h
    src/applicaton.cpp
)

add_executable(${TARGET}
  ${COMMON_SRC}
  ${GUEST_SRC}
)
target_link_libraries(${TARGET} Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
