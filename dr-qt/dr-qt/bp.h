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

#ifndef BP_H
#define BP_H

#include "bp_neuron_net.h"
#include "data_input.h"
#include "neuron_utils.h"
#include <memory.h>

/** indicate 0 ~ 9 */
#define NUM_NET_OUT 10
#define NUM_HIDDEN 300
#define NET_LEARNING_RATE 0.5

#define TRAIN_IMAGES_URL "./train-images.idx3-ubyte"
#define TRAIN_LABELS_URL "./train-labels.idx1-ubyte"

class BP
{
public:
    BP(); //train
    void preProcessInputDataWithNoise(const unsigned char src[], double out[], int size);
    void preProcessInputData(const unsigned char src[], double out[], int size);
    int check(const char* test_image_url, const char* test_lable_url); //test
private:
    dataInput src;
    dataInput testData;
    bpNeuronNet *bpnn;
};

#endif // BP_H
