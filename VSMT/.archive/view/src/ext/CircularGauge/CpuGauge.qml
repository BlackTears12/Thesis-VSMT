import QtQuick 2.2
import view

CircularGauge {
    /* CpuRangeModel */

    targetValue: CpuRangeModel.value
    gaugeStyle: GaugeStyle{
        tickActivatedColor: "#5af155"
    }

    Connections {
        target: CpuRangeModel
        function onValueChanged() {
            refresh()
        }
    }

    onClicked: CpuRangeModel.activated()
}
