import QtQuick 2.15
import vsmt

ClientConfigListForm {
    listView.model: ClientConfigListModel

    Component.onCompleted: {
        editClicked.connect(ClientConfigListModel.configEditClicked)
        connectClicked.connect(ClientConfigListModel.configConnectClicked)
        newConfigClicked.connect(ClientConfigListModel.newConfigClicked)
        deleteClieked.connect(ClientConfigListModel.deleteConfigClicked)
    }
}
