/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCharts 2.7
import vsmt

ChartView {
    id: chartView

    property int maxSize
    property alias mapper: mapper
    property string chartName: "chart"
    property alias spline: spline
    property alias maxValue: yAxis.max

    layer.smooth: true
    antialiasing: true
    backgroundColor: Style.backgroundColor
    legend.labelColor: "white"

    SplineSeries {
        id: spline
        useOpenGL: true

        name: "Average Core Utilization"
        color: "#c11417"
        pointsVisible: true
        width: 3

        axisX: ValuesAxis {
            min: 1
            max: maxSize
            labelsColor: "white"
            labelsVisible: false
        }

        axisY: ValuesAxis {
            id: yAxis
            min: 0
            max: 100
            labelsColor: "white"
            labelsVisible: false
        }

        VXYModelMapper {
            id: mapper
            xColumn: 0
            yColumn: 1
        }
    }
}
