import QtQuick 2.2
import view

CircularGauge {
    /* MemoryRangeModel */

    targetValue: MemoryRangeModel.value
    gaugeStyle: GaugeStyle{
        tickActivatedColor: "#c12108"
    }

    Connections {
        target: MemoryRangeModel
        function onValueChanged() {
            refresh()
        }
    }

    onClicked: MemoryRangeModel.activated()
}
