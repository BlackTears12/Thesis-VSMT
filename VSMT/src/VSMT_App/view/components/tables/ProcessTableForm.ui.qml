

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels
import vsmt

Rectangle {
    id: root
    property alias model: tableView.model
    property alias header: header
    property alias tableHeight: tableView.height
    signal headerClicked(int col)
    height: header.height + tableView.height
    color: Style.backgroundColor
    width: 500

    HorizontalHeaderView {
        id: header
        anchors.horizontalCenter: tableView.horizontalCenter
        anchors.top: parent.top
        syncView: tableView
        z: 100

        property int orderedByCol: 4
        property bool ascendingOrder: true

        delegate: Rectangle {
            id: headerDelegate

            color: "#00ffffff"
            implicitHeight: 50
            implicitWidth: 180

            //color: Style.backgroundColor
            Text {
                id: colName
                color: "#ffffff"
                anchors.fill: parent
                text: display
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.styleName: "Bold"
            }
            MouseArea {
                id: headerMouseArea
                anchors.fill: parent
                // @disable-check M222
                onClicked: root.headerClicked(model.column)
            }
            Image {
                height: 30
                width: 30
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                source: header.ascendingOrder ? "qrc:/resources/resources/sort-up.png" :
                    "qrc:/resources/resources/sort-down.png"
                visible: (header.orderedByCol === model.column)
                antialiasing: true
            }
        }
    }

    TableView {
        id: tableView
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: header.bottom
        width: parent.width
        height: 350

        property var colWidths: [100,120,170,200]
        // @disable-check M222
        columnWidthProvider: function(col) {
            if(col < 4)
                return colWidths[col];
            // @disable-check M222
            return (parent.width - colWidths.reduce((sum,a) => sum+a,0))/2
        }

        delegate: Rectangle {
            id: delegateItem
            color: "#d6343437"
            implicitHeight: 50
            implicitWidth: 250
            border.width: 0

            Text {
                color: "#cdcdcd"
                anchors.fill: parent
                text: display
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.styleName: "Bold"
                antialiasing: true
            }

            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 2
                color: "white"
            }
        }

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
            height: 50
            anchors.top: parent.top
            anchors.left: parent.right
        }

        // @disable-check M223
        Component.onCompleted: {
            //tring to fix table content only appearing on resize
            // @disable-check M222
        }
    }
}
