import QtQuick 2.15
import view

ProcessTableForm {
    model: ProcessTableModel

    Component.onCompleted: {
        headerClicked.connect(model.headerClicked)
    }
}
