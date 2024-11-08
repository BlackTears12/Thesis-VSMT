import QtQuick 2.15
import vsmt

LinearChartForm {
    required property NetworkLoadDataModel dataModel
    property string splineName: "Rx"
    property color splineColor: "red"
    property color chartBackgroundColor: Style.secondaryColor

    mapper.model: dataModel
    spline.name: splineName
    spline.color: splineColor
    maxSize: dataModel.maxSize
    maxValue: dataModel.maxValue
    backgroundColor: chartBackgroundColor

    spline.axisX {
        gridVisible: false
    }
}
