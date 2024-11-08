

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels


Rectangle {
    id: root
    property alias model: tableView.model
    signal headerClicked(col: int)
    height: header.height + tableView.height

    HorizontalHeaderView {
        id: header
        anchors.horizontalCenter: tableView.horizontalCenter
        anchors.top: parent.top
        syncView: tableView
        height: contentHeight + bottomLine.height
        width: contentWidth

        delegate: Rectangle {
            id: headerDelegate
            implicitHeight: 50
            implicitWidth: 200
            border.width: 0
            Text {
                anchors.fill: parent
                text: display
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.styleName: "Bold"
            }
            MouseArea {
                id: headerMouseArea
                anchors.fill: parent
                onClicked: root.headerClicked(model.column)
            }
        }
        Rectangle {
            id: bottomLine
            anchors.top: parent.bottom
            implicitWidth: parent.width
            implicitHeight: 1
            border.width: 1
        }
    }

    TableView {
        id: tableView
        anchors.left: parent.left
        anchors.top: header.bottom
        width: contentWidth
        height: contentHeight
        delegate: Rectangle {
            id: delegateItem
            implicitWidth: 100
            implicitHeight: 50
            border.width: 1
            Text {
                anchors.fill: parent
                text: display
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.styleName: "Bold"
            }
        }
        resizableColumns : true
    }
}
