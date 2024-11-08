import QtQuick
import QtQuick.Controls
import view

ApplicationWindow {
    visible: true
    title: "Virtual System Monitoring Tool"
    width: 1600
    height: 900
    color: Style.backgroundColor

    menuBar: MenuBar {
        Menu {
            title: "Test"
            Action {
                text: "Decrease Cpu"
                onTriggered: MenubarModel.decreaseCpu()
            }
            Action {
                text: "Increase Cpu"
                onTriggered: MenubarModel.increaseCpu()
            }
        }
    }

    PageRoot {
        anchors.fill: parent
    }
}
