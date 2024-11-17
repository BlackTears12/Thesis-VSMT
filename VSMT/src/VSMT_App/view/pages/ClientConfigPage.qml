import QtQuick 2.15
import vsmt

Window {
    ClientConfigPageForm {
        id: form
    }

    width: form.width
    height: form.height
    maximumHeight: height
    minimumHeight: height
    maximumWidth: width
    minimumWidth: width

    title: "Configure client"

    Component.onCompleted: {
        form.saveConfig.connect(ClientConfigListModel.saveConfigClicked)
        form.revertConfig.connect(ClientConfigListModel.revertConfigClicked)
    }

    function refreshContext() {
        setFieldValues(ClientConfigListModel.context.name,ClientConfigListModel.context.cid,ClientConfigListModel.context.port)
    }

    function setFieldValues(name,cid,port) {
        form.nameField.fieldValue = name
        form.cidField.fieldValue = cid
        form.portField.fieldValue = port
    }
}
