cmake_minimum_required(VERSION 3.16)

project(VSMT_Hyp_Gateway LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

if(DEFINED yocto_deploy)
    set(COMMON_LIB_PATH src)
    set(HYP_SHARED_PATH src)
else()
    set(COMMON_LIB_PATH ../common)
    set(HYP_SHARED_PATH ../VSMT_Hyp_Shared)
endif()

include_directories(${COMMON_LIB_PATH} ${HYP_SHARED_PATH})

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
    ${COMMON_LIB_PATH}/qnx/resourcemonitor_qnx.cpp
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


set(HYP_SHARED_SRC
    ${HYP_SHARED_PATH}/command.hpp
    ${HYP_SHARED_PATH}/command.cpp
    ${HYP_SHARED_PATH}/blockreader.hpp
    ${HYP_SHARED_PATH}/blockwriter.hpp
)

set(HYPE_GW_SRC
    src/main.cpp
    src/clientconnector.hpp
    src/clientconnector.cpp
    src/localclientdispatcher.hpp
    src/localclientdispatcher.cpp
    src/remoteclientdispacher.hpp
    src/remoteclientdispacher.cpp
    src/clientdispatcher.hpp
    src/vsockclient.cpp
    src/vsockclient.hpp
)

add_executable(VSMT_Hyp_Gateway
  ${HYPE_GW_SRC}
  ${COMMON_SRC}
  ${HYP_SHARED_SRC}

  src/vmgateway.hpp src/vmgateway.cpp
  src/controller.hpp src/controller.cpp
)
target_link_libraries(VSMT_Hyp_Gateway Qt${QT_VERSION_MAJOR}::Core Qt5::Network)

include(GNUInstallDirs)
install(TARGETS VSMT_Hyp_Gateway
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
