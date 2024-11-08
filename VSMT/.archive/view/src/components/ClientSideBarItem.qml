import QtQuick 2.15
import view

ClientSideBarItemForm {
    id: form
    property int clientID: 0
    signal onClicked(id: int)

    Connections {
        target: mouseArea
        function onClicked() {
            form.onClicked(clientID)
        }
    }

    property alias displayName: form.name
    property alias displayCpu: form.cpu
    property alias displayMemory: form.memory
}
