/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtQuick Enterprise Controls Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

.pragma library

// 360 degrees.
var pi2 = 2 * Math.PI;

/*!
    Converts the angle \a degrees to radians.
*/
function degToRad(degrees) {
    return degrees * (Math.PI / 180);
}

/*!
    Converts the angle \a degrees to radians.

    This function assumes that the angle origin (0) is north, as this
    is the origin used by all of the Enterprise Controls. The angle
    returned will have its angle origin (0) pointing east, in order to be
    consistent with standard angles used by \l {QtQuick::Canvas}{Canvas},
    for example.
*/
function degToRadOffset(degrees) {
    return (degrees - 90) * (Math.PI / 180);
}

/*!
    Converts the angle \a radians to degrees.
*/
function radToDeg(radians) {
    return radians * (180 / Math.PI);
}

/*!
    Converts the angle \a radians to degrees.

    This function assumes that the angle origin (0) is east; as is standard for
    mathematical operations using radians (this origin is used by
    \l {QtQuick::Canvas}{Canvas}, for example). The angle returned in degrees
    will have its angle origin (0) pointing north, which is what the enterprise
    controls expect.
*/
function radToDegOffset(radians) {
    return radians * (180 / Math.PI) + 90;
}

/*!
    Returns the top left position of the item if it were centered along
    a circle according to \a angleOnCircle and \a distanceAlongRadius.

    \a angleOnCircle is from 0.0 - pi2.
    \a distanceAlongRadius is the distance along the radius in pixels.
*/
function centerAlongCircle(xCenter, yCenter, width, height, angleOnCircle, distanceAlongRadius) {
    return Qt.point(
        (xCenter - width / 2) + (distanceAlongRadius * Math.cos(angleOnCircle)),
        (yCenter - height / 2) + (distanceAlongRadius * Math.sin(angleOnCircle)));
}

/*!
    Returns \a number rounded to the nearest even integer.
*/
function roundEven(number) {
    var rounded = Math.round(number);
    return rounded % 2 == 0 ? rounded : rounded + 1;
}

///convert the needles rotation to the value pointed at
function rotationToValue(rotation,max_value){
    /*
        40x + c = 0
        90x + c = -145
        x = 145/90
    */
    return (rotation + 120)*(max_value/2/120);
}
