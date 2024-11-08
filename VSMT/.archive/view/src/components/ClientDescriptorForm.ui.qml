

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import ".."

Rectangle {
    id: root
    width: 200
    height: 600
    color: Style.backgroundColor
    border.color: "white"

    property string clientName: 'Client'

    Rectangle {
        id: nameRect
        width: parent.width
        height: parent.height * 0.15
        color: "#00ffffff"
        anchors.top: parent.top
        Label {
            id: nameLabel
            color: "#ffffff"
            text: root.clientName
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 20
        }
        Rectangle {
            width: parent.width
            anchors.bottom: parent.bottom
            height: 3
            color: 'white'
        }
    }

    ListView {
        id: descriptorView
        anchors.top: nameRect.bottom
        width: parent.width
        height: contentHeight

        delegate: Rectangle {
            id: delegateItem
            required property string category
            required property string value

            width: parent.width
            height: 60
            color: "#00ffffff"
            Rectangle {
                id: descriptionCategoryRect
                height: parent.height
                width: (parent.width / 2) - 1.5
                anchors.left: parent.left
                color: "#00ffffff"
                Label {
                    id: descriptionCategoryLabel
                    color: "#ffffff"
                    text: delegateItem.category
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: 10
                    font.pointSize: 15
                }
            }

            Rectangle {
                id: separator
                height: parent.height
                width: 3
                anchors.left: descriptionCategoryRect.right
            }

            Rectangle {
                id: descriptionValueRect
                height: parent.height
                width: (parent.width / 2) - 1.5
                anchors.right: parent.right
                color: "#00ffffff"
                Label {
                    id: descriptionValueLabel
                    color: "#ffffff"
                    text: delegateItem.value
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    rightPadding: 10
                    font.pointSize: 15
                }
            }
        }

        model: ListModel {
            id: testModel

            ListElement {
                category: 'OS'
                value: 'QNX'
            }

            ListElement {
                category: 'OS'
                value: 'QNX'
            }
        }
    }

    Rectangle {
        width: parent.width
        height: 3
        anchors.top: descriptorView.bottom
    }
}
