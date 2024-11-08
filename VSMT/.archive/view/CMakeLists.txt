cmake_minimum_required(VERSION 3.16)

project(view VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 COMPONENTS Core Quick QuickControls2 Charts REQUIRED)

set(SRC_DIR src/model)
set(QML_DIR src)
set(EXT_DIR src/ext)

qt_standard_project_setup()

include_directories(
    ${SRC_DIR}
    ${EXT_DIR}/CircularGauge
)

set(SINGLETON_SRC_FILES
    ${SRC_DIR}/clientstatusmodel.hpp
    ${SRC_DIR}/clientstatusmodel.cpp
    ${SRC_DIR}/mainpageadapter.cpp
    ${SRC_DIR}/mainpageadapter.hpp
    ${SRC_DIR}/pagenavigator.hpp
    ${SRC_DIR}/pagenavigator.cpp
    ${SRC_DIR}/menubarmodel.hpp
    ${SRC_DIR}/cpugraphdatamodel.hpp
    ${SRC_DIR}/processtablemodel.hpp
    ${SRC_DIR}/processtablemodel.cpp
)


set(CIRCULAR_GAUGE_QML
    ${EXT_DIR}/CircularGauge/CircularGauge.qml
    ${EXT_DIR}/CircularGauge/CpuGauge.qml
    ${EXT_DIR}/CircularGauge/MemoryGauge.qml
    ${EXT_DIR}/CircularGauge/CircularTickmarkLabel.qml
    ${EXT_DIR}/CircularGauge/GaugeStyle.qml
    ${EXT_DIR}/CircularGauge/Utils.js
)

set(CIRCULAR_GAUGE_SINGLETON
    ${EXT_DIR}/CircularGauge/rangemodel.hpp
    ${EXT_DIR}/CircularGauge/cpurangemodel.hpp
    ${EXT_DIR}/CircularGauge/memoryrangemodel.hpp
)

set(CIRCULAR_GAUGE_SRC
    ${EXT_DIR}/CircularGauge/CircularGauge.qrc
    ${EXT_DIR}/CircularGauge/qquickrangemodel_p_p.h
    ${EXT_DIR}/CircularGauge/qquickrangemodel_p.h
    ${EXT_DIR}/CircularGauge/qquickrangemodel.cpp
    ${CIRCULAR_GAUGE_SINGLETON}
)

qt_add_executable(appview
    qml.qrc
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/view.hpp
    ${SRC_DIR}/view.cpp    
    ${SRC_DIR}/lineargraphdatamodel.hpp
    ${SRC_DIR}/lineargraphdatamodel.cpp
    ${SRC_DIR}/qmlsingleton.hpp
    ${SRC_DIR}/flowbuffer.hpp
    ${SRC_DIR}/processindexer.hpp
    ${SRC_DIR}/processindexer.cpp
    ${SRC_DIR}/clientviewcontroller.hpp
    ${SRC_DIR}/clientviewcontroller.cpp
    ${SRC_DIR}/dataprovider.hpp
    ${SINGLETON_SRC_FILES}
    ${CIRCULAR_GAUGE_SRC}
)

set_source_files_properties(${SINGLETON_SRC_FILES}
    ${QML_DIR}/Style.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

set_source_files_properties(${CIRCULAR_GAUGE_SINGLETON}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(appview
    URI view
    VERSION 1.0
    QML_FILES
        ${QML_DIR}/qmldir
        ${QML_DIR}/Style.qml

        ${QML_DIR}/AppWindow.qml
        ${QML_DIR}/PageRoot.qml
        ${QML_DIR}/PageRootForm.ui.qml
        ${QML_DIR}/pages/MainPage.qml
        ${QML_DIR}/pages/MainPageForm.ui.qml
        ${QML_DIR}/pages/ClientOverviewPageForm.ui.qml
        ${QML_DIR}/pages/ClientOverviewPage.qml
        ${QML_DIR}/pages/ClientCpuPage.qml
        ${QML_DIR}/pages/ClientCpuPageForm.ui.qml

        ${QML_DIR}/components/ClientSideBarForm.ui.qml
        ${QML_DIR}/components/ClientSideBar.qml
        ${QML_DIR}/components/ClientSideBarItemForm.ui.qml
        ${QML_DIR}/components/ClientSideBarItem.qml  
        ${QML_DIR}/components/ClientDescriptor.qml
        ${QML_DIR}/components/ClientDescriptorForm.ui.qml
        ${QML_DIR}/components/ProcessTableForm.ui.qml
        ${QML_DIR}/components/ProcessTable.qml

        ${QML_DIR}/components/LinearChartForm.ui.qml
        ${QML_DIR}/components/CpuChart.qml
        ${QML_DIR}/components/MemoryChart.qml

        ${CIRCULAR_GAUGE_QML}
    URI view
    VERSION 1.0
    SOURCES
        ${SINGLETON_SRC_FILES}        
    URI view
    VERSION 1.0
    SOURCES
        ${CIRCULAR_GAUGE_SRC}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appview PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appview
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


target_link_libraries(appview
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::Charts
)


include(GNUInstallDirs)

install(TARGETS appview
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
