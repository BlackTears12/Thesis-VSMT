import QtQuick 2.15
import vsmt

Rectangle {
    width: parent.width
    height: 35
    color: "#717173"

    component Icon : Rectangle {
        property alias iconSrc: img.source
        property alias mouseArea: mouseArea

        width: 35
        height: 35
        anchors.verticalCenter: parent.verticalCenter
        color: mouseArea.containsMouse ? "Grey" : "#717173"
        Image {
            id: img
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: 30
            height: 30
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
            }
        }
    }

    Row {
        anchors.fill: parent
        leftPadding: 5
        spacing: 40

        Icon {
            iconSrc: "qrc:/resources/resources/home_icon.png"
            mouseArea.onClicked: PageNavigator.mainPageRequested()
        }
        Icon {
            iconSrc: "qrc:/resources/resources/settings_icon.png"
            mouseArea.onClicked: PageNavigator.mainPageRequested()
        }
    }
}
