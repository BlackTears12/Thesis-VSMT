import QtQuick 2.15
import vsmt

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

        function onClientMemoryPageRequested() {
            loader.source = "pages/ClientProcessPage.qml"
        }

        function onClientDiskPageRequested() {
            loader.source = "pages/ClientDiskPage.qml"
        }

        function onClientNetworkPageRequested() {
            loader.source = "pages/ClientNetworkPage.qml"
        }

        function onOpenClientConfigPageRequested() {
            configPage.refreshContext()
            configPage.show()
        }

        function onCloseClientConfigPageRequested() {
            configPage.close()
        }
    }
}
