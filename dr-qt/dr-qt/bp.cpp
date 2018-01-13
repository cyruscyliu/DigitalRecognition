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
#include <QProgressDialog>
#include <QApplication>
#include <QDesktopWidget>

BP::BP(){
    // progress dialog
    QProgressDialog progressDialog;
    progressDialog.move((QApplication::desktop()->width() - progressDialog.width())/2,
                        (QApplication::desktop()->height() - progressDialog.height())/2);
    progressDialog.setWindowModality(Qt::WindowModal);
    progressDialog.setMinimumDuration(0);
    progressDialog.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    progressDialog.setFixedSize(200, 50);
    progressDialog.setRange(0, 100);
    progressDialog.setWindowTitle("Training...");
    progressDialog.setCancelButton(0);
    progressDialog.setValue(1);

    // vars
    if (!src.openImageFile(TRAIN_IMAGES_URL) or !src.openLabelFile(TRAIN_LABELS_URL)){
        qDebug("Open data failed");
    }

    int imageSize = src.imageLength();
    int numImages = src.numImage();

    bpnn = new bpNeuronNet(imageSize, NET_LEARNING_RATE);
    bpnn->addNeuronLayer(NUM_HIDDEN);
    bpnn->addNeuronLayer(NUM_NET_OUT);

    double net_target[NUM_NET_OUT];
    char* temp = new char[imageSize];
    double* net_train = new double[imageSize];

    // train
    numImages = 7000;
    for (int j = 0; j < numImages; j++)
    {
        int label = 0;
        memset(net_target, 0, NUM_NET_OUT * sizeof(double));

        if (src.read(&label, temp))
        {
            net_target[label] = 1.0;
            preProcessInputDataWithNoise((unsigned char*)temp, net_train, imageSize);
            bpnn->training(net_train, net_target);
            progressDialog.setValue(95.0 * j / numImages);
        } else {
            qDebug("read train data failed");
            break;
        }
        if(progressDialog.wasCanceled())
            break;
    }

    src.reset();
    delete []net_train;
    delete []temp;
    qDebug("%f", bpnn->getError());
    progressDialog.setValue(100);
}

void BP::preProcessInputDataWithNoise(const unsigned char src[], double out[], int size){
    for (int i = 0; i < size; i++){
        out[i] = ((src[i] >= 128) ? 1.0 : 0.0) + RandFloat() * 0.1;
    }
}

void BP::preProcessInputData(const unsigned char src[], double out[], int size){
    for (int i = 0; i < size; i++){
        out[i] = (src[i] >= 128) ? 1.0 : 0.0;
    }
}

int BP::check(const char* test_image_url, const char* test_lable_url){
    int idx = 256;
    if (testData.openImageFile(test_image_url) && testData.openLabelFile(test_lable_url)){
        int imageSize = testData.imageLength();

        double* net_out = NULL;
        char* temp = new char[imageSize];
        double* net_test = new double[imageSize];

        int label = 0;
        if (testData.read(&label, temp)){
            preProcessInputData((unsigned char*)temp, net_test, imageSize);
            bpnn->process(net_test, &net_out);
            // find the best
            idx = -1;
            double max_value = -99999;
            for (int i = 0; i < NUM_NET_OUT; i++){
                if (net_out[i] > max_value){
                        max_value = net_out[i];
                        idx = i;
                }
            }
        } else {
            qDebug("read data failed");
        }
        delete []net_test;
        delete []temp;
    } else {
        qDebug("open data failed");
    }
    return idx;
}
