

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import "../components"
import "../ext/CircularGauge"
import QtCharts

import view

Rectangle {
    id: root
    width: 1100
    height: 900
    color: "#303030"

    property alias procLabel: procLabel
    property alias descriptor: descriptor

    ClientDescriptor {
        id: descriptor
        width: 300
        height: 600
        anchors.top: root.top
        anchors.left: root.left
    }

    Label {
        id: procLabel
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 20
        anchors.left: descriptor.right
        width: (root.width - descriptor.width)/2
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
        height: 300
    }

    Label {
        id: memLabel
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 20
        anchors.right: parent.right
        width: (root.width - descriptor.width)/2
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
        height: 300
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

    ProcessTable {
        id: procTable
        anchors.top: divider.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: divider.horizontalCenter
        width: root.width - descriptor.width
    }
}
