import QtQuick 2.15

Item {
    property color labelColor: "white"
    property int labelSize: 18
    property color alertLabelColor: "red"
    property color backgroundColor: "#303030"

    property color tickAlertColor: "red"
    property color tickColor: "grey"
    property color tickActivatedColor: "red"

    property int alertThreshold: 0

    property bool tickmarkVisible: false
    property bool minorTickmarkVisible: true

    property real tickmarkWidthMultiplier: 0.04
    property real tickmarkHeightMultiplier: 0.1

    property real minorTickmarkWidthMultiplier: 0.05
    //0.1
    property real minorTickmarkHeightMultiplier: 0.2

    property int valueAngle: 120
}
