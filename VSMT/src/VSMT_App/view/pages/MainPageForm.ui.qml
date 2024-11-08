

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import vsmt

Item {
    width: 1100
    height: 900

    Text {
        id: mainCaption
        anchors.top: parent.top
        anchors.topMargin: 30
        font.pointSize: 25
        anchors.horizontalCenter: parent.horizontalCenter
        color: "white"
        text: "Virtual System Monitoring Tool"
    }

    ClientConfigList {
        anchors.top: mainCaption.bottom
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.7
        height: parent.height * 0.6
    }

    Image {
        width: 320
        height: 50
        anchors.verticalCenter: signature.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/resources/resources/kb_logo.png"
    }

    Text {
        id: signature
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        font.pointSize: 16
        anchors.horizontalCenter: parent.horizontalCenter
        color: "white"
        text: "Made by Bálint Szombati"
    }

    Image {
        width: 70
        height: 70
        anchors.verticalCenter: signature.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        antialiasing: true
        source: "qrc:/resources/resources/ELTE_logo.png"
    }
}
