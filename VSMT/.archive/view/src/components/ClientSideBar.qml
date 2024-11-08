import QtQuick 2.15
import view


ClientSideBarForm {
    id: root
    color: Style.secondaryColor

    ListView {
        id: listView
        anchors.fill: parent
        model: ClientStatusModel

        delegate: ClientSideBarItem {
            width: parent.width
            height: 150

            required property string name
            required property real cpu
            required property real memory

            displayName: name
            displayMemory: memory
            displayCpu: cpu

            Component.onCompleted: {
                onClicked.connect(ClientStatusModel.itemTriggered)
            }
        }
    }
}
