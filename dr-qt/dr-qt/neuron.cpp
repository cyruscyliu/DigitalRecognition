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

#include "neuron_utils.h"
#include "neuron.h"
#include <memory.h>

using namespace std;

/************************************************************************
 * neuron                                                                      
 ************************************************************************/


/************************************************************************
 * neuron layer                                                                      
 ************************************************************************/

neuronLayer::neuronLayer(int numNeurons, int numInputsPerNeuron)
	:mNumNeurons(numNeurons),
	mNumInputsPerNeuron(numInputsPerNeuron)
{
	mWeights = new double*[mNumNeurons];
	mOutActivations = new double[mNumNeurons];
	mOutErrors = new double[mNumNeurons];

	reset();
}

neuronLayer::neuronLayer(neuronLayer& nl)
	:neuronLayer(nl.mNumNeurons, nl.mNumInputsPerNeuron)
{
	int copySize = mNumNeurons * sizeof(double);

	memcpy(mOutActivations, nl.mOutActivations, copySize);
	memcpy(mOutErrors, nl.mOutErrors, copySize);

	for (int i = 0; i < mNumNeurons; i++)
	{
		memcpy(mWeights[i], nl.mWeights[i], copySize);
	}
}

neuronLayer::~neuronLayer()
{
	/** release weights */
	for (int i = 0; i < mNumNeurons; i++)
	{
		delete []mWeights[i];
	}

	delete []mWeights;

	/** release activations */
	delete []mOutActivations;

	/** release errors */
	delete []mOutErrors;
}

void neuronLayer::reset()
{
	memset(mOutActivations, 0, mNumNeurons * sizeof(double));
	memset(mOutErrors, 0, mNumNeurons * sizeof(double));

	for (int i = 0; i < mNumNeurons; ++i)
	{
		//we need an additional weight for the bias hence the +1
		int numWeights = mNumInputsPerNeuron + 1;
		double* curWeights = new double[numWeights];
		mWeights[i] = curWeights;

		for (int w = 0; w < numWeights; w++)
		{
			//set up the weights with an initial random value
			double temp = RandomClamped();
			curWeights[w] = temp;
		}
	}
}

