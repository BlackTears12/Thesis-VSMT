import QtQuick 2.15
import vsmt

LinearChartForm {
    required property CoreLoadDataModel dataModel
    property string splineName: "CPU core"
    property color splineColor: "red"
    property color chartBackgroundColor: Style.secondaryColor

    mapper.model: dataModel
    spline.name: splineName
    spline.color: splineColor
    maxSize: dataModel.maxSize
    backgroundColor: chartBackgroundColor

    spline.axisX {
        gridVisible: false
    }
}
