

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import vsmt

Rectangle {
    id: root
    width: 1100
    height: 900
    color: Style.backgroundColor

    Rectangle {
        id: clientDescriptorExtension
        width: clientDescriptor.width
        height: 50
        color: Style.backgroundColor
    }
    ClientDescriptor {
        id: clientDescriptor
        width: 350
        anchors.top: clientDescriptorExtension.bottom
        anchors.left: parent.left
        height: parent.height
    }

    Item {
        id: contentRoot
        anchors.top: parent.top
        anchors.left: clientDescriptor.right
        width: parent.width - clientDescriptor.width
        height: parent.height

    Rectangle {
        id: netHeader
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        height: 50
        color: "#1e1e1e"
        Text {
            anchors.fill: parent
            color: "#ffffff"
            text: "Network Interfaces"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 20
        }
    }

    ListView {
        id: netList
        anchors.top: netHeader.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        width: parent.width * 0.9
        height: parent.height - netHeader.height - anchors.topMargin
        spacing: 5
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
            height: 50
            anchors.top: parent.top
            anchors.left: parent.right
        }
        delegate: Rectangle {
            id: netdescriptor
            required property string name
            required property string type
            required property string rxValue
            required property string txValue
            required property NetworkLoadDataModel rxDataModel
            required property NetworkLoadDataModel txDataModel
            height: 250
            width: netList.width
            color: Style.secondaryColor

            Rectangle {
                id: netNameRect
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                height: 80
                Text {
                    id: netNameLabel
                    text: name
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 18
                    color: "white"
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: type
                    anchors.top: netNameLabel.bottom
                    anchors.topMargin: 15
                    height: 10
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 14
                    color: "white"
                }
            }

            Rectangle {
                anchors.top: netNameRect.bottom
                id: divider
                width: parent.width
                height: 2
                color: "white"
            }

            Row {
                anchors.top: divider.bottom
                width: parent.width
                height: parent.height - netNameRect.height - anchors.topMargin
                Item {
                    width: parent.width/2
                    height: parent.height
                    NetworkLoadChart {
                        dataModel: netdescriptor.rxDataModel
                        id: rxChart
                        splineName: "RX b"
                        anchors.fill: parent
                    }
                    Text {
                        anchors.top: rxChart.top
                        anchors.topMargin: 10
                        text: "Receive: " + netdescriptor.rxValue + "b"
                        color:"white"
                        anchors.horizontalCenter: rxChart.horizontalCenter
                        z:100
                    }
                }
                Item {
                    width: parent.width/2
                    height: parent.height
                    NetworkLoadChart {
                        dataModel: netdescriptor.txDataModel
                        id: txChart
                        splineName: "TX b"
                        width: parent.width
                        height: parent.height
                        splineColor: "green"
                    }
                    Text {
                        anchors.top: txChart.top
                        anchors.topMargin: 10
                        text: "Transmit: " + netdescriptor.txValue + "b"
                        color:"white"
                        anchors.horizontalCenter: txChart.horizontalCenter
                        z:100
                    }
                }

            }
        }

        model: NetworkInterfaceModel
    }
    }
}
