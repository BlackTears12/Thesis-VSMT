import QtQuick 2.2
import vsmt

CircularGauge {
    /* CpuRangeModel */

    targetValue: CpuRangeModel.value
    gaugeStyle: GaugeStyle{
        tickActivatedColor: "#c11417"
    }

    Connections {
        target: CpuRangeModel
        function onValueChanged() {
            refresh()
        }
    }

    onClicked: CpuRangeModel.activated()
}
