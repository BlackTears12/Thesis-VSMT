cmake_minimum_required(VERSION 3.14)

project(VSMT_Client LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

if(DEFINED yocto_deploy)
    set(COMMON_LIB_PATH src)
else()
    set(COMMON_LIB_PATH ../common)
endif()

include_directories(${COMMON_LIB_PATH})

set(COMMON_SRC
    ${COMMON_LIB_PATH}/platform.hpp

    ${COMMON_LIB_PATH}/metrics.hpp
    ${COMMON_LIB_PATH}/metrics.cpp
    ${COMMON_LIB_PATH}/util.cpp
    ${COMMON_LIB_PATH}/util.hpp
    ${COMMON_LIB_PATH}/vsocket.hpp
    ${COMMON_LIB_PATH}/vsocket.cpp
    ${COMMON_LIB_PATH}/metricserializer.hpp
    ${COMMON_LIB_PATH}/metricserializer.cpp
    ${COMMON_LIB_PATH}/resourcemonitor.hpp
    ${COMMON_LIB_PATH}/resourcemonitor_interface.hpp
    ${COMMON_LIB_PATH}/resourcemonitor_qnx.cpp
    ${COMMON_LIB_PATH}/vsockmessage.hpp
    ${COMMON_LIB_PATH}/vsockmessage.cpp
    ${COMMON_LIB_PATH}/clientconfiguration.hpp

    ${COMMON_LIB_PATH}/linux/resourcemonitor_linux.cpp
    ${COMMON_LIB_PATH}/linux/resourcemonitor_linux.hpp
    ${COMMON_LIB_PATH}/linux/sysfileparser.hpp
    ${COMMON_LIB_PATH}/linux/sysfileparser.cpp
    ${COMMON_LIB_PATH}/linux/commandutil.cpp
    ${COMMON_LIB_PATH}/linux/commandutil.hpp
)

set(GUEST_SRC
    src/main.cpp
    src/application.h
    src/application.cpp
    src/vsocksingletonserver.hpp
    src/vsocksingletonserver.cpp
)

add_executable(VSMT_Client
  ${COMMON_SRC}
  ${GUEST_SRC}
)

target_link_libraries(VSMT_Client Qt${QT_VERSION_MAJOR}::Core  Qt${QT_VERSION_MAJOR}::Network)

include(GNUInstallDirs)
install(TARGETS VSMT_Client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
