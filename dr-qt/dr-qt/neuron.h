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

#ifndef __NEURON_H__
#define __NEURON_H__

/** the type of neuron layer */

struct neuronLayer 
{
public:
	neuronLayer(int numNeurons, int numInputsPerNeuron);

	neuronLayer(neuronLayer& nl);
	~neuronLayer();

	void reset(void);
public:
	int mNumInputsPerNeuron; /** the count of input node per neuron */
	int mNumNeurons; /** the count of neuron(or node) of current layer */

	double** mWeights; /** 2D array,row: indicate neuron, column: the weights per neuron */
	double* mOutActivations; /** the output activation of neuron. 1D array, the index of array indicate neuron */
	double* mOutErrors; /** the error of output of neuron. 1D array, the index of array indicate neuron */

};

#endif // !__NEURON_H__

