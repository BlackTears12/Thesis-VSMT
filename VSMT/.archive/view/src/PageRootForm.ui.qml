

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import "components"
import "pages"

Item {
    id: window
    width: 1440
    height: 1080

    property alias loader: loader

    ClientSideBar {
        id: clientSideBar
        x: 624
        width: 200
        height: window.height
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 0
        anchors.topMargin: 0
    }

    Loader {
        source: "pages/MainPage.qml"
        id: loader
        height: window.height
        width: window.width - clientSideBar.width
        anchors.right: clientSideBar.left
    }
}
