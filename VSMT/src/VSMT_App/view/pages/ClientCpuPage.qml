

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCharts
import vsmt

Item {
    width: 1100
    height: 900

    ClientDescriptor {
        id: descriptor
        width: 350
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.left: parent.left
        height: parent.height
    }

    Item {
        id: contentRoot

        width: parent.width - descriptor.width
        height: parent.height
        anchors.left: descriptor.right
        anchors.top: parent.top

        CpuChart {
            id: cpuChart
            width: parent.width*0.9
            height: width * 0.3
            anchors.horizontalCenter: parent.horizontalCenter
        }

        GridView {
            id: grid
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: cpuChart.bottom
            height: parent.height - cpuChart.height
            width: parent.width - anchors.leftMargin
            cellWidth: width/3
            cellHeight: cellWidth*0.5

            model: CoreLoadDataModelProvider
            delegate: Rectangle {
                required property CoreLoadDataModel datamodel
                required property int coreIndex

                radius: 20
                width: grid.cellWidth - 10
                height: grid.cellHeight - 10
                color: "#303030"
                SmallCpuChart {
                    splineName: "CPU " + coreIndex
                    splineColor: grid.chartColorProvider(coreIndex)
                    anchors.fill: parent
                    dataModel: datamodel
                }
            }

            function chartColorProvider(index) {
                var colors = ["#00ff13","#0046ff","#f5f106","#f50132","#2bc2f3",
                    "#186019","#ff6d00"]
                return colors[index%colors.length]
            }
        }
    }
}
