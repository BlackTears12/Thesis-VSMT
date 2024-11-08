

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import view

Rectangle {
    id: mainFrame
    width: 300
    height: 150
    color: Style.backgroundColor
    border.color: "#ffffff"

    property alias mouseArea: mouseArea

    property string name
    property string cpu
    property string memory

    Item {
        id: column
        anchors.fill: parent

        Label {
            id: nameLabel
            width: 300
            height: 20
            text: name
            anchors.top: parent.top
            anchors.topMargin: 15
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Medium"
            font.pointSize: 12
            topPadding: 0
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
            id: cpuLabel
            height: 30
            text: qsTr("CPU:")
            anchors.left: parent.left
            anchors.top: nameLabel.bottom
            anchors.leftMargin: 10
            anchors.topMargin: 20
            font.pointSize: 12
        }

        Label {
            id: cpuValueLabel
            height: 30
            text: cpu
            anchors.right: parent.right
            anchors.top: nameLabel.bottom
            anchors.rightMargin: 20
            anchors.topMargin: 20
            font.pointSize: 12
        }

        Label {
            id: memLabel
            height: 30
            text: qsTr("Memory:")
            anchors.left: parent.left
            anchors.top: cpuLabel.bottom
            anchors.leftMargin: 10
            anchors.topMargin: 10
            font.pointSize: 12
        }

        Label {
            id: memValueLabel
            height: 30
            text: memory
            anchors.right: parent.right
            anchors.top: cpuValueLabel.bottom
            anchors.rightMargin: 20
            anchors.topMargin: 10
            font.pointSize: 12
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
}
