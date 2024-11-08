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
    }

    TextEdit {
        text: fieldValue
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        color: "white"
        onEditingFinished: {
            parent.fieldValue = text
        }
    }
}

