

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import "../components"
import QtCharts

import vsmt

Rectangle {
    id: root
    width: 1100
    height: 900
    color: "#303030"

    property alias procLabel: procLabel
    property alias descriptor: descriptor

    Rectangle {
        id: descriptorContainer
        anchors.top: root.top
        anchors.left: root.left
        width: 350
        height: parent.height
        color: Style.backgroundColor
        ClientDescriptor {
            id: descriptor
            width: parent.width
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.left: parent.left
            height: parent.height*0.6
        }

        Text {
            text: "Network Usage"
            color: "white"
            font.pointSize: 16
            anchors.bottom: netRect.top
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Rectangle {
            id: netRect
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.9
            height: 180
            anchors.top: descriptor.bottom
            anchors.topMargin: 10
            color: Style.secondaryColor
            radius: 20

            MouseArea {
                anchors.fill: parent
                // @disable-check M222
                onClicked: PageNavigator.clientNetworkPageRequested()
                z: -10
            }
            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.leftMargin: 5
                width: parent.width * 0.7
                spacing: 25

                Text {
                    text: "Received bytes:\t" + NetworkInterfaceModel.overallRx + " b/s"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 14
                }

                ProgressBar {
                    id: rcvProgress
                    value: NetworkInterfaceModel.overallRx
                    width: parent.width
                    to: 2000
                }

                Text {
                    text: "Transmited bytes:\t" + NetworkInterfaceModel.overallTx + " b/s"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 14
                }
                ProgressBar {
                    id: transmitProgress
                    value: NetworkInterfaceModel.overallTx
                    width: parent.width
                    to: 2000
                }
            }
        }

        Item {
            id: disconnectContainer
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            width: 50
            height: 50

            Image{
                id: disconnectImg
                width: parent.width*0.8
                height: parent.height*0.8
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                source: "qrc:/resources/resources/disconnect.png"
                MouseArea {
                    anchors.fill: parent
                    // @disable-check M223
                    onClicked: {
                        // @disable-check M222
                        PageNavigator.requestDisconnect()
                    }
                }
            }

            Text {
                text: "Disconnect"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: disconnectImg.bottom
                anchors.topMargin: 2
                font.pointSize: 8
                color: "white"
            }
        }
    }

    Label {
        id: procLabel
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 16
        anchors.left: descriptorContainer.right
        width: (root.width - descriptor.width)/3
        height: parent.height * 0.1
        text: "Processor Usage"
    }

    CpuGauge {
        id: cpuGauge
        maximumValue: 100
        anchors.left: procLabel.left
        anchors.horizontalCenter: procLabel.horizontalCenter
        anchors.top: procLabel.bottom
        anchors.topMargin: 15
        antialiasing: true
        width: 200
        height: 240
    }

    Label {
        id: memLabel
        anchors.top: parent.top
        anchors.horizontalCenter: divider.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 16
        width: (root.width - descriptor.width)/3
        height: parent.height * 0.1
        text: "Memory Usage"
    }

    MemoryGauge {
        id: memoryGauge
        maximumValue: 100
        anchors.right: memLabel.right
        anchors.horizontalCenter: memLabel.horizontalCenter
        anchors.top: memLabel.bottom
        anchors.topMargin: 15
        antialiasing: true
        width: 200
        height: 240
    }

    Label {
        id: diskLabel
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 16
        anchors.right: parent.right
        width: (root.width - descriptor.width)/3
        height: parent.height * 0.1
        text: "Disk Usage"
    }

    DiskGauge {
        id: diskGauge
        maximumValue: 100
        anchors.right: diskLabel.right
        anchors.horizontalCenter: diskLabel.horizontalCenter
        anchors.top: diskLabel.bottom
        anchors.topMargin: 15
        antialiasing: true
        width: 200
        height: 240
    }

    Rectangle {
        id: divider
        anchors.top: cpuGauge.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        width: root.width - descriptor.width
        height: 10
        color: "#585858"
    }

    Label {
        id: processLabel
        anchors.horizontalCenter: divider.horizontalCenter
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.top : divider.bottom
        anchors.topMargin: 10
        text: "Processes"
    }

    ProcessTable {
        id: procTable
        anchors.top: processLabel.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: divider.horizontalCenter
        anchors.left: divider.left
        anchors.leftMargin: 10
        width: divider.width
        tableHeight:  parent.height - y - 100
    }
}
