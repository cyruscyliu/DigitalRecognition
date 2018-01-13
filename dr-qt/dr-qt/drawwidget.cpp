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

#include "bp.h"
#include "drawwidget.h"
#include <QPen>
#include <QMessageBox>

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent) {
    setAutoFillBackground (true);
    setPalette (QPalette(Qt::white));
    // 280=28*10
    setFixedSize(280, 280);
    pix = new QPixmap(280, 280);
    pix->fill (Qt::white);
    style = Qt::SolidLine;
    weight = 28;
    color = Qt::black;
}

void DrawWidget::mousePressEvent (QMouseEvent *e){
    startPos = e->pos ();
}

void DrawWidget::mouseMoveEvent (QMouseEvent *e){
    QPainter *painter = new QPainter();

    QPen pen;
    pen.setStyle ((Qt::PenStyle)style);
    pen.setWidth (weight);
    pen.setColor (color);

    painter->begin (pix); // draw on the pix(QPixmap)
    painter->setPen (pen);
    painter->drawLine (startPos, e->pos ());
    painter->end ();
    startPos = e->pos ();
    update ();
}

void DrawWidget::paintEvent (QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap (QPoint(0,0), *pix);
}

void DrawWidget::clear (){
    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill (Qt::white);
    pix = clearPix;
    update ();
}

void DrawWidget::check(){
    bp_ = new BP();

    // save as a test set image file
    // 0x00000803 0x00000001 0x0000001C 0x0000001C
    // 0x00000000 pixels
    QFile file_image("image.dat");
    file_image.open(QIODevice::WriteOnly);
    QDataStream out_image(&file_image);
    out_image << (quint32)0x00000803;
    out_image << (qint32)1;
    out_image << (qint32)28;
    out_image << (qint32)28;

    pix->save("temp.jpg");
    QImage image_t = QImage("temp.jpg").scaled(28, 28);
    image_t.invertPixels();

    for(int i=0; i<image_t.width(); ++i){
        for(int j=0; j<image_t.height(); ++j)
            out_image << (qint8)qGray(image_t.pixel(j, i));
    }
    file_image.close();

    // save as a test set label file
    // 0x00000801
    // 0x00000001
    // 0xFF       label
    QFile file_label("label.dat");
    file_label.open(QIODevice::WriteOnly);
    QDataStream out_label(&file_label);
    out_label << (quint32)0x00000801;
    out_label << (qint32)1;
    out_label << (qint8)0x0;
    file_label.close();

    int result = bp_->check("./image.dat", "./label.dat");

    QMessageBox::information(NULL, "Result", QString::number(result), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    file_image.remove("image.dat");
    file_label.remove("label.dat");
}
