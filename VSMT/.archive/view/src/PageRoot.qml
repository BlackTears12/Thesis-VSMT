import QtQuick 2.15
import view

PageRootForm {
    Connections {
        target: PageNavigator

        function onMainPageRequested() {
            loader.source = "pages/MainPage.qml"
        }

        function onClientOverviewPageRequested() {
            loader.source = "pages/ClientOverviewPage.qml"
        }

        function onClientCpuPageRequested() {
            loader.source = "pages/ClientCpuPage.qml"
        }
    }
}
