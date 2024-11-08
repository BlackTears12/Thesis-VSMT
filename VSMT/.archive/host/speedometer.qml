import QtQuick 2.4
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

/*
    The speedometer gauge and the speed display
*/
CircularGauge {
    id: gauge

    ///current and the target speed value
    value: 0
    property int target_value: value

    maximumValue: 180
    anchors.centerIn: parent

    style: CircularGaugeStyle {
        id: gaugeStyle
        minorTickmarkInset: 3
        minorTickmarkCount: maximumValue / 5

        /*
            The speed display item and its grey background container
        */
        foreground: Item {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.bottom
            anchors.verticalCenterOffset: -130
            Rectangle{
                anchors.centerIn: parent
                color: "#686868"
                implicitHeight: 35
                implicitWidth: 200
                radius: 50
            }
            Text {
                id: speedLabel
                anchors.centerIn: parent
                text: gauge.value.toFixed(0) + " km/h"
                font.pixelSize: outerRadius * 0.15
                color: gauge.value >= gauge.maximumValue - 40 ? "red" : "white"
                antialiasing: true
            }
        }

        ///convert the needles rotation to the value pointed at
        function rotationToValue(rotation : Number){
            /*
                90x + c = 0
                0x + c = -145
                x = 145/90
            */
            return (rotation + 145)*(90/145);
        }

        minorTickmark: Rectangle{
            implicitWidth: 3
            implicitHeight: 10
            antialiasing: true
            anchors.centerIn: parent
            color: rotationToValue(gaugeStyle.needleRotation) >= styleData.value ? "#686868" : (styleData.value >= gauge.maximumValue -45 &&
                   (styleData.value % 10 > 9 || styleData.value % 10 < 1)? "red" : "white")
        }

        tickmark : Rectangle{
            implicitWidth: 3
            implicitHeight: 15
            antialiasing: true
            color: rotationToValue(gaugeStyle.needleRotation) >= styleData.value ? "#686868" : styleData.value >= gauge.maximumValue - 40 ? "red" : "white"
        }

        tickmarkLabel: Text {
            font.pixelSize: Math.max(6, outerRadius * 0.1)
            text: styleData.value
            color: styleData.value >= gauge.maximumValue - 40  ? "red" : "white"
            antialiasing: true
        }

        needle: Rectangle{
            color: "transparent"
        }
    }

    ///the animation which makes the transition to a new speed value fluid
    NumberAnimation {
        id: updateAnimation
        target: gauge
        property: "value"
        easing.type:  Easing.Linear
        alwaysRunToEnd: true
        from: gauge.value
        to: gauge.target_value
        duration: 1000
    }

    ///this function set the desired speed as target and start the NumberAnimation, should be called from a widget
    function updateSpeed(speed : double){
        target_value = speed;
        updateAnimation.restart()
    }
}
