import QtQuick 2.15
import vsmt

ProcessTableForm {
    width: parent.width
    model: ProcessTableModel

    Component.onCompleted: {
        headerClicked.connect(onTableHeaderClicked)
        model.sortByCol(4,true)
    }

    function onTableHeaderClicked(col) {
        if(header.orderedByCol === col) {
            header.ascendingOrder = !header.ascendingOrder
        }
        else {
            header.orderedByCol = col
            header.ascendingOrder = true
        }
        model.sortByCol(col,header.ascendingOrder)
    }
}
