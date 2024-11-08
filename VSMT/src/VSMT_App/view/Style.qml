pragma Singleton
import QtQuick 2.15

QtObject {
    property color backgroundColor: "#252d50"
    property color secondaryColor: "#303030"
    property color dividerColor: "#585858"

    property color gaugeTextColor: "white"
    property color gaugeAlertTextColor: "red"
    property color gaugeBackgroundColor: "#303030"

    property color gaugeTickAlertColor: "red"
    property color gaugeTickColor: "white"
    property color gaugeTickActivatedColor: "grey"

    property int gaugeAlertThreshold: 15
}
