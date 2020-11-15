/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "renderarea.h"

#include <QDebug>
#include <QtMath>
#include <QPair>
#include <QPainter>
#include <QPainterPath>

//! [0]
RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    squareGreen.load(":/images/carre_vert.bmp");
    squareGray.load(":/images/carre_gris.bmp");
    squareEnding.load(":/images/carre_arrivee.bmp");
    squareCar.load(":/images/voiture.bmp");

    setBackgroundRole(QPalette::Base);
//    setAutoFillBackground(true);


    // tout en gazon
    for(int i=0; i<maxStylesX; i++) {
        for(int j=0; j<maxStylesY; j++) {
           setStyle(i, j, Garden);
        }
    }

    // lignes horizontales
    for(int i=4; i<maxStylesX-4; i++) {
        setStyle(i, 1, Road);
        setStyle(i, 2, Road);
        setStyle(i, maxStylesY-2, Road);
        setStyle(i, maxStylesY-3, Road);
    }

    // lignes verticales
    for(int j=4; j<maxStylesY-4; j++) {
        setStyle(1, j, Road);
        setStyle(2, j, Road);
        setStyle(maxStylesX-2, j, Road);
        setStyle(maxStylesX-3, j, Road);
    }

    // coins
    bool first=true;
    for(int i=1; i<4; i++) {
        for(int j=1; j<4; j++) {
            if(first) { first=false; continue;}
            setStyle(i, j, Road);
            setStyle(maxStylesX-i-1, j, Road);
            setStyle(i, maxStylesY-j-1, Road);
            setStyle(maxStylesX-i-1, maxStylesY-j-1, Road);
        }
    }

    // ligne d'arrivee
    setStyle(18, maxStylesY-2, End);
    setStyle(18, maxStylesY-3, End);

    // position initiale voiture
    posVoiture.first = 18.5f;
    posVoiture.second = maxStylesY-2.5f;
    rotVoiture=0;
}
//! [0]

void RenderArea::setStyle(const qint8 x, const qint8 y, const Styles s) {
    QPair<qint8,qint8> pair;
    pair.first = x;
    pair.second = y;
    styles[pair] = s;
}

//! [1]
QSize RenderArea::minimumSizeHint() const
{
    return QSize(800, 600);
}
//! [1]

//! [2]
QSize RenderArea::sizeHint() const
{
    return QSize(800, 600);
}
//! [2]

//! [8]
void RenderArea::paintEvent(QPaintEvent * /* event */)
{
//! [9]
     QPainter painter(this);
//    painter.setPen(pen);
//    painter.setBrush(brush);
    // dessine circuit
    for(int i=0; i<maxStylesX; i++) {
        for(int j=0; j<maxStylesY; j++) {
            QPixmap pix=squareGreen;
            QPair<qint8,qint8> pair(i,j);

            switch(styles[pair]) {
                case Road:
//                    qDebug() << "x(" << i << "," << j <<"): Road";
                    pix=squareGray;
                    break;
                case End:
//                    qDebug() << "x(" << i << "," << j <<"): End";
                    pix=squareEnding;
                    break;
                case Garden:
//                    qDebug() << "x(" << i << "," << j <<"): Garden";
                    pix=squareGreen;
                    break;
                default: qDebug() << "x(" << i << "," << j <<"): Unknown";
            }

            painter.drawPixmap(i*32, j*32, pix);
        }
    }

    // dessine voiture
    painter.save();
    painter.translate(32*posVoiture.first, 32*posVoiture.second);
    painter.rotate(rotVoiture);
    painter.drawPixmap(-squareCar.size().width()/2,-squareCar.size().height()/2, squareCar);
    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
//    painter.setPen(palette().dark().color());
//    painter.setBrush(Qt::NoBrush);
//    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
//! [13]

void RenderArea::doKey(const Action a) {
    switch(a) {
    case Up:
    {
        posVoiture.second-=0.1f;
        float t=rotVoiture-10;
        if (t<-90.0f)
            rotVoiture=-90.0f;
        else
            rotVoiture=t;
    }
        break;
    case Down:
        posVoiture.second+=0.1f;
        rotVoiture=90;
        break;
    case Right:
        posVoiture.first+=0.1f;
        rotVoiture=0;
        break;
    case Left:
        posVoiture.first-=0.1f;
        rotVoiture=180;
        break;
    default: break;
    }
    update();
}
