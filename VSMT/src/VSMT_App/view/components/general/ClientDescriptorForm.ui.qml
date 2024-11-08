

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import ".."
import vsmt

Rectangle {
    id: root
    width: 200
    color: Style.backgroundColor
    border.color: "white"
    border.width: 0

    property string clientName: ClientDescriptionModel.name

    Label {
        id: nameLabel
        color: "#ffffff"
        text: root.clientName
        width: parent.width
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 20
    }

    Rectangle {
        id: divider
        width: parent.width
        anchors.top: nameLabel.bottom
        anchors.topMargin: 5
        height: 3
        color: 'white'
    }

    Column {
        id: descriptorView
        anchors.top: divider.bottom
        width: parent.width
        height: 100

        component DesciptorItem: Rectangle {
            id: delegateItem
            required property string category
            required property string value

            width: parent.width
            height: 80
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
                    font.pointSize: 14
                    wrapMode: Text.Wrap
                }
            }
        }

        DesciptorItem {
            category: "Platform"
            value: ClientDescriptionModel.platform
        }

        DesciptorItem {
            category: "Distribution"
            value: ClientDescriptionModel.distribution
        }

        DesciptorItem {
            category: "CPU model"
            value: ClientDescriptionModel.cpuModel
        }

        DesciptorItem {
            category: "CPU cores"
            value: ClientDescriptionModel.cpuCores
        }

        DesciptorItem {
            category: "CPU speed"
            value: ClientDescriptionModel.cpuCores + " GHz"
        }
    }
}
