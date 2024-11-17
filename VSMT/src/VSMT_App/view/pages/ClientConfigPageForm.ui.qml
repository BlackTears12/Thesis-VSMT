

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import QtQuick.Layouts
import vsmt
import "../components/general"

Rectangle {
    id: root
    property ClientConfigModel configModel: ClientConfigListModel.context
    signal saveConfig(string name,string cid,string port)
    signal revertConfig

    property string name: configModel.name
    property string cid: configModel.cid
    property string port: configModel.port

    property alias nameField: nameField
    property alias cidField: cidField
    property alias portField: portField

    width: 350
    height: 400

    //color: Style.backgroundColor
    color: "#252d50"
    Rectangle {
        id: nameLableContainer
        width: parent.width
        height: 40
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        color: "grey"
        Label {
            id: nameLabel
            height: 20
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            text: configModel.name
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
        }
    }

    ColumnLayout {
        width: parent.width
        anchors.top: nameLableContainer.bottom
        spacing: 10

        Rectangle {
            height: 3
            width: parent.width
            color: "grey"
        }

        ClientConfigField {
            id: nameField
            fieldName: "Name"
            fieldValue: name
        }

        Rectangle {
            height: 3
            width: parent.width
            color: "grey"
        }

        ClientConfigField {
            id: cidField
            fieldName: "Context ID"
            fieldValue: cid
        }

        Rectangle {
            height: 3
            width: parent.width
            color: "grey"
        }

        ClientConfigField {
            id: portField
            fieldName: "Port"
            fieldValue: port
        }

        Rectangle {
            height: 3
            width: parent.width
            color: "grey"
        }
    }

    Button {
        width: 80
        height: 30
        id: cancelButton
        text: "Cancel"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 40
        // @disable-check M222
        onClicked: revertConfig()
    }

    Button {
        width: 80
        height: 30
        id: saveButton
        text: "Save"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 40
        // @disable-check M223
        onClicked: {
            // @disable-check M222
            saveConfig(nameField.fieldValue,cidField.fieldValue,portField.fieldValue)
        }
    }
}
