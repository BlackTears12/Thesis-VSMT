

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
    width: 600
    height: 400
    color: "#424242"
    radius: 20

    signal editClicked(int id)
    signal connectClicked(int id)
    signal deleteClieked(int id)
    signal newConfigClicked

    property alias listView: listView

    Rectangle {
        id: header
        width: parent.width
        height: 60
        color: "#010a2e"
        anchors.top: parent.top

        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: "Client configurations"
            font.pointSize: 18
            color: "white"
        }

        Button {
            id: newConfigButton
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 30
            height: 30

            icon {
                source: "qrc:/resources/resources/plus_icon_white.png"
            }
            // @disable-check M222
            onClicked: root.newConfigClicked()
        }
    }

    ListView {
        id: listView
        width: parent.width
        height: parent.height - header.height
        anchors.top: header.bottom

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
            height: 50
            anchors.top: parent.top
            anchors.left: parent.right
        }

        delegate: Rectangle {
            id: rectangle
            required property string name
            required property int identifier
            required property bool isRemote
            required property ClientStatus status
            required property string statusMessage

            color: isRemote ? "#292e44" : header.color

            radius: 0
            width: root.width
            height: 100

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 30
                font.pointSize: 16
                id: idLabel
                text: parent.name
            }

            Image {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.topMargin: 3
                height: 30
                width: 30
                source: "qrc:/resources/resources/delete_x.png"
                visible: rectangle.isRemote
                MouseArea {
                    anchors.fill: parent
                    // @disable-check M223
                    onClicked: {
                        if (rectangle.isRemote)
                            // @disable-check M222
                            root.deleteClieked(identifier)
                    }
                }
            }

            Text {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                text: rectangle.statusMessage
                color: "white"
            }

            Button {
                width: 90
                height: 30
                text: 'Edit'
                anchors.left: parent.left
                id: editButton
                anchors.bottom: parent.bottom
                anchors.leftMargin: 100
                anchors.bottomMargin: 10
                // @disable-check M223
                onClicked: {
                    if (rectangle.isRemote)
                        // @disable-check M222
                        root.editClicked(identifier)
                }
            }

            Button {
                id: connectButton
                width: 90
                height: 30
                text: 'Connect'
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.rightMargin: 100
                anchors.bottomMargin: 10
                // @disable-check M223
                onClicked: {
                    if (rectangle.isRemote)
                        // @disable-check M222
                        root.connectClicked(identifier)
                }
            }

            Rectangle {
                width: parent.width
                height: 4
                color: "#b9b9b9"
                anchors.bottom: parent.bottom
            }
        }
    }
}
