

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

    width: 300
    height: 500

    //color: Style.backgroundColor
    color: "#252d50"
    Label {
        id: nameLabel
        width: parent.width
        height: 20
        text: configModel.name
        anchors.top: parent.top
        anchors.topMargin: 10
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: divider
        width: parent.width
        height: 10
        color: "#424242"
        anchors.top: nameLabel.bottom
        anchors.topMargin: 15
        radius: 100
    }

    ColumnLayout {
        width: parent.width
        anchors.top: divider.bottom
        anchors.topMargin: 10
        spacing: 10

        ClientConfigField {
            id: nameField
            fieldName: "Name"
            fieldValue: name
        }

        ClientConfigField {
            id: cidField
            fieldName: "Context ID"
            fieldValue: cid
        }

        ClientConfigField {
            id: portField
            fieldName: "Port"
            fieldValue: port
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
