cmake_minimum_required(VERSION 3.16)

project(VSMT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 COMPONENTS Core Quick QuickControls2 Charts Network REQUIRED)

qt_standard_project_setup()

set(COMMON_LIB_PATH ../common)

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
    ${COMMON_LIB_PATH}/vsockmessage.hpp
    ${COMMON_LIB_PATH}/vsockmessage.cpp
    ${COMMON_LIB_PATH}/vsock_headers.hpp
    ${COMMON_LIB_PATH}/clientconfiguration.hpp

    ${COMMON_LIB_PATH}/linux/resourcemonitor_linux.cpp
    ${COMMON_LIB_PATH}/linux/resourcemonitor_linux.hpp
    ${COMMON_LIB_PATH}/linux/sysfileparser.hpp
    ${COMMON_LIB_PATH}/linux/sysfileparser.cpp
    ${COMMON_LIB_PATH}/linux/commandutil.cpp
    ${COMMON_LIB_PATH}/linux/commandutil.hpp

    ${COMMON_LIB_PATH}/qnx/resourcemonitor_qnx.hpp
    ${COMMON_LIB_PATH}/qnx/resourcemonitor_qnx.cpp
)
include_directories(
    controller
    datamodels
    util
    viewcontrollers
    core
    ${COMMON_LIB_PATH}
)

set(SINGLETON_SRC_FILES
    viewcontrollers/pagenavigator.hpp
    viewcontrollers/pagenavigator.cpp
    viewcontrollers/menubarmodel.hpp

    datamodels/clientstatusmodel.hpp
    datamodels/clientstatusmodel.cpp
    datamodels/cpuloaddatamodel.hpp

    datamodels/processtablemodel.hpp
    datamodels/processtablemodel.cpp
    datamodels/rangemodel.hpp
    datamodels/cpurangemodel.hpp
    datamodels/memoryrangemodel.hpp
    datamodels/diskrangemodel.hpp
    datamodels/lineargraphdatamodel.hpp
    datamodels/lineargraphdatamodel.cpp
    datamodels/clientconfiglistmodel.hpp
    datamodels/clientconfiglistmodel.cpp
    datamodels/clientdescriptionmodel.hpp
    datamodels/clientdescriptionmodel.cpp
    datamodels/storagedatamodel.hpp
    datamodels/storagedatamodel.cpp
    datamodels/networkinterfacemodel.hpp
    datamodels/networkinterfacemodel.cpp

    datamodels/coreloaddatamodel.hpp
    datamodels/coreloaddatamodel.cpp
)

qt_add_executable(VSMT
    qml.qrc
    main.cpp

    datamodels/flowbuffer.hpp
    datamodels/processindexer.hpp
    datamodels/processindexer.cpp

    datamodels/clientconfigmodel.hpp
    datamodels/clientconfigmodel.cpp
    datamodels/contiguousclientmapper.hpp
    datamodels/contiguousclientmapper.cpp
    datamodels/clientdatacontainer.hpp
    datamodels/cpuloaddatamodel.cpp

    controller/clientviewcontroller.cpp
    controller/clientviewcontroller.hpp
    controller/clientdispatcher.hpp

    controller/remoteclientdispacher.hpp
    controller/remoteclientdispacher.cpp
    controller/localclientdispatcher.hpp
    controller/localclientdispatcher.cpp
    controller/clientconnector.hpp
    controller/clientconnector.cpp

    controller/controller.hpp
    controller/controller.cpp
    controller/vsockclient.hpp
    controller/vsockclient.cpp

    core/metatypes.hpp
    core/application.hpp
    core/application.cpp
    core/qmlsingleton.hpp

    ${SINGLETON_SRC_FILES}
    ${COMMON_SRC}
)

set_source_files_properties(${SINGLETON_SRC_FILES}
    view/Style.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

set_source_files_properties(${CIRCULAR_GAUGE_SINGLETON}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(VSMT
    URI vsmt
    VERSION 1.0
    QML_FILES
        view/Style.qml

        view/AppWindow.qml
        view/PageRoot.qml
        view/PageRootForm.ui.qml
        view/pages/MainPage.qml
        view/pages/MainPageForm.ui.qml
        view/pages/ClientOverviewPageForm.ui.qml
        view/pages/ClientOverviewPage.qml
        view/pages/ClientCpuPage.qml
        view/pages/ClientConfigPageForm.ui.qml
        view/pages/ClientConfigPage.qml
        view/pages/ClientDiskPageForm.ui.qml
        view/pages/ClientDiskPage.qml
        view/pages/ClientNetworkPage.qml
        view/pages/ClientNetworkPageForm.ui.qml
        view/pages/ClientProcessPage.qml
        view/pages/ClientProcessPageForm.ui.qml

        view/components/general/ClientSideBarForm.ui.qml
        view/components/general/ClientSideBar.qml
        view/components/general/ClientSideBarItemForm.ui.qml
        view/components/general/ClientSideBarItem.qml
        view/components/general/ClientDescriptor.qml
        view/components/general/ClientDescriptorForm.ui.qml
        view/components/general/ClientConfigList.qml
        view/components/general/ClientConfigListForm.ui.qml
        view/components/general/ClientConfigField.qml
        view/components/general/Desktop.qml

        view/components/tables/ProcessTableForm.ui.qml
        view/components/tables/ProcessTable.qml

        view/components/charts/LinearChartForm.ui.qml
        view/components/charts/SmallCpuChart.qml
        view/components/charts/CpuChart.qml
        view/components/charts/NetworkLoadChart.qml

        view/components/gauges/CircularGauge.qml
        view/components/gauges/CpuGauge.qml
        view/components/gauges/MemoryGauge.qml
        view/components/gauges/DiskGauge.qml
        view/components/gauges/CircularTickmarkLabel.qml
        view/components/gauges/GaugeStyle.qml
        view/components/Utils.js
    RESOURCES
        qmldir
    URI vsmt
    VERSION 1.0
    SOURCES
        ${SINGLETON_SRC_FILES}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(VSMT PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appview
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


target_link_libraries(VSMT
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::Charts
    PRIVATE Qt6::Network
)


include(GNUInstallDirs)

install(TARGETS VSMT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
