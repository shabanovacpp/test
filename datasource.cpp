/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "datasource.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)


DataSource::DataSource(QQuickView *appViewer, QObject *parent) :
    QObject(parent),
    m_appViewer(appViewer),
    m_index_function(-1),
    m_index_convolution(-1),
    m_index_fft(-1)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

    generateData(1, 5, timeLength);
}

void DataSource::update(QAbstractSeries *series, QString nameOfGraphic)
{
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);

        if(nameOfGraphic == "signal")
        {
            m_index_function++;
            if (m_index_function > m_data_function.count() - 1)
                m_index_function = 0;
            QVector<QPointF> points = m_data_function.at(m_index_function);
            xySeries->replace(points);
        }
        else if(nameOfGraphic == "convolution"){
            m_index_convolution++;
            if (m_index_convolution > m_data_convolution.count() - 1)
                m_index_convolution = 0;
            QVector<QPointF> points = m_data_convolution.at(m_index_convolution);
            xySeries->replace(points);
        }
        else if(nameOfGraphic == "fft"){
            m_index_fft++;
            if (m_index_fft > m_data_fft.count() - 1)
                m_index_fft = 0;
            QVector<QPointF> points = m_data_fft.at(m_index_fft);
            xySeries->replace(points);
        }
    }
}

void DataSource::generateData(int type, int rowCount, int colCount)
{
    // Remove previous data
    m_data_function.clear();
    m_data_convolution.clear();
    m_data_fft.clear();

    // Append the new data depending on the type
    for (int i(0); i < rowCount; i++) {

        QVector<QPointF> points_function;
        QVector<QPointF> points_convolution;
        QVector<QPointF> points_fft;
        points_function.reserve(colCount);
        points_convolution.reserve(colCount);
        points_fft.reserve(colCount);

        vectorKek.push_back(points_function);

        for (int j(0); j < colCount; j++) {
            qreal x_function(0);
            qreal y_function(0);
            qreal x_convolution(0);
            qreal y_convolution(0);
            qreal x_fft(0);
            qreal y_fft(0);
            switch (type) {
            case 0:
                // beats data
                y_function = qCos(M_PI / (timeLength/100) * j)*qCos(M_PI / (timeLength/10) * j) + QRandomGenerator::global()->generateDouble()/5;
                x_function = j;
                x_convolution = j;
                y_convolution = y_function*qSin(M_PI / 50 * j);
                x_fft = j;
                y_fft = 10*y_function/((j+timeLength/2)/10 - 100);
                break;
            case 1:
                // sin data
                x_function = j;
                y_function = qSin(M_PI / 50 * j) +  QRandomGenerator::global()->generateDouble()/3;
                x_convolution = j;
                y_convolution = y_function*qSin(M_PI / 500 * j);
                x_fft = j*qSin(j/5)+timeLength/2;
                y_fft = j*qCos(j/5)/50;


                break;
            default:
                // unknown, do nothing
                break;
            }
            points_function.append(QPointF(x_function, y_function));
            points_convolution.append(QPointF(x_convolution, y_convolution));
            points_fft.append(QPointF(x_fft, y_fft));
        }
        m_data_function.append(points_function);
        m_data_convolution.append(points_convolution);
        m_data_fft.append(points_fft);
    }
}
