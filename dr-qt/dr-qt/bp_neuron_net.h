/*
* MIT License
*
* Copyright (c) 2017 wen.gu <454727014@qq.com>
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

#ifndef __BP_NEURON_NET_H__
#define __BP_NEURON_NET_H__

#include <vector>
#include "neuron.h"

using namespace std;

/** used in bpNeuronNet */

/** range, 0 < x <= 1.0 */
#define ACTIVATION_RESPONSE 0.7
#define BIAS                1

/** bp neuron net */
class bpNeuronNet
{
public:
	bpNeuronNet(int numInputs, double learningRate);
	~bpNeuronNet();
public:
	inline double getError(void) { return mErrorSum; }
	bool training(const double inputs[], const double targets[]);
	void process(const double inputs[], double* outputs[]);
	void reset(void);
	void addNeuronLayer(int numNeurons);
private:
	/** Forward propagation, calculate the output of neuron net */
	inline double sigmoidActive(double activation, double response);
	void updateNeuronLayer(neuronLayer& nl, const double inputs[]);
	/** Back propagation, for training neuron net */
	inline double backActive(double x);
	void trainUpdate(const double inputs[], const double targets[]);
	void trainNeuronLayer(neuronLayer& nl,  const double prevOutActivations[], double prevOutErrors[]);
private:
	int mNumInputs;
	int mNumOutputs;
	int mNumHiddenLayers; /** the total layers= mNumHiddenLayers + 1; (doesn't include input layer) */
	double mLearningRate;
	double mErrorSum;
	vector<neuronLayer*> mNeuronLayers;
};

#endif // !__BP_NEURON_NET_H__
