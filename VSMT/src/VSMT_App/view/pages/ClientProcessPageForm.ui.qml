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
        anchors.top: parent.top
        anchors.left: clientDescriptor.right
        width: parent.width - clientDescriptor.width
        height: parent.height

        Text {
            text: "Processes"
            color: "white"
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 18
            id: txt
        }

        ProcessTable {
            width: parent.width - 30
            anchors.top: txt.bottom
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 10
            tableHeight: parent.height - txt.height -
                txt.anchors.topMargin - anchors.topMargin - 100
        }
    }
}
