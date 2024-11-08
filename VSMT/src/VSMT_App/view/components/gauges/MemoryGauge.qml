import QtQuick 2.2
import vsmt

CircularGauge {
    /* MemoryRangeModel */

    targetValue: MemoryRangeModel.value
    gaugeStyle: GaugeStyle{
        tickActivatedColor: "#5af155"
    }

    Connections {
        target: MemoryRangeModel
        function onValueChanged() {
            refresh()
        }
    }

    onClicked: MemoryRangeModel.activated()
}
