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

import QtQuick 2.0

//![1]
Item {
    id: main
    width: 1980
    height: 1150



    ControlPanel {
        id: controlPanel
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: 10
//![1]

        onSignalSourceChanged: {
            if (source == "sin")
                dataSource.generateData(1, signalCount, sampleCount);
            else
                dataSource.generateData(0, signalCount, sampleCount);
            scopeView1.axisX().max = sampleCount;
            scopeView2.axisX().max = sampleCount;
            scopeView3.axisX().max = sampleCount;
        }
        onSeriesTypeChanged: {
            scopeView1.changeSeriesType(type, scopeView1.name);
            scopeView2.changeSeriesType(type, scopeView2.name);
            scopeView3.changeSeriesType(type, scopeView3.name);
        }


        onRefreshRateChanged: scopeView1.changeRefreshRate(rate);

    }

//![2]
    ScopeView {
        id: scopeView1
        name: "signal"
        color: "#38ad6b"
        anchors.top: parent.top
        anchors.right: controlPanel.left
        anchors.left: parent.left
        width: main.width
        height: main.height/2
    }
    ScopeView {
        id: scopeView2
        name: "convolution"
        color: "#C1DFF9"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: (main.width - controlPanel.width)/2
        height: main.height/2

    }
    ScopeView {
        id: scopeView3
        name: "fft"
        color: "#bccccb"
        anchors.bottom: parent.bottom
        anchors.right: controlPanel.left
        width: (main.width - controlPanel.width)/2
        height: main.height/2
    }

//![2]

}
