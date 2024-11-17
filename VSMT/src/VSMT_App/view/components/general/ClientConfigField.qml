import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle
    color: "transparent"
    width: parent.width
    height: 50
    anchors.topMargin: 10
    required property string fieldName
    required property string fieldValue

    Label {
        text: fieldName
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pixelSize: 16
    }

    TextEdit {
        text: fieldValue
        width: 120
        height: 25
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        font.pixelSize: 16
        horizontalAlignment: TextEdit.AlignHCenter
        verticalAlignment: TextEdit.AlignVCenter
        color: "white"
        onEditingFinished: {
            parent.fieldValue = text
        }
        Rectangle {
            color: "#4b4e4e"
            anchors.fill: parent
            z: -1
            radius: 5
        }
    }
}

