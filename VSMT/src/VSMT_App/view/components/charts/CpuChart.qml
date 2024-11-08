import QtQuick 2.15
import vsmt

LinearChartForm {
    maxSize: CpuLoadDataModel.maxSize
    mapper.model: CpuLoadDataModel

    backgroundColor: Style.backgroundColor
    spline.axisY {
        labelsVisible: true
    }
}
