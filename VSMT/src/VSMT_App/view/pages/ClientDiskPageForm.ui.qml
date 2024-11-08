

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
    color: "#303030"

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
        width: parent.width-clientDescriptor.width
        height: parent.height
        anchors.left: clientDescriptor.right
        anchors.top: parent.top

    Rectangle {
        id: storageHeader
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: 50
        color: "#1e1e1e"
        Text {
            anchors.fill: parent
            color: "#ffffff"
            text: "Storage Devices"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 20
        }
    }

    ListView {
        id: storageList
        anchors.top: storageHeader.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        width: parent.width * 0.8
        height: (parent.height - storageHeader.height - anchors.topMargin)
        delegate: Rectangle {
            id: descriptor
            required property string name
            required property string fileFsType
            required property string device
            required property int bytesTotal
            required property int bytesFree
            required property real usedPercent
            width: parent.width * 0.7
            anchors.horizontalCenter: parent.horizontalCenter
            radius: 100

            Rectangle {
                id: nameRect
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                height: 100
                Text {
                    color: "#ffffff"
                    text: descriptor.device
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 20
                }
            }

            Item {
                id: progressContainer
                anchors.top: nameRect.bottom
                width: parent.width
                ProgressBar {
                    id: usedProgress
                    anchors.horizontalCenter: parent.horizontalCenter
                    value: usedPercent
                    width: parent.width * 0.6
                    from: 0
                    to: 100
                }

                Row {
                    id: usageContaniner
                    anchors.top: usedProgress.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Text {
                        id: usedtext
                        color: "#ffffff"
                        font.pointSize: 16
                        text: "Used: " + (bytesTotal - bytesFree) + "Kb"
                    }

                    Text {
                        id: totalText
                        color: "#ffffff"
                        font.pointSize: 16
                        text: "Total: " + bytesTotal + "Kb"
                    }
                }
            }
            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: progressContainer.bottom
                anchors.topMargin: usageContaniner.height + usageContaniner.anchors.topMargin + 20
                spacing: 10
                Text {
                    color: "#ffffff"
                    text: "Filesystem type: " + fileFsType
                    font.pointSize: 15
                }
                Text {
                    color: "#ffffff"
                    text: "Name: " + name
                    font.pointSize: 15
                }
            }
        }

        model: StorageDeviceModel
    }
    }
}
