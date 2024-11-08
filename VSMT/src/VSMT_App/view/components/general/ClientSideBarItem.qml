import QtQuick 2.15

ClientSideBarItemForm {
    id: form
    property int clientID
    signal onClicked(id: int)

    Connections {
        target: mouseArea
        function onClicked() {
            form.onClicked(clientID)
        }
    }

    clientIndex: clientID

    property alias displayName: form.name
    property alias displayCpu: form.cpu
    property alias displayMemory: form.memory
}
