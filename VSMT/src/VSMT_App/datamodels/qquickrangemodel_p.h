/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

/*#ifndef QQUICKRANGEMODEL_P_H
#define QQUICKRANGEMODEL_P_H

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class QQuickRangeModel1Private;

class QQuickRangeModel1 : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    QML_NAMED_ELEMENT(RangeModel)

    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged USER true)
    Q_PROPERTY(qreal minimumValue READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(qreal maximumValue READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(qreal stepSize READ stepSize WRITE setStepSize NOTIFY stepSizeChanged)
    Q_PROPERTY(qreal position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(qreal positionAtMinimum READ positionAtMinimum WRITE setPositionAtMinimum NOTIFY positionAtMinimumChanged)
    Q_PROPERTY(qreal positionAtMaximum READ positionAtMaximum WRITE setPositionAtMaximum NOTIFY positionAtMaximumChanged)
    Q_PROPERTY(bool inverted READ inverted WRITE setInverted NOTIFY invertedChanged)

    Q_INTERFACES(QQmlParserStatus)

public:
    QQuickRangeModel1(QObject *parent = 0);
    virtual ~QQuickRangeModel1();

    void setRange(qreal min, qreal max);
    void setPositionRange(qreal min, qreal max);

    void setStepSize(qreal stepSize);
    qreal stepSize() const;

    void setMinimum(qreal min);
    qreal minimum() const;

    void setMaximum(qreal max);
    qreal maximum() const;

    void setPositionAtMinimum(qreal posAtMin);
    qreal positionAtMinimum() const;

    void setPositionAtMaximum(qreal posAtMax);
    qreal positionAtMaximum() const;

    void setInverted(bool inverted);
    bool inverted() const;

    qreal value() const;
    qreal position() const;

    Q_INVOKABLE qreal valueForPosition(qreal position) const;
    Q_INVOKABLE qreal positionForValue(qreal value) const;

    void classBegin() override;
    void componentComplete() override;

public Q_SLOTS:
    void toMinimum();
    void toMaximum();
    void setValue(qreal value);
    void setPosition(qreal position);
    void increaseSingleStep();
    void decreaseSingleStep();

Q_SIGNALS:
    void valueChanged(qreal value);
    void positionChanged(qreal position);

    void stepSizeChanged(qreal stepSize);

    void invertedChanged(bool inverted);

    void minimumChanged(qreal min);
    void maximumChanged(qreal max);
    void positionAtMinimumChanged(qreal min);
    void positionAtMaximumChanged(qreal max);

protected:
    QQuickRangeModel1(QQuickRangeModel1Private &dd, QObject *parent);
    QQuickRangeModel1Private* d_ptr;

private:
    Q_DISABLE_COPY(QQuickRangeModel1)
    Q_DECLARE_PRIVATE(QQuickRangeModel1)

};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickRangeModel1)

#endif // QQUICKRANGEMODEL_P_H
*/
