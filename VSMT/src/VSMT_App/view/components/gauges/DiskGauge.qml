import QtQuick 2.2
import vsmt

CircularGauge {

    targetValue: DiskRangeModel.value
    gaugeStyle: GaugeStyle{
        tickActivatedColor: "#c9c905"
    }

    Connections {
        target: DiskRangeModel
        function onValueChanged() {
            refresh()
        }
    }

    onClicked: DiskRangeModel.activated()
}
