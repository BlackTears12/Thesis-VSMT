import QtQuick 2.15
import view

LinearChartForm {
    Connections {
           target: dataFromCpp
           onWValueChanged: {
               if(lineSeries1.count > 5)
                   lineSeries1.remove(0);
               lineSeries1.append(dataFromCpp.wValue.x, dataFromCpp.wValue.y)
               axisX.min = lineSeries1.at(0).x
               axisX.max = lineSeries1.at(lineSeries1.count-1).x
           }
    }
}
