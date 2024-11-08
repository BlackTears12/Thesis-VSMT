import QtQuick 2.15
import view

LinearChartForm {
    maxSize: CpuGraphDataModel.maxSize
    mapper.model: CpuGraphDataModel
}
