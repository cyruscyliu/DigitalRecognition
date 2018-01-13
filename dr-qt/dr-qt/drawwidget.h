/*
* MIT License
*
* Copyright (c) 2018 Cyrus Liu <liuqiangqhtf@163.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QPalette>
#include "bp.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);
    // mouse event
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    // update paint
    void paintEvent(QPaintEvent *);
signals:
public slots:
    void clear();
    void check();
private:
    BP *bp_;
    QPixmap *pix;
    QPoint startPos;
    QPoint endPos;
    int style;
    int weight;
    QColor color;
};

#endif // DRAWWIDGET_H
